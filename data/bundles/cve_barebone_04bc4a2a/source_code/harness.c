/* cve_barebone isolation harness for rizin CVE-2023-27590
 * Target: gdb_to_rz_profile (librz/reg/profile.c) -- CWE-787 stack-buffer-overflow.
 *
 * The bug: the per-register parser uses unbounded `%s` conversions in
 *   sscanf(ptr, " %s %d %d %d %d %s %s", name, ..., type, groups)
 * writing into the fixed stack buffers  name[16] / type[16] / groups[128].
 * A field longer than its buffer overflows the stack slot -> ASAN reports a
 * stack-buffer-overflow WRITE inside the sscanf interceptor with
 * gdb_to_rz_profile on the stack (dedup_token:
 *   scanf_common--__interceptor___isoc99_sscanf--gdb_to_rz_profile).
 *
 * Everything below the target function is copied VERBATIM from the vulnerable
 * rizin tree (librz/util/strbuf.c, str.c, str_trim.c, mem.c) with real names.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>

/* ---- minimal faithful rizin macros / typedefs (from rz_types.h, rz_assert.h,
 *      rz_str_util.h, rz_types_overflow.h) ---- */
typedef unsigned char ut8;

#define RZ_API
#define RZ_OWN
#define RZ_NONNULL

#define RZ_NEW0(x) (x *)calloc(1, sizeof(x))
#define RZ_FREE(x) \
	{ \
		free((void *)x); \
		x = NULL; \
	}
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

/* release-build form of rz_assert.h: no abort, just early-return */
#define rz_return_if_fail(expr) \
	do { \
		if (!(expr)) { \
			return; \
		} \
	} while (0)
#define rz_return_val_if_fail(expr, val) \
	do { \
		if (!(expr)) { \
			return (val); \
		} \
	} while (0)

#define IS_WHITECHAR(x) ((x) == ' ' || (x) == '\t' || (x) == '\n' || (x) == '\r')

/* rz_types_overflow.h: UNSIGNED_MUL_OVERFLOW_CHECK(SZT_MUL_OVFCHK, size_t, ...) */
static inline bool SZT_MUL_OVFCHK(size_t a, size_t b) {
	return (a > 0 && b > 0 && a > SIZE_MAX / b);
}

/* ---- RzStrBuf (librz/include/rz_util/rz_strbuf.h) ---- */
typedef struct {
	char buf[32];
	size_t len; // string length in chars or binary buffer size
	char *ptr; // ptr replacing buf in case strlen > sizeof(buf)
	size_t ptrlen; // string length + 1 or binary buffer size
	bool weakref; // ptr is not owned
} RzStrBuf;

/* ---- librz/util/mem.c ---- */
RZ_API void *rz_mem_dup(const void *s, int l) {
	void *d = malloc(l);
	if (d) {
		memcpy(d, s, l);
	}
	return d;
}

/* ---- librz/util/str_trim.c ---- */
RZ_API const char *rz_str_trim_head_ro(const char *str) {
	rz_return_val_if_fail(str, NULL);
	for (; *str && IS_WHITECHAR(*str); str++) {
		;
	}
	return str;
}

/* ---- librz/util/str.c ---- */
RZ_API bool rz_str_startswith(RZ_NONNULL const char *str, RZ_NONNULL const char *needle) {
	rz_return_val_if_fail(str && needle, false);
	if (str == needle) {
		return true;
	}
	return !strncmp(str, needle, strlen(needle));
}

/* ---- librz/util/strbuf.c ---- */
RZ_API void rz_strbuf_init(RzStrBuf *sb) {
	rz_return_if_fail(sb);
	memset(sb, 0, sizeof(RzStrBuf));
}

RZ_API bool rz_strbuf_setbin(RzStrBuf *sb, const ut8 *s, size_t l) {
	rz_return_val_if_fail(sb && s, false);
	if (l >= sizeof(sb->buf)) {
		char *ptr = sb->ptr;
		if (!ptr || l + 1 > sb->ptrlen) {
			ptr = malloc(l + 1);
			if (!ptr) {
				return false;
			}
			RZ_FREE(sb->ptr);
			sb->ptrlen = l + 1;
			sb->ptr = ptr;
		}
		memcpy(ptr, s, l);
		ptr[l] = 0;
	} else {
		RZ_FREE(sb->ptr);
		memcpy(sb->buf, s, l);
		sb->buf[l] = 0;
	}
	sb->len = l;
	sb->weakref = false;
	return true;
}

RZ_API char *rz_strbuf_get(RzStrBuf *sb) {
	rz_return_val_if_fail(sb, NULL);
	return sb->ptr ? sb->ptr : sb->buf;
}

RZ_API const char *rz_strbuf_set(RzStrBuf *sb, const char *s) {
	rz_return_val_if_fail(sb, NULL);
	if (!s) {
		rz_strbuf_init(sb);
		return rz_strbuf_get(sb);
	}
	size_t len = strlen(s);
	if (!rz_strbuf_setbin(sb, (const ut8 *)s, len)) {
		return NULL;
	}
	sb->len = len;
	return rz_strbuf_get(sb);
}

RZ_API RzStrBuf *rz_strbuf_new(const char *str) {
	RzStrBuf *s = RZ_NEW0(RzStrBuf);
	if (str) {
		rz_strbuf_set(s, str);
	}
	return s;
}

RZ_API bool rz_strbuf_append_n(RzStrBuf *sb, const char *s, size_t l) {
	rz_return_val_if_fail(sb && s, false);

	if (sb->weakref) {
		return false;
	}

	// fast path if no chars to append
	if (l == 0) {
		return true;
	}

	if ((sb->len + l + 1) <= sizeof(sb->buf)) {
		memcpy(sb->buf + sb->len, s, l);
		sb->buf[sb->len + l] = 0;
		RZ_FREE(sb->ptr);
	} else {
		size_t newlen = sb->len + l + 128;
		char *p = sb->ptr;
		bool allocated = true;
		if (!sb->ptr) {
			p = malloc(newlen);
			if (p && sb->len > 0) {
				memcpy(p, sb->buf, sb->len);
			}
		} else if (sb->len + l + 1 > sb->ptrlen) {
			if (SZT_MUL_OVFCHK(newlen, 2)) {
				return false;
			}
			newlen *= 2;
			p = realloc(sb->ptr, newlen);
		} else {
			allocated = false;
		}
		if (allocated) {
			if (!p) {
				return false;
			}
			sb->ptr = p;
			sb->ptrlen = newlen;
		}
		if (p) {
			memcpy(p + sb->len, s, l);
			*(p + sb->len + l) = 0;
		}
	}
	sb->len += l;
	return true;
}

RZ_API bool rz_strbuf_append(RzStrBuf *sb, const char *s) {
	rz_return_val_if_fail(sb && s, false);

	int l = strlen(s);
	return rz_strbuf_append_n(sb, s, l);
}

RZ_API bool rz_strbuf_vappendf(RzStrBuf *sb, const char *fmt, va_list ap) {
	int ret;
	va_list ap2;
	char string[1024];

	rz_return_val_if_fail(sb && fmt, false);

	if (sb->weakref) {
		return false;
	}
	va_copy(ap2, ap);
	ret = vsnprintf(string, sizeof(string), fmt, ap);
	if (ret >= sizeof(string)) {
		char *p = malloc(ret + 1);
		if (!p) {
			va_end(ap2);
			return false;
		}
		*p = 0;
		vsnprintf(p, ret + 1, fmt, ap2);
		ret = rz_strbuf_append(sb, p);
		free(p);
	} else if (ret >= 0) {
		ret = rz_strbuf_append(sb, string);
	} else {
		ret = false;
	}
	va_end(ap2);
	return ret;
}

RZ_API bool rz_strbuf_appendf(RzStrBuf *sb, const char *fmt, ...) {
	va_list ap;

	rz_return_val_if_fail(sb && fmt, false);

	va_start(ap, fmt);
	bool ret = rz_strbuf_vappendf(sb, fmt, ap);
	va_end(ap);
	return ret;
}

static inline char *drain(RzStrBuf *sb) {
	return sb->ptr
		? sb->weakref
			? rz_mem_dup(sb->ptr, sb->ptrlen)
			: sb->ptr
		: strdup(sb->buf);
}

RZ_API RZ_OWN char *rz_strbuf_drain(RzStrBuf *sb) {
	rz_return_val_if_fail(sb, NULL);
	char *ret = drain(sb);
	free(sb);
	return ret;
}

RZ_API void rz_strbuf_fini(RzStrBuf *sb) {
	if (sb && !sb->weakref) {
		RZ_FREE(sb->ptr);
		sb->ptr = NULL;
		sb->len = 0;
		sb->buf[0] = '\0';
	}
}

RZ_API void rz_strbuf_free(RzStrBuf *sb) {
	if (sb) {
		rz_strbuf_fini(sb);
		free(sb);
	}
}

/* ======================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from                             */
/*   data_cve/cve_04bc4a2a/target/original_function.c                       */
/* ======================================================================== */
static char *gdb_to_rz_profile(const char *gdb) {
	rz_return_val_if_fail(gdb, NULL);
	RzStrBuf *sb = rz_strbuf_new("");
	if (!sb) {
		return NULL;
	}
	char *ptr1, *gptr, *gptr1;
	char name[16], groups[128], type[16];
	const int all = 1, gpr = 2, save = 4, restore = 8, float_ = 16,
		  sse = 32, vector = 64, system = 128, mmx = 256;
	int number, rel, offset, size, type_bits, ret;
	// Every line is -
	// Name Number Rel Offset Size Type Groups
	const char *ptr = rz_str_trim_head_ro(gdb);

	// It's possible someone includes the heading line too. Skip it
	if (rz_str_startswith(ptr, "Name")) {
		if (!(ptr = strchr(ptr, '\n'))) {
			rz_strbuf_free(sb);
			return NULL;
		}
		ptr++;
	}
	for (;;) {
		// Skip whitespace at beginning of line and empty lines
		while (isspace((ut8)*ptr)) {
			ptr++;
		}
		if (!*ptr) {
			break;
		}
		if ((ptr1 = strchr(ptr, '\n'))) {
			*ptr1 = '\0';
		} else {
			eprintf("Could not parse line: %s (missing \\n)\n", ptr);
			rz_strbuf_free(sb);
			return false;
		}
		ret = sscanf(ptr, " %s %d %d %d %d %s %s", name, &number, &rel,
			&offset, &size, type, groups);
		// Groups is optional, others not
		if (ret < 6) {
			if (*ptr != '*') {
				eprintf("Could not parse line: %s\n", ptr);
				rz_strbuf_free(sb);
				return NULL;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// If name is '', then skip
		if (rz_str_startswith(name, "''")) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// If size is 0, skip
		if (size == 0) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		type_bits = 0;
		// Parse group
		if (ret >= 7) {
			gptr = groups;
			while (1) {
				if ((gptr1 = strchr(gptr, ','))) {
					*gptr1 = '\0';
				}
				if (rz_str_startswith(gptr, "general")) {
					type_bits |= gpr;
				} else if (rz_str_startswith(gptr, "all")) {
					type_bits |= all;
				} else if (rz_str_startswith(gptr, "save")) {
					type_bits |= save;
				} else if (rz_str_startswith(gptr, "restore")) {
					type_bits |= restore;
				} else if (rz_str_startswith(gptr, "float")) {
					type_bits |= float_;
				} else if (rz_str_startswith(gptr, "sse")) {
					type_bits |= sse;
				} else if (rz_str_startswith(gptr, "mmx")) {
					type_bits |= mmx;
				} else if (rz_str_startswith(gptr, "vector")) {
					type_bits |= vector;
				} else if (rz_str_startswith(gptr, "system")) {
					type_bits |= system;
				}
				if (!gptr1) {
					break;
				}
				gptr = gptr1 + 1;
			}
		}
		// If type is not defined, skip
		if (!*type) {
			if (!ptr1) {
				break;
			}
			ptr = ptr1 + 1;
			continue;
		}
		// TODO: More mappings between gdb and rizin reg groups. For now, either fpu or gpr
		if (!(type_bits & sse) && !(type_bits & float_)) {
			type_bits |= gpr;
		}
		// Print line
		rz_strbuf_appendf(sb, "%s\t%s\t.%d\t%d\t0\n",
			// Ref: Comment above about more register type mappings
			((type_bits & mmx) || (type_bits & float_) || (type_bits & sse)) ? "fpu" : "gpr",
			name, size * 8, offset);
		// Go to next line
		if (!ptr1) {
			break;
		}
		ptr = ptr1 + 1;
		continue;
	}
	return rz_strbuf_drain(sb);
}
/* ==================== end verbatim target function ====================== */

/* Direct-call driver: read argv[1] into a HEAP buffer (ASAN-guarded),
 * NUL-terminate it, and feed it as the `gdb` register-profile string.
 * gdb_to_rz_profile treats the input purely as a C string, so the whole
 * file content is the single argument -- no extra FDP slicing is needed. */
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

	/* malloc exactly len+1 so the trailing NUL sits at the last guarded byte;
	 * the input string itself is heap-owned and ASAN-instrumented. */
	char *buf = (char *)malloc((size_t)sz + 1);
	if (!buf) { fclose(f); return 64; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);
	buf[n] = '\0';

	char *out = gdb_to_rz_profile(buf);
	if (out) {
		fprintf(stderr, "ok, %zu bytes\n", strlen(out));
		free(out);
	}
	free(buf);
	return 0;
}

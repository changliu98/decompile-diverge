/* cve_barebone isolation harness for rizin CVE (pyc marshal complex-number parser).
 * Target: get_complex_object (librz/bin/format/pyc/marshal.c) -- CWE-787 heap-buffer-overflow
 * WRITE.
 *
 * The bug: n1 (and, symmetrically, n2) is read via get_st32() into an *unsigned* ut32 -- the
 * 32-bit-length marshal format is selected whenever `pyc->magic_int & 0xffff > 62061`. The code
 * then does `ut8 *s1 = malloc(n1 + 1);` with NO overflow check. When the attacker supplies
 * n1 == 0xFFFFFFFF (UT32_MAX), `n1 + 1` wraps (ut32 arithmetic) to 0, so `s1` is a 0-byte heap
 * allocation. Immediately after, `rz_buf_read(buffer, s1, n1)` is asked to copy n1 (~4G) bytes
 * into that 0-byte allocation -> heap-buffer-overflow WRITE the instant it copies the first real
 * byte past the end of s1. Fixed upstream (commit 68948017423a) by adding
 * `UT32_ADD_OVFCHK(n1, 1)` / `UT32_ADD_OVFCHK(n2, 1)` guards before each malloc.
 *
 * Everything below the target function is copied VERBATIM (real names) from the vulnerable
 * rizin tree:
 *   - get_ut8 / get_st32               librz/bin/format/pyc/marshal.c (SAME file as the target)
 *   - pyc_object, TYPE_COMPLEX,
 *     RzBinPycObj's `magic_int` field  librz/bin/format/pyc/marshal.h
 *   - rz_str_newf                      librz/util/str.c
 *   - UT32_MAX, UT32_ADD_OVFCHK        librz/include/rz_types_base.h, rz_types_overflow.h
 *   - RZ_NEW0 / RZ_FREE / RZ_API       librz/include/rz_types.h
 *
 * RzBuffer is rizin's polymorphic buffer abstraction (file/io/mmap/sparse/bytes backends,
 * librz/util/buf*.c); a .pyc parse always backs `buffer` with a plain byte array ("bytes"
 * backend), so `rz_buf_read` / `rz_buf_read_le32` below are a minimal faithful stub restricted
 * to exactly that backend's real semantics: librz/util/buf_bytes.c:buf_bytes_read computes
 * `real_len = min(length-offset, len)`, `memmove`s that many REAL bytes, and returns real_len
 * (a short read simply returns fewer bytes than requested -- no other magic, no padding). This
 * is the one piece of scaffolding that is a faithful stub rather than a verbatim copy, because
 * the real functions are generated through rizin's internal macro-templating and are themselves
 * incidental to the vulnerability (which is pure unsigned-overflow-then-oversized-copy
 * arithmetic in get_complex_object's own body).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* ---- librz/include/rz_types_base.h (verbatim macros) ---- */
#define ut64 unsigned long long
#define st64 long long
#define ut32 unsigned int
#define st32 int
#define ut16 unsigned short
#define st16 short
#define ut8  unsigned char
#define st8  signed char

#define UT32_MAX 0xFFFFFFFFU

/* ---- librz/include/rz_types_overflow.h (verbatim) ---- */
#define UT32_ADD_OVFCHK(x, y) ((UT32_MAX - (x)) < (y))

/* ---- librz/include/rz_types.h (verbatim) ---- */
#define RZ_API
#define RZ_OWN
#define RZ_NONNULL
#define RZ_NEW0(x) (x *)calloc(1, sizeof(x))
#define RZ_FREE(x) \
	{ \
		free((void *)x); \
		x = NULL; \
	}
#define rz_return_val_if_fail(expr, val) \
	do { \
		if (!(expr)) { \
			return (val); \
		} \
	} while (0)

/* ---- librz/bin/format/pyc/marshal.h (verbatim members get_complex_object touches) ---- */
typedef enum {
	TYPE_COMPLEX = 'x',
} pyc_marshal_type;

typedef struct {
	pyc_marshal_type type;
	void *data;
} pyc_object;

/* RzBinPycObj (real name = `struct pyc_context`, see marshal.h): get_complex_object reads only
 * `magic_int`; the RzList and pyc_version members are irrelevant to this bug and are omitted. */
typedef struct pyc_context {
	ut32 magic_int;
} RzBinPycObj;

/* ---- librz/include/rz_util/rz_buf.h + buf.c / buf_bytes.c: minimal faithful "bytes" backend ---- */
typedef struct rz_buffer_t {
	const ut8 *buf;
	ut64 length;
	ut64 offset;
} RzBuffer;

/* librz/util/buf_bytes.c:buf_bytes_read, wrapped exactly as librz/util/buf.c:rz_buf_read's
 * documented contract ("Read len bytes of the buffer at the cursor. Return the number of bytes
 * read.") -- short reads return the REAL byte count actually copied; every caller in this file
 * detects truncation itself by comparing the return value to the requested length. */
static st64 rz_buf_read(RzBuffer *b, ut8 *out, ut64 len) {
	ut64 real_len = (b->length < b->offset) ? 0 : (b->length - b->offset);
	if (len < real_len) {
		real_len = len;
	}
	memmove(out, b->buf + b->offset, (size_t)real_len);
	b->offset += real_len;
	return (st64)real_len;
}

/* librz/util/buf.c: rz_buf_read_ble32 (the templated le/be helper behind the
 * rz_buf_read_le32(b,result) macro in rz_buf.h) -- reads sizeof(ut32) bytes and packs them in
 * the requested endianness; success iff the full width was actually read, matching every
 * get_* caller's `if (!rz_buf_read_leN(...)) *error = true;` usage. */
static bool rz_buf_read_ble32(RzBuffer *b, ut32 *result, bool big_endian) {
	ut8 tmp[4];
	if (rz_buf_read(b, tmp, 4) != 4) {
		return false;
	}
	*result = big_endian
		? ((ut32)tmp[0] << 24 | (ut32)tmp[1] << 16 | (ut32)tmp[2] << 8 | (ut32)tmp[3])
		: ((ut32)tmp[3] << 24 | (ut32)tmp[2] << 16 | (ut32)tmp[1] << 8 | (ut32)tmp[0]);
	return true;
}
/* librz/include/rz_util/rz_buf.h:267 (verbatim macro) */
#define rz_buf_read_le32(b, result) rz_buf_read_ble32(b, result, false)

/* ---- librz/util/str.c:rz_str_newf (verbatim) ---- */
RZ_API char *rz_str_newf(const char *fmt, ...) {
	rz_return_val_if_fail(fmt, NULL);
	va_list ap, ap2;

	va_start(ap, fmt);
	if (!strchr(fmt, '%')) {
		va_end(ap);
		return strdup(fmt);
	}
	va_copy(ap2, ap);
	int ret = vsnprintf(NULL, 0, fmt, ap2);
	ret++;
	char *p = calloc(1, ret);
	if (p) {
		(void)vsnprintf(p, ret, fmt, ap);
	}
	va_end(ap2);
	va_end(ap);
	return p;
}

/* ---- librz/bin/format/pyc/marshal.c: get_ut8 / get_st32 (verbatim, same file as the target) ---- */
static ut8 get_ut8(RzBuffer *buffer, bool *error) {
	ut8 ret = 0;
	int size = rz_buf_read(buffer, &ret, sizeof(ret));
	if (size < sizeof(ret)) {
		*error = true;
	}
	return ret;
}

static st32 get_st32(RzBuffer *buffer, bool *error) {
	st32 ret = 0;
	if (!rz_buf_read_le32(buffer, (ut32 *)&ret)) {
		*error = true;
	}
	return ret;
}

/* ======================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from                             */
/*   data_cve/cve_1d5da548/target/original_function.c                      */
/* ======================================================================== */
static pyc_object *get_complex_object(RzBinPycObj *pyc, RzBuffer *buffer) {
	pyc_object *ret = NULL;
	bool error = false;
	ut32 size = 0;
	ut32 n1 = 0;
	ut32 n2 = 0;

	ret = RZ_NEW0(pyc_object);
	if (!ret) {
		return NULL;
	}

	if ((pyc->magic_int & 0xffff) <= 62061) {
		n1 = get_ut8(buffer, &error);
	} else {
		n1 = get_st32(buffer, &error);
	}
	if (error) {
		free(ret);
		return NULL;
	}
	ut8 *s1 = malloc(n1 + 1);
	if (!s1) {
		return NULL;
	}
	/* object contain string representation of the number */
	size = rz_buf_read(buffer, s1, n1);
	if (size != n1) {
		RZ_FREE(s1);
		RZ_FREE(ret);
		return NULL;
	}
	s1[n1] = '\0';

	if ((pyc->magic_int & 0xffff) <= 62061) {
		n2 = get_ut8(buffer, &error);
	} else
		n2 = get_st32(buffer, &error);
	if (error) {
		return NULL;
	}
	ut8 *s2 = malloc(n2 + 1);
	if (!s2) {
		return NULL;
	}
	/* object contain string representation of the number */
	size = rz_buf_read(buffer, s2, n2);
	if (size != n2) {
		RZ_FREE(s1);
		RZ_FREE(s2);
		RZ_FREE(ret);
		return NULL;
	}
	s2[n2] = '\0';

	ret->type = TYPE_COMPLEX;
	ret->data = rz_str_newf("%s+%sj", s1, s2);
	RZ_FREE(s1);
	RZ_FREE(s2);
	if (!ret->data) {
		RZ_FREE(ret);
		return NULL;
	}
	return ret;
}
/* ==================== end verbatim target function ====================== */

/* Direct-call driver: read argv[1] into a HEAP buffer (ASAN-guarded) and use it verbatim as the
 * body of a "bytes" RzBuffer, exactly as rizin's pyc loader does when it wraps a .pyc file's
 * bytes for marshal.c to parse. `magic_int` is fixed above the "<=62061" cutoff so n1/n2 are
 * always read via the vulnerable get_st32() 32-bit-length branch (the get_ut8() 1-byte-length
 * branch is the OTHER, non-vulnerable code path -- a 1-byte length can never make n+1 overflow
 * a ut32). */
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
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return 64;
	}
	long sz = ftell(f);
	if (sz < 0) {
		fclose(f);
		return 64;
	}
	if (fseek(f, 0, SEEK_SET) != 0) {
		fclose(f);
		return 64;
	}

	size_t alloc_sz = (sz > 0) ? (size_t)sz : 1;
	ut8 *body = (ut8 *)malloc(alloc_sz);
	if (!body) {
		fclose(f);
		return 64;
	}
	size_t n = fread(body, 1, (size_t)sz, f);
	fclose(f);

	RzBinPycObj pyc;
	memset(&pyc, 0, sizeof(pyc));
	pyc.magic_int = 62062; /* low 16 bits > 62061 -> selects the vulnerable get_st32() branch */

	RzBuffer buffer;
	buffer.buf = body;
	buffer.length = (ut64)n;
	buffer.offset = 0;

	pyc_object *obj = get_complex_object(&pyc, &buffer);
	if (obj) {
		fprintf(stderr, "ok: type=%c data=%s\n", (char)obj->type, obj->data ? (char *)obj->data : "(null)");
		free(obj->data);
		free(obj);
	} else {
		fprintf(stderr, "get_complex_object returned NULL\n");
	}
	free(body);
	return 0;
}

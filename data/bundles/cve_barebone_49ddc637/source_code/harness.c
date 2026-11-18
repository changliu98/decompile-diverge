/* cve_barebone direct-call harness for CVE-2016-8654 (jasper)
 * Target: jpc_qmfb_split_colgrp  (src/libjasper/jpc/jpc_qmfb.c)
 * Bug class: heap-buffer-overflow WRITE (CWE-787) on the heap `buf` spill path.
 *
 * Root cause (from the fix diff, jasper-software/jasper@4a59cfaf9ab3d48fca4a15c0d2674bf7138e3d1a):
 *   int bufsize = JPC_CEILDIVPOW2(numrows, 1);              // ~= numrows / 2
 *   jpc_fix_t splitbuf[QMFB_SPLITBUFSIZE * JPC_QMFB_COLGRPSIZE];  // sized for bufsize*16 elems
 *   jpc_fix_t *buf = splitbuf;
 *   if (bufsize > QMFB_SPLITBUFSIZE) {
 *       buf = jas_alloc2(bufsize, sizeof(jpc_fix_t));        // VULNERABLE: only `bufsize` elems
 *   }
 *   ... writes/reads up to `m * JPC_QMFB_COLGRPSIZE` (~bufsize*16) elements through `buf` ...
 *
 * The stack fallback (`splitbuf`) is correctly sized for `bufsize * JPC_QMFB_COLGRPSIZE`
 * elements, but once `numrows` is large enough that `bufsize > QMFB_SPLITBUFSIZE` (4096),
 * the code switches to a HEAP buffer allocated with only `bufsize` elements -- 16x
 * (JPC_QMFB_COLGRPSIZE) too small. The very next loop then writes `JPC_QMFB_COLGRPSIZE`-wide
 * blocks into `buf` for `m` (~bufsize) iterations, overflowing the heap allocation almost
 * immediately. The fix (jas_alloc3(bufsize, JPC_QMFB_COLGRPSIZE, sizeof(jpc_fix_t))) is a
 * pure allocation-size fix; jpc_qmfb_split_colgrp's own logic/loops are untouched by us.
 *
 * The function only needs three real project pieces, copied verbatim by name from
 * source_code/: the `jpc_fix_t` typedef (jpc_fix.h), the JPC_QMFB_COLGRPSIZE /
 * JPC_CEILDIVPOW2 macros (jpc_qmfb.h / jpc_math.h) and QMFB_SPLITBUFSIZE (local #define in
 * jpc_qmfb.c), and the jas_alloc2/jas_malloc/jas_free allocator trio (jas_malloc.c) --
 * reproduced here verbatim in their DEFAULT (JAS_DEFAULT_MAX_MEM_USAGE undefined, the
 * project's real default -- grepped, never #define'd anywhere in this tree) plain
 * malloc/free form, plus the jas_safe_size_mul() overflow-checked multiply jas_alloc2 calls
 * (verbatim from jas_math.h).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ==== VERBATIM (by name) from source_code/src/libjasper/jpc/jpc_fix.h ==== */
typedef int_fast32_t jpc_fix_t;

/* ==== VERBATIM (by name) from source_code/src/libjasper/jpc/jpc_qmfb.h ==== */
#define JPC_QMFB_COLGRPSIZE	16

/* ==== VERBATIM (by name) from source_code/src/libjasper/jpc/jpc_qmfb.c (local #define) ==== */
#define QMFB_SPLITBUFSIZE	4096

/* ==== VERBATIM from source_code/src/libjasper/include/jasper/jas_math.h ==== */
/* Compute the product of two size_t integers with overflow checking. */
inline static bool jas_safe_size_mul(size_t x, size_t y, size_t *result)
{
	/* Check if overflow would occur */
	if (x && y > SIZE_MAX / x) {
		/* Overflow would occur. */
		return false;
	}
	if (result) {
		*result = x * y;
	}
	return true;
}

/* ==== VERBATIM from source_code/src/libjasper/jpc/jpc_math.h ==== */
#define	JPC_CEILDIVPOW2(x, y) \
	(((x) + (1 << (y)) - 1) >> (y))

/* ==== VERBATIM from source_code/src/libjasper/base/jas_malloc.c
 * (the `#if !defined(JAS_DEFAULT_MAX_MEM_USAGE)` branch -- the project's real default;
 * JAS_DEFAULT_MAX_MEM_USAGE is never #define'd anywhere in this source tree) ==== */
void *jas_malloc(size_t size)
{
	void *result;
	result = malloc(size);
	return result;
}

void jas_free(void *ptr)
{
	free(ptr);
}

/* ==== VERBATIM from source_code/src/libjasper/base/jas_malloc.c ==== */
void *jas_alloc2(size_t num_elements, size_t element_size)
{
	size_t size;
	if (!jas_safe_size_mul(num_elements, element_size, &size)) {
		return 0;
	}
	return jas_malloc(size);
}

/* ==== VERBATIM from data_cve/cve_49ddc637/target/original_function.c ==== */
void jpc_qmfb_split_colgrp(jpc_fix_t *a, int numrows, int stride,
  int parity)
{

	int bufsize = JPC_CEILDIVPOW2(numrows, 1);
	jpc_fix_t splitbuf[QMFB_SPLITBUFSIZE * JPC_QMFB_COLGRPSIZE];
	jpc_fix_t *buf = splitbuf;
	jpc_fix_t *srcptr;
	jpc_fix_t *dstptr;
	register jpc_fix_t *srcptr2;
	register jpc_fix_t *dstptr2;
	register int n;
	register int i;
	int m;
	int hstartcol;

	/* Get a buffer. */
	if (bufsize > QMFB_SPLITBUFSIZE) {
		if (!(buf = jas_alloc2(bufsize, sizeof(jpc_fix_t)))) {
			/* We have no choice but to commit suicide in this case. */
			abort();
		}
	}

	if (numrows >= 2) {
		hstartcol = (numrows + 1 - parity) >> 1;
		// ORIGINAL (WRONG): m = (parity) ? hstartcol : (numrows - hstartcol);
		m = numrows - hstartcol;

		/* Save the samples destined for the highpass channel. */
		n = m;
		dstptr = buf;
		srcptr = &a[(1 - parity) * stride];
		while (n-- > 0) {
			dstptr2 = dstptr;
			srcptr2 = srcptr;
			for (i = 0; i < JPC_QMFB_COLGRPSIZE; ++i) {
				*dstptr2 = *srcptr2;
				++dstptr2;
				++srcptr2;
			}
			dstptr += JPC_QMFB_COLGRPSIZE;
			srcptr += stride << 1;
		}
		/* Copy the appropriate samples into the lowpass channel. */
		dstptr = &a[(1 - parity) * stride];
		srcptr = &a[(2 - parity) * stride];
		n = numrows - m - (!parity);
		while (n-- > 0) {
			dstptr2 = dstptr;
			srcptr2 = srcptr;
			for (i = 0; i < JPC_QMFB_COLGRPSIZE; ++i) {
				*dstptr2 = *srcptr2;
				++dstptr2;
				++srcptr2;
			}
			dstptr += stride;
			srcptr += stride << 1;
		}
		/* Copy the saved samples into the highpass channel. */
		dstptr = &a[hstartcol * stride];
		srcptr = buf;
		n = m;
		while (n-- > 0) {
			dstptr2 = dstptr;
			srcptr2 = srcptr;
			for (i = 0; i < JPC_QMFB_COLGRPSIZE; ++i) {
				*dstptr2 = *srcptr2;
				++dstptr2;
				++srcptr2;
			}
			dstptr += stride;
			srcptr += JPC_QMFB_COLGRPSIZE;
		}
	}

	/* If the split buffer was allocated on the heap, free this memory. */
	if (buf != splitbuf) {
		jas_free(buf);
	}

}
/* ==== end verbatim ==== */

/* ---- driver: construct jpc_qmfb_split_colgrp's arguments from the input bytes ---- */

static int32_t read_i32(const unsigned char *data, size_t sz, size_t off, int32_t defval)
{
	if (!data || off + 4 > sz)
		return defval;
	uint32_t u = (uint32_t)data[off] | ((uint32_t)data[off + 1] << 8) |
	  ((uint32_t)data[off + 2] << 16) | ((uint32_t)data[off + 3] << 24);
	return (int32_t)u;
}

static uint8_t read_u8(const unsigned char *data, size_t sz, size_t off, uint8_t defval)
{
	if (!data || off >= sz)
		return defval;
	return data[off];
}

static int clampi(int32_t v, int lo, int hi)
{
	if (v < lo)
		return lo;
	if (v > hi)
		return hi;
	return (int)v;
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the raw input file so ASAN guards it (our own scaffolding read of it
	 * is strictly bounds-checked below -- read_i32/read_u8 -- so the file buffer can never
	 * itself be the source of a fault; the only fault a triggering input can raise is the
	 * intended heap-buffer-overflow inside jpc_qmfb_split_colgrp's own `buf`). */
	unsigned char *data = NULL;
	size_t sz = (size_t)fsz;
	if (sz > 0) {
		data = (unsigned char *)malloc(sz);
		if (!data) { fclose(f); return 0; }
		size_t rd = fread(data, 1, sz, f);
		sz = rd;
	}
	fclose(f);

	/* File layout (9-byte header, little-endian):
	 *   [0..3]  int32  numrows_raw
	 *   [4..7]  int32  stride_raw
	 *   [8]     uint8  parity_raw (bit 0)
	 * Clamped (not modulo'd) into safe ranges so the harness's own array `a` -- which WE
	 * size, independent of jpc_qmfb_split_colgrp's own (buggy) internal `buf` sizing -- is
	 * always large enough for the accesses the function makes into `a` (as opposed to `buf`,
	 * where the whole point is that its internal allocation is undersized). */
	int32_t numrows_raw = read_i32(data, sz, 0, 2);
	int32_t stride_raw  = read_i32(data, sz, 4, 1);
	uint8_t parity_raw  = read_u8(data, sz, 8, 0);

	int numrows = clampi(numrows_raw, 0, 20000);
	int stride  = clampi(stride_raw, 1, 8);
	int parity  = parity_raw & 1;

	/* `a` represents the column data jpc_qmfb_split_colgrp operates in place on. Sized with
	 * generous headroom over every index the function's own loops touch for the numrows/
	 * stride ranges above (worst case ~65535 for a full-completion safe call; the triggering
	 * heap overflow inside `buf` fires within ~256 outer iterations regardless of numrows,
	 * touching only a few thousand `a` indices) -- so `a` itself is never the fault source. */
	const size_t ALEN = 200000;
	jpc_fix_t *a = (jpc_fix_t *)calloc(ALEN, sizeof(jpc_fix_t));
	if (!a) { free(data); return 0; }

	jpc_qmfb_split_colgrp(a, numrows, stride, parity);

	free(a);
	free(data);
	return 0;
}

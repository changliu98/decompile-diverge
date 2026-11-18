/*
 * Direct-call crash harness for CVE-2014-0207 (file/file, src/cdf.c:
 * cdf_read_short_sector) -- Decompile-Diverge bundle cvf_78d6981b.
 *
 * cdf_read_short_sector() is embedded VERBATIM below (byte-for-byte from
 * target/original_function.c). Everything above it is the minimal-but-real
 * subset of file's src/cdf.h / src/cdf.c that the function's body actually
 * references (real type/field/macro names, no invented placeholders).
 *
 * Root cause (real CVE-2014-0207, CWE-125 heap-buffer-overflow READ):
 * cdf_read_short_sector() is handed a "short sector container" stream
 * `sst` whose sst_tab buffer holds sst->sst_len sectors of CDF_SEC_SIZE(h)
 * bytes each (that is how the real caller, cdf_read_long_sector_chain,
 * allocates it: calloc(sst_len, CDF_SEC_SIZE(h))). The function computes
 *   pos = id * CDF_SHORT_SEC_SIZE(h)
 * and guards the read with
 *   if (pos > CDF_SEC_SIZE(h) * sst->sst_len) return -1;
 * but that guard only checks the START offset `pos`, never `pos + len`.
 * So an `id` for which `pos` lands right at (or within one short-sector of)
 * the end of the buffer passes the check, yet the following
 *   memcpy(buf + offs, sst->sst_tab + pos, len)
 * (len == CDF_SHORT_SEC_SIZE(h)) reads up to a whole short-sector's worth
 * of bytes past the end of the sst_tab allocation -> heap-buffer-overflow
 * READ, matching the baseline dedup_token
 * "__asan_memcpy--cdf_read_short_sector--cdf_read_short_sector_chain" and
 * baseline.cwe CWE-125 exactly (the memcpy is called *from*
 * cdf_read_short_sector, which itself is called from
 * cdf_read_short_sector_chain in the real crash -- here we call
 * cdf_read_short_sector directly, so the crash stack is
 * __asan_memcpy <- cdf_read_short_sector <- main).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>   /* ssize_t */
#include <assert.h>

/* ---------------------------------------------------------------------
 * Minimal faithful defs from file's src/cdf.h / src/cdf.c.
 * Field/macro names are copied verbatim; only fields unused by
 * cdf_read_short_sector's body are omitted from the structs.
 * --------------------------------------------------------------------- */

typedef int32_t cdf_secid_t;

/* cdf.h: cdf_header_t, trimmed to the two fields the target function's
 * macros (CDF_SEC_SIZE / CDF_SHORT_SEC_SIZE) actually dereference. */
typedef struct {
	uint16_t	h_sec_size_p2;
	uint16_t	h_short_sec_size_p2;
} cdf_header_t;

/* cdf.h: bounds/position macros, copied verbatim. */
#define CDF_SEC_SIZE(h) ((size_t)(1 << (h)->h_sec_size_p2))
#define CDF_SHORT_SEC_SIZE(h)	((size_t)(1 << (h)->h_short_sec_size_p2))
#define CDF_SHORT_SEC_POS(h, secid) ((secid) * CDF_SHORT_SEC_SIZE(h))

/* cdf.h: cdf_stream_t, trimmed to the two fields the target function's
 * body touches (sst->sst_tab, sst->sst_len); sst_dirlen is unused here. */
typedef struct {
	void	*sst_tab;
	size_t	sst_len;
} cdf_stream_t;

/* cdf.c: DPRINTF is compiled out (a no-op) unless CDF_DEBUG is defined,
 * which is the real release-build configuration; a no-op is faithful and
 * keeps the harness free of file's separate debug-printf plumbing. */
#define DPRINTF(a)

/* ---------------------------------------------------------------------
 * TARGET FUNCTION -- VERBATIM copy of target/original_function.c.
 * Do not modify logic, names, or signature.
 * --------------------------------------------------------------------- */

ssize_t
cdf_read_short_sector(const cdf_stream_t *sst, void *buf, size_t offs,
    size_t len, const cdf_header_t *h, cdf_secid_t id)
{
	size_t ss = CDF_SHORT_SEC_SIZE(h);
	size_t pos = CDF_SHORT_SEC_POS(h, id);
	assert(ss == len);
	if (pos > CDF_SEC_SIZE(h) * sst->sst_len) {
		DPRINTF(("Out of bounds read %" SIZE_T_FORMAT "u > %"
		    SIZE_T_FORMAT "u\n",
		    pos, CDF_SEC_SIZE(h) * sst->sst_len));
		return -1;
	}
	(void)memcpy(((char *)buf) + offs,
	    ((const char *)sst->sst_tab) + pos, len);
	return len;
}

/* ---------------------------------------------------------------------
 * Direct-call driver.
 *
 * Input file format (10 bytes, all fields chosen by the corpus generator
 * to deterministically land on either side of the buggy bounds check --
 * see gen_corpus.py):
 *   byte 0      : h_sec_size_p2        (u8)
 *   byte 1      : h_short_sec_size_p2  (u8)
 *   bytes 2..5  : sst_len              (u32 LE)
 *   bytes 6..9  : id                   (i32 LE, two's complement)
 *
 * argv[1] is read into a HEAP buffer (malloc) -- required so ASAN's
 * allocation tracking covers the raw bytes. The actual vulnerable buffer
 * that the target function over-reads, sst.sst_tab, is a SEPARATE,
 * exact-size heap allocation (calloc(sst_len, CDF_SEC_SIZE(h)), mirroring
 * exactly how the real caller cdf_read_long_sector_chain allocates it) so
 * an out-of-bounds read lands precisely in the ASAN redzone right after
 * that allocation.
 * --------------------------------------------------------------------- */

static uint32_t
clampu32(uint32_t v, uint32_t lo, uint32_t hi)
{
	if (v < lo) return lo;
	if (v > hi) return hi;
	return v;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	if (sz < 0)
		sz = 0;
	fseek(f, 0, SEEK_SET);

	size_t alloc_sz = (size_t)sz > 0 ? (size_t)sz : 1;
	unsigned char *raw = (unsigned char *)malloc(alloc_sz);
	if (!raw) {
		fclose(f);
		return 1;
	}
	size_t got = sz > 0 ? fread(raw, 1, (size_t)sz, f) : 0;
	fclose(f);

	uint8_t  sec_p2   = got > 0 ? raw[0] : 9;
	uint8_t  short_p2 = got > 1 ? raw[1] : 6;
	uint32_t sst_len_raw = 0;
	if (got >= 6)
		sst_len_raw = (uint32_t)raw[2] | ((uint32_t)raw[3] << 8) |
		    ((uint32_t)raw[4] << 16) | ((uint32_t)raw[5] << 24);
	int32_t id_raw = 0;
	if (got >= 10)
		id_raw = (int32_t)((uint32_t)raw[6] | ((uint32_t)raw[7] << 8) |
		    ((uint32_t)raw[8] << 16) | ((uint32_t)raw[9] << 24));
	free(raw);

	/* Defensive clamps (no-ops for every value gen_corpus.py actually
	 * emits) so a malformed/short file can never itself misbehave --
	 * only the target function's own logic decides crash vs. clean. */
	sec_p2 = (uint8_t)clampu32(sec_p2, 4, 16);
	short_p2 = (uint8_t)clampu32(short_p2, 2, 14);
	uint32_t sst_len32 = clampu32(sst_len_raw, 1, 4096);

	cdf_header_t h;
	h.h_sec_size_p2 = sec_p2;
	h.h_short_sec_size_p2 = short_p2;

	size_t sec_size = CDF_SEC_SIZE(&h);
	size_t ss = CDF_SHORT_SEC_SIZE(&h);
	size_t sst_len = (size_t)sst_len32;

	cdf_stream_t sst;
	sst.sst_len = sst_len;
	/* Exact-size heap allocation, matching the real
	 * cdf_read_long_sector_chain: calloc(sst_len, CDF_SEC_SIZE(h)). */
	sst.sst_tab = calloc(sst_len, sec_size);
	if (sst.sst_tab == NULL) {
		fprintf(stderr, "calloc(sst_tab) failed\n");
		return 1;
	}

	void *buf = malloc(ss);
	if (!buf) {
		free(sst.sst_tab);
		return 1;
	}

	cdf_secid_t id = (cdf_secid_t)id_raw;

	ssize_t r = cdf_read_short_sector(&sst, buf, 0, ss, &h, id);

	/* Consume buf's contents so the optimizer cannot treat the memcpy's
	 * destination write (and therefore the whole call, including its
	 * source READ) as a dead store and elide it -- without this, -O1
	 * after inlining silently drops the OOB read entirely because `buf`
	 * is otherwise never observed before being freed. */
	unsigned csum = 0;
	unsigned char *bb = (unsigned char *)buf;
	for (size_t i = 0; i < ss; i++)
		csum = csum * 131u + bb[i];

	fprintf(stderr,
	    "cdf_read_short_sector -> %zd csum=%u (sec_size_p2=%u short_sec_size_p2=%u "
	    "sst_len=%zu bound=%zu ss=%zu id=%d)\n",
	    (ssize_t)r, csum, sec_p2, short_p2, sst_len, sec_size * sst_len, ss,
	    (int)id);

	free(buf);
	free(sst.sst_tab);
	return 0;
}

/*
 * cve_f19e560f direct-call crash harness for ImageWorsener's
 * iwjpeg_scan_exif_ifd()  (CVE-2017-9207 / CWE-125 heap-buffer-overflow READ
 * in iw_get_ui16_e(), called from iwjpeg_scan_exif_ifd, called from
 * iwjpeg_scan_exif -- baseline dedup_token
 * "iw_get_ui16_e--iwjpeg_scan_exif_ifd--iwjpeg_scan_exif").
 *
 * Root cause (visible directly in target/original_function.c, unchanged):
 *
 *     if(ifd<8 || ifd>e->d_len-18) return;
 *     tag_count = iw_get_ui16_e(&e->d[ifd],e->endian);   <-- BUG (first OOB read)
 *
 *   e->d_len is a size_t. When the Exif payload is short (d_len < 18),
 *   "e->d_len - 18" UNDERFLOWS to a huge unsigned value, so the upper-bound
 *   guard "ifd > e->d_len-18" is always false and any ifd >= 8 slips through.
 *   iw_get_ui16_e() then reads e->d[ifd] / e->d[ifd+1] past the end of the
 *   short heap buffer -> heap-buffer-overflow READ (CWE-125). This is exactly
 *   the shape of the original PoC (Exif payload "II*\0" + a 32-bit IFD offset
 *   of 0xC8 = 200 pointing far past an 8-byte payload); here we drive the same
 *   bug with the read landing just past the end of the malloc'd payload so
 *   ASAN's right-redzone flags it deterministically.
 *
 * This file assembles, in order:
 *   1. Minimal REAL type vocabulary copied from source_code/ (real names):
 *        - iw_byte / iw_uint32 / iw_int32 / iw_uint16 macros (imagew.h 353-356),
 *        - IW_ENDIAN_BIG / IW_ENDIAN_LITTLE (imagew.h 804-805),
 *        - IW_IMPL() (expands to just the return type in this standalone TU),
 *        - struct iw_exif_state (imagew-jpeg.c, verbatim),
 *        - struct iwjpegrcontext, trimmed to the four exif_* fields the
 *          isolated function actually dereferences (real field names/types;
 *          the leading libjpeg-specific fields -- struct jpeg_source_mgr pub,
 *          struct iw_context *ctx, struct iw_iodescr *iodescr, JOCTET *buffer,
 *          size_t buffer_len, int is_jfif -- are never touched by
 *          iwjpeg_scan_exif_ifd / iwjpeg_scan_exif so they are omitted rather
 *          than dragging in jpeglib.h).
 *   2. REAL callees copied verbatim from source_code/:
 *        iw_get_ui16le/iw_get_ui16be/iw_get_ui32le/iw_get_ui32be (imagew-util.c),
 *        iw_get_ui16_e/iw_get_ui32_e (imagew-util.c), iw_zeromem (imagew-util.c),
 *        get_exif_tag_int_value/get_exif_tag_dbl_value (imagew-jpeg.c).
 *   3. VERBATIM target: target/original_function.c byte-for-byte.
 *   4. REAL caller iwjpeg_scan_exif() verbatim (imagew-jpeg.c) so the crash
 *      stack is iw_get_ui16_e <- iwjpeg_scan_exif_ifd <- iwjpeg_scan_exif <-
 *      main, matching the baseline dedup family.
 *   5. main(): reads argv[1] into a HEAP buffer (malloc, so ASAN guards it) and
 *      calls iwjpeg_scan_exif() on it exactly as the real marker walker does
 *      (this derives e and ifd from the input bytes the same way the program
 *      does -- FDP-style).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- imagew.h lines 353-356, verbatim (the stdint variant) ---- */
#define iw_byte     uint8_t
#define iw_uint16   uint16_t
#define iw_int32    int32_t
#define iw_uint32   uint32_t

/* ---- imagew.h lines 804-805, verbatim ---- */
#define IW_ENDIAN_BIG    0
#define IW_ENDIAN_LITTLE 1

/* IW_IMPL wraps the return type of exported functions in the real build; in
 * this single self-contained TU it is just the return type. */
#define IW_IMPL(t) t

/* ---- imagew-jpeg.c, verbatim ---- */
struct iw_exif_state {
	int endian;
	const iw_byte *d;
	size_t d_len;
};

/* ---- imagew-jpeg.c struct iwjpegrcontext, trimmed to the exif_* fields the
 * isolated function touches (real names/types) ---- */
struct iwjpegrcontext {
	unsigned int exif_orientation; // 0 means not set
	double exif_density_x, exif_density_y; // -1.0 means not set.
	unsigned int exif_density_unit; // 0 means not set
};

/* ---- imagew-util.c, verbatim: low-level byte readers ---- */
IW_IMPL(unsigned int) iw_get_ui16le(const iw_byte *b)
{
	return (unsigned int)b[0] | ((unsigned int)b[1]<<8);
}

IW_IMPL(unsigned int) iw_get_ui32le(const iw_byte *b)
{
	return (unsigned int)b[0] | ((unsigned int)b[1]<<8) |
		((unsigned int)b[2]<<16) | ((unsigned int)b[3]<<24);
}

IW_IMPL(unsigned int) iw_get_ui16be(const iw_byte *b)
{
	return ((unsigned int)b[0]<<8) | (unsigned int)b[1];
}

IW_IMPL(unsigned int) iw_get_ui32be(const iw_byte *b)
{
	return ((unsigned int)b[0]<<24) | ((unsigned int)b[1]<<16) |
		((unsigned int)b[2]<<8) | (unsigned int)b[3];
}

// Accepts a flag indicating the endianness.
IW_IMPL(unsigned int) iw_get_ui16_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui16le(b);
	return iw_get_ui16be(b);
}

IW_IMPL(unsigned int) iw_get_ui32_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui32le(b);
	return iw_get_ui32be(b);
}

IW_IMPL(void) iw_zeromem(void *mem, size_t n)
{
	memset(mem,0,n);
}

/* ---- imagew-jpeg.c, verbatim: Exif tag value helpers (called by target) ---- */
// Try to read an Exif tag into an integer.
// Returns zero on failure.
static int get_exif_tag_int_value(struct iw_exif_state *e, unsigned int tag_pos,
	unsigned int *pv)
{
	unsigned int field_type;
	unsigned int value_count;

	field_type = iw_get_ui16_e(&e->d[tag_pos+2],e->endian);
	value_count = iw_get_ui32_e(&e->d[tag_pos+4],e->endian);

	if(value_count!=1) return 0;

	if(field_type==3) { // SHORT (uint16)
		*pv = iw_get_ui16_e(&e->d[tag_pos+8],e->endian);
		return 1;
	}
	else if(field_type==4) { // LONG (uint32)
		*pv = iw_get_ui32_e(&e->d[tag_pos+8],e->endian);
		return 1;
	}

	return 0;
}

// Read an Exif tag into a double.
// This only supports the case where the tag contains exactly one Rational value.
static int get_exif_tag_dbl_value(struct iw_exif_state *e, unsigned int tag_pos,
	double *pv)
{
	unsigned int field_type;
	unsigned int value_count;
	unsigned int value_pos;
	unsigned int numer, denom;

	field_type = iw_get_ui16_e(&e->d[tag_pos+2],e->endian);
	value_count = iw_get_ui32_e(&e->d[tag_pos+4],e->endian);

	if(value_count!=1) return 0;

	if(field_type!=5) return 0; // 5=Rational (two uint32's)

	// A rational is 8 bytes. Since 8>4, it is stored indirectly. First, read
	// the location where it is stored.

	value_pos = iw_get_ui32_e(&e->d[tag_pos+8],e->endian);
	if(value_pos > e->d_len-8) return 0;

	// Read the actual value.
	numer = iw_get_ui32_e(&e->d[value_pos  ],e->endian);
	denom = iw_get_ui32_e(&e->d[value_pos+4],e->endian);
	if(denom==0) return 0;

	*pv = ((double)numer)/denom;
	return 1;
}

/* ==================================================================
 * verbatim target function -- data_cve/cve_f19e560f/target/original_function.c
 * ================================================================== */
static void iwjpeg_scan_exif_ifd(struct iwjpegrcontext *rctx,
	struct iw_exif_state *e, iw_uint32 ifd)
{
	unsigned int tag_count;
	unsigned int i;
	unsigned int tag_pos;
	unsigned int tag_id;
	unsigned int v;
	double v_dbl;

	if(ifd<8 || ifd>e->d_len-18) return;

	tag_count = iw_get_ui16_e(&e->d[ifd],e->endian);
	if(tag_count>1000) return; // Sanity check.

	for(i=0;i<tag_count;i++) {
		tag_pos = ifd+2+i*12;
		if(tag_pos+12 > e->d_len) return; // Avoid overruns.
		tag_id = iw_get_ui16_e(&e->d[tag_pos],e->endian);

		switch(tag_id) {
		case 274: // 274 = Orientation
			if(get_exif_tag_int_value(e,tag_pos,&v)) {
				rctx->exif_orientation = v;
			}
			break;

		case 296: // 296 = ResolutionUnit
			if(get_exif_tag_int_value(e,tag_pos,&v)) {
				rctx->exif_density_unit = v;
			}
			break;

		case 282: // 282 = XResolution
			if(get_exif_tag_dbl_value(e,tag_pos,&v_dbl)) {
				rctx->exif_density_x = v_dbl;
			}
			break;

		case 283: // 283 = YResolution
			if(get_exif_tag_dbl_value(e,tag_pos,&v_dbl)) {
				rctx->exif_density_y = v_dbl;
			}
			break;
		}
	}
}
/* ==================================================================
 * end of verbatim target function
 * ================================================================== */

/* ---- imagew-jpeg.c, verbatim: the REAL caller that derives e + ifd from the
 * raw Exif payload and invokes the target ---- */
static void iwjpeg_scan_exif(struct iwjpegrcontext *rctx,
		const iw_byte *d, size_t d_len)
{
	struct iw_exif_state e;
	iw_uint32 ifd;

	if(d_len<8) return;

	iw_zeromem(&e,sizeof(struct iw_exif_state));
	e.d = d;
	e.d_len = d_len;

	e.endian = d[0]=='I' ? IW_ENDIAN_LITTLE : IW_ENDIAN_BIG;

	ifd = iw_get_ui32_e(&d[4],e.endian);

	iwjpeg_scan_exif_ifd(rctx,&e,ifd);
}

int main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	size_t n;
	iw_byte *buf;
	struct iwjpegrcontext rctx;

	if(argc<2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	f = fopen(argv[1], "rb");
	if(!f) { perror("fopen"); return 1; }
	if(fseek(f, 0, SEEK_END)!=0) { fclose(f); return 1; }
	fsz = ftell(f);
	if(fsz<0) fsz = 0;
	if(fseek(f, 0, SEEK_SET)!=0) { fclose(f); return 1; }

	/* attacker data MUST live on the heap so ASAN instruments it; the
	 * allocation length IS the Exif payload length (mirrors the real
	 * captured-marker buffer whose length == the payload length). */
	buf = (iw_byte *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if(!buf) { fclose(f); return 1; }

	n = fsz>0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&rctx, 0, sizeof(rctx));

	/* Exactly the real marker-walker call: d = the Exif payload, d_len = its
	 * length. iwjpeg_scan_exif() reads the endian byte + the 32-bit IFD
	 * offset from the payload and calls iwjpeg_scan_exif_ifd(). */
	iwjpeg_scan_exif(&rctx, buf, n);

	free(buf);
	return 0;
}

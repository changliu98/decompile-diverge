// cve_barebone isolation harness for CVE-2017-9205 (imageworsener)
// Target: iwjpeg_scan_exif_ifd  (src/imagew-jpeg.c) -- CWE-476 wild-read SEGV
// Bug: `if(ifd<8 || ifd>e->d_len-18) return;` -- e->d_len is size_t, so for
// d_len in [8,17] the subtraction underflows and the guard is bypassed, letting
// iw_get_ui16_e(&e->d[ifd], ...) read at an attacker-chosen huge offset.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ---- real typedefs / macros from src/imagew.h ----
#define iw_byte     uint8_t
#define iw_uint16   uint16_t
#define iw_int32    int32_t
#define iw_uint32   uint32_t
#define IW_ENDIAN_BIG    0
#define IW_ENDIAN_LITTLE 1

// ---- minimal real-named foreign types (jpeglib / iw internals; never touched
// by the target function, kept only so struct iwjpegrcontext is faithful) ----
typedef unsigned char JOCTET;
struct iw_context;
struct iw_iodescr;
struct jpeg_source_mgr {
	const unsigned char *next_input_byte;
	size_t bytes_in_buffer;
};

// ---- real struct definitions (verbatim from src/imagew-jpeg.c) ----
struct iwjpegrcontext {
	struct jpeg_source_mgr pub; // This field must be first.
	struct iw_context *ctx;
	struct iw_iodescr *iodescr;
	JOCTET *buffer;
	size_t buffer_len;
	int is_jfif;
	unsigned int exif_orientation; // 0 means not set
	double exif_density_x, exif_density_y; // -1.0 means not set.
	unsigned int exif_density_unit; // 0 means not set
};

struct iw_exif_state {
	int endian;
	const iw_byte *d;
	size_t d_len;
};

// ---- real helper functions (verbatim from src/imagew-util.c) ----
unsigned int iw_get_ui16le(const iw_byte *b)
{
	return (unsigned int)b[0] | ((unsigned int)b[1]<<8);
}

unsigned int iw_get_ui32le(const iw_byte *b)
{
	return (unsigned int)b[0] | ((unsigned int)b[1]<<8) |
		((unsigned int)b[2]<<16) | ((unsigned int)b[3]<<24);
}

unsigned int iw_get_ui16be(const iw_byte *b)
{
	return ((unsigned int)b[0]<<8) | (unsigned int)b[1];
}

unsigned int iw_get_ui32be(const iw_byte *b)
{
	return ((unsigned int)b[0]<<24) | ((unsigned int)b[1]<<16) |
		((unsigned int)b[2]<<8) | (unsigned int)b[3];
}

// Accepts a flag indicating the endianness.
unsigned int iw_get_ui16_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui16le(b);
	return iw_get_ui16be(b);
}

unsigned int iw_get_ui32_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui32le(b);
	return iw_get_ui32be(b);
}

// ---- real callees (verbatim from src/imagew-jpeg.c) ----
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

// ================= TARGET FUNCTION (verbatim) =================
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

// ============== end verbatim target function ==============

// Faithful re-implementation of the real caller iwjpeg_scan_exif's setup:
// the input file IS the Exif data blob `d`. main derives endian + ifd exactly
// as iwjpeg_scan_exif does, then drives iwjpeg_scan_exif_ifd directly.
int main(int argc, char **argv)
{
	if(argc<2) { fprintf(stderr,"usage: %s <input>\n",argv[0]); return 2; }

	FILE *fp = fopen(argv[1],"rb");
	if(!fp) { fprintf(stderr,"cannot open %s\n",argv[1]); return 2; }
	fseek(fp,0,SEEK_END);
	long sz = ftell(fp);
	fseek(fp,0,SEEK_SET);
	if(sz<0) sz=0;
	size_t d_len = (size_t)sz;

	// HEAP-allocate the Exif blob so ASAN guards the over-read.
	iw_byte *d = (iw_byte*)malloc(d_len ? d_len : 1);
	if(!d) { fclose(fp); return 2; }
	if(d_len) {
		if(fread(d,1,d_len,fp)!=d_len) { fclose(fp); free(d); return 2; }
	}
	fclose(fp);

	struct iwjpegrcontext rctx;
	memset(&rctx,0,sizeof(rctx));
	rctx.exif_density_x = -1.0;
	rctx.exif_density_y = -1.0;

	struct iw_exif_state e;
	memset(&e,0,sizeof(e));
	e.d = d;
	e.d_len = d_len;

	// iwjpeg_scan_exif: endian from d[0], ifd = ui32 at bytes[4..7].
	int endian = IW_ENDIAN_BIG;
	iw_uint32 ifd = 0;
	if(d_len>=1) endian = (d[0]=='I') ? IW_ENDIAN_LITTLE : IW_ENDIAN_BIG;
	e.endian = endian;
	if(d_len>=8) ifd = iw_get_ui32_e(&d[4],endian);

	iwjpeg_scan_exif_ifd(&rctx,&e,ifd);

	// Consume the results so nothing is optimized away.
	fprintf(stderr,"orient=%u unit=%u dx=%f dy=%f\n",
		rctx.exif_orientation, rctx.exif_density_unit,
		rctx.exif_density_x, rctx.exif_density_y);

	free(d);
	return 0;
}

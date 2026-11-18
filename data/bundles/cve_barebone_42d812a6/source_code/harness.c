/* cve_barebone direct-call harness for CVE (gpac)
 * Target: MPEG12_ParseSeqHdr  (src/media_tools/mpeg2_ps.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * Fix commit 3ec93d73d048ed7b46fe6e9f307cc7a0cc13db63 adds:
 *     if (buflen<6) return found;
 * right after `*have_mpeg2 = 0;` and before `buflen -= 6;`. Without that guard,
 * calling MPEG12_ParseSeqHdr with buflen < 6 makes the unsigned subtraction
 * `buflen -= 6` UNDERFLOW (buflen is `u32`) to a huge value (e.g. buflen=0 ->
 * 0xFFFFFFFA), so the `for (ix = 0; ix < buflen; ix++, pbuffer++)` loop keeps
 * reading `pbuffer[0..3]` far past the small input buffer -> heap-buffer-overflow
 * READ, almost immediately (within the first few iterations for any buflen<6).
 *
 * The vulnerable function only depends on primitive gpac scalar typedefs (u32/
 * s32/Double), 4 start-code #defines, the SEQ_ID enum-ish constant, and the
 * static frame-rate lookup table -- all copied verbatim (real names) from
 * src/media_tools/mpeg2_ps.c / mpeg2_ps.h. No project callees are invoked.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ==== real gpac scalar typedefs (include/gpac/setup.h) ==== */
typedef unsigned int u32;
typedef int s32;
typedef double Double;

/* ==== real start-code / id constants (src/media_tools/mpeg2_ps.h + mpeg2_ps.c) ==== */
#define MPEG12_PICTURE_START_CODE         0x00000100
#define MPEG12_SEQUENCE_START_CODE        0x000001b3
#define MPEG12_EXT_START_CODE             0x000001b5
#define SEQ_ID 1

/* ==== verbatim from src/media_tools/mpeg2_ps.c (static table feeding the fn) ==== */
static Double mpeg12_frame_rate_table[16] =
{
	0.0,   /* Pad */
	24000.0/1001.0,       /* Official frame rates */
	24.0,
	25.0,
	30000.0/1001.0,
	30.0,
	50.0,
	((60.0*1000.0)/1001.0),
	60.0,

	1,                    /* Unofficial economy rates */
	5,
	10,
	12,
	15,
	0,
	0,
};

/* ==== VERBATIM from data_cve/cve_42d812a6/target/original_function.c ==== */
int MPEG12_ParseSeqHdr(unsigned char *pbuffer, u32 buflen, s32 *have_mpeg2, u32 *height, u32 *width,
                       Double *frame_rate, Double *bitrate, u32 *aspect_ratio)
{
	u32 aspect_code;
	u32 framerate_code;
	u32 bitrate_int;
	u32 bitrate_ext;
	u32 scode, ix;
	s32 found = -1;
	*have_mpeg2 = 0;
	buflen -= 6;
	bitrate_int = 0;
	for (ix = 0; ix < buflen; ix++, pbuffer++) {
		scode = ((u32)pbuffer[0] << 24) | (pbuffer[1] << 16) | (pbuffer[2] << 8) |
		        pbuffer[3];

		if (scode == MPEG12_SEQUENCE_START_CODE) {
			pbuffer += sizeof(u32);
			*width = (pbuffer[0]);
			*width <<= 4;
			*width |= ((pbuffer[1] >> 4) &0xf);
			*height = (pbuffer[1] & 0xf);
			*height <<= 8;
			*height |= pbuffer[2];
			aspect_code = (pbuffer[3] >> 4) & 0xf;
			if (aspect_ratio != NULL) {
				u32 par = 0;
				switch (aspect_code) {
				default:
					*aspect_ratio = 0;
					break;
				case 2:
					par = 4;
					par<<=16;
					par |= 3;
					break;
				case 3:
					par = 16;
					par<<=16;
					par |= 9;
					break;
				case 4:
					par = 2;
					par<<=16;
					par |= 21;
					break;
				}
				*aspect_ratio = par;
			}


			framerate_code = pbuffer[3] & 0xf;
			*frame_rate = mpeg12_frame_rate_table[framerate_code];
			// 18 bits
			bitrate_int = (pbuffer[4] << 10) |
			              (pbuffer[5] << 2) |
			              ((pbuffer[6] >> 6) & 0x3);
			*bitrate = bitrate_int;
			*bitrate *= 400.0;
			ix += sizeof(u32) + 7;
			pbuffer += 7;
			found = 0;
		} else if (found == 0) {
			if (scode == MPEG12_EXT_START_CODE) {
				pbuffer += sizeof(u32);
				ix += sizeof(u32);
				switch ((pbuffer[0] >> 4) & 0xf) {
				case SEQ_ID:
					*have_mpeg2 = 1;
					*height = ((pbuffer[1] & 0x1) << 13) |
					          ((pbuffer[2] & 0x80) << 5) |
					          (*height & 0x0fff);
					*width = (((pbuffer[2] >> 5) & 0x3) << 12) | (*width & 0x0fff);
					bitrate_ext = (pbuffer[2] & 0x1f) << 7;
					bitrate_ext |= (pbuffer[3] >> 1) & 0x7f;
					bitrate_int |= (bitrate_ext << 18);
					*bitrate = bitrate_int;
					*bitrate *= 400.0;
					break;
				default:
					break;
				}
				pbuffer++;
				ix++;
			} else if (scode == MPEG12_PICTURE_START_CODE) {
				return found;
			}
		}
	}
	return found;
}
/* ==== end verbatim ==== */

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;
	FILE* f = fopen(argv[1], "rb");
	if (!f)
		return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return 0; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the input EXACTLY at the file's size (no guard padding): the
	 * bug under test is `buflen` (== the caller's byte-count for the chunk, here
	 * the file size) underflowing when < 6, so the buffer's true extent must be
	 * exactly `buflen` bytes for the OOB read to be unambiguously attributable to
	 * that underflow, not to any padding slack. Inputs are always >=1 byte (see
	 * corpus generation) so plain malloc(sz) is unambiguous under ASAN. */
	if (sz == 0) { fclose(f); return 0; }
	unsigned char* buf = (unsigned char*)malloc((size_t)sz);
	if (!buf) { fclose(f); return 0; }
	size_t n = fread(buf, 1, (size_t)sz, f);
	fclose(f);

	u32 buflen = (u32)n;
	s32 have_mpeg2 = 0;
	u32 height = 0, width = 0, aspect_ratio = 0;
	Double frame_rate = 0.0, bitrate = 0.0;

	int r = MPEG12_ParseSeqHdr(buf, buflen, &have_mpeg2, &height, &width,
	                            &frame_rate, &bitrate, &aspect_ratio);
	fprintf(stderr, "ok r=%d have_mpeg2=%d w=%u h=%u\n", r, have_mpeg2, width, height);

	free(buf);
	return 0;
}

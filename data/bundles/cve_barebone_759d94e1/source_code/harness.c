/* cve_barebone direct-call harness for cve_759d94e1 (gpac)
 * Target: latm_dmx_process  (src/filters/reframe_latm.c, GF_Err latm_dmx_process(GF_Filter *filter))
 * CVE-2021-30199. Bug class: NULL-pointer dereference (CWE-476).
 *
 * fix_commit b2db2f99b4c30f96e17b9a14537c776da6cb5dca moved
 *     data = (char *) gf_filter_pck_get_data(pck, &pck_size);
 * from unconditionally-after the `if (!pck) {...}` guard into that guard's own
 * `else` branch (pck != NULL only), and initialized data=NULL / pck_size=0.
 *
 * Root cause -- entirely inside latm_dmx_process's own body: pck = gf_filter_pid_
 * get_packet(...) can legitimately be NULL (no new packet ready this call). The
 * `if (!pck) {...}` block only RETURNS early in two of its three sub-cases:
 *   (a) input pid not yet at EOS                       -> return GF_OK;
 *   (b) EOS reached AND no bytes left buffered          -> return GF_EOS;
 * The THIRD sub-case -- EOS reached, no new packet, but a PREVIOUS call already left
 * `ctx->latm_buffer_size` unconsumed bytes pending in ctx->latm_buffer -- falls out
 * of every nested `if` with no return at all, straight into:
 *     data = (char *) gf_filter_pck_get_data(pck, &pck_size);
 * still holding pck==NULL. gf_filter_pck_get_data() (filter_core/filter_pck.c)
 * dereferences its argument unconditionally (`pck = pck->pck;`) -- a direct, one-hop
 * NULL read caused entirely by latm_dmx_process's own missing guard on that third
 * sub-case. Reproduced here by copying that getter verbatim (it IS the crash site).
 *
 * This harness drives exactly that state machine (is-EOS / has-buffered-bytes /
 * in_error) from the input file; it needs no real LATM/LOAS bitstream parsing at all
 * -- the crash fires before latm_dmx_process ever touches the bitstream layer, so
 * every bitstream/packet-output callee below this comment is unreached dead-link
 * scaffolding (real signatures, minimal bodies).
 *
 * Single-TU DCE note: on the exact path this corpus drives, latm_dmx_process's own
 * `data`/`pck_size` locals (the results of the crash-site call) are never read
 * afterwards (their one use is gated behind `if (pck && ...)`, and pck is statically
 * NULL on this path) -- so a *single-file* build can see straight through the call
 * and prove its results dead, then legally delete the whole (non-volatile,
 * "side-effect-free") NULL dereference as dead code. In the real codebase
 * gf_filter_pck_get_data lives in a SEPARATE translation unit (filter_pck.c) from
 * latm_dmx_process (reframe_latm.c), so without LTO the compiler never gets that
 * visibility and the load genuinely executes and faults -- which is the actual,
 * reported CVE. gf_filter_pck_get_data's copy below routes its one dereference
 * through a `volatile`-qualified pointer purely to restore that real-build opacity
 * (forces the load to execute exactly as written, cannot be proven dead/elided) --
 * it does not change which bytes are read or add any behavior beyond what the
 * verbatim getter already does.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#define NDEBUG   /* disable assert() so the getter's real NULL-deref SEGVs instead of
                  * tripping its own defensive assert(pck) first -- matches -DNDEBUG
                  * release/fuzzing configs (configure: debuginfo=no -> -DNDEBUG) and
                  * surfaces the actual memory fault the fix commit addresses. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define GF_EXPORT

/* ---- gpac/setup.h: base scalar types & Bool (real names) ---- */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int s32;
typedef long long s64;
typedef short s16;
typedef double Double;
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;

/* gpac/setup.h */
typedef struct { s64 num; u64 den; } GF_Fraction64;

/* gpac/tools.h GF_Err -- only the values latm_dmx_process's own body can produce */
typedef enum {
	GF_EOS       = 1,
	GF_OK        = 0,
	GF_BAD_PARAM = -1
} GF_Err;

/* gpac/filters.h */
#define GF_FILTER_NO_TS 0xFFFFFFFFFFFFFFFFUL

/* gpac/filters.h opaque core objects -- latm_dmx_process only ever passes these
 * around by pointer, it never dereferences a GF_FilterPid/GF_BitStream itself. */
typedef struct __gf_filter GF_Filter;
typedef struct __gf_filter_pid GF_FilterPid;
typedef struct __tag_bitstream GF_BitStream;   /* gpac/bitstream.h, kept opaque */

/* filter_core/filter_session.h struct __gf_filter -- trimmed to the one field
 * gf_filter_get_udta() (copied verbatim below) actually reads. */
struct __gf_filter {
	void *filter_udta;
};

/* filter_core/filter_session.h struct __gf_filter_pck -- trimmed to the fields
 * gf_filter_pck_get_data() (copied verbatim below, THE crash site) reads. The bug
 * fires on pck==NULL before any field is touched, so a live packet's exact layout
 * is never exercised by this corpus. */
struct __gf_filter_pck {
	struct __gf_filter_pck *pck;   /* real field name: "this object" */
	char *data;
	u32 data_length;
};
typedef struct __gf_filter_pck GF_FilterPacket;

/* gpac/avparse.h GF_M4ADecSpecInfo -- trimmed to the one field latm_dmx_process reads
 * (base_object_type); only touched inside the while() loop, past every return point
 * this corpus exercises. */
typedef struct {
	u32 base_object_type;
} GF_M4ADecSpecInfo;

/* gpac/avparse.h, verbatim */
static const u32 GF_M4ASampleRates[] =
{
	96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
	16000, 12000, 11025, 8000, 7350, 0, 0, 0
};

/* gpac/filters.h GF_FilterSAPType, verbatim */
typedef enum
{
	GF_FILTER_SAP_NONE = 0,
	GF_FILTER_SAP_1,
	GF_FILTER_SAP_2,
	GF_FILTER_SAP_3,
	GF_FILTER_SAP_4,
	GF_FILTER_SAP_4_PROL
} GF_FilterSAPType;

#define GF_BITSTREAM_READ 0
#define GF_CODECID_USAC 0x75736163U  /* GF_4CC('u','s','a','c') */

/* src/filters/reframe_latm.c, verbatim (top of file) */
typedef struct
{
	u64 pos;
	Double duration;
} LATMIdx;

/* src/filters/reframe_latm.c, verbatim */
typedef struct
{
	//filter args
	u32 frame_size;
	Double index;

	//only one input pid declared
	GF_FilterPid *ipid;
	//only one output pid declared
	GF_FilterPid *opid;

	GF_BitStream *bs;
	u64 file_pos, cts;
	u32 sr_idx, nb_ch, base_object_type;
	GF_Fraction64 duration;
	Double start_range;
	Bool in_seek;
	u32 timescale;

	GF_M4ADecSpecInfo acfg;

	char *latm_buffer;
	u32 latm_buffer_size, latm_buffer_alloc;
	u32 dts_inc;

	Bool is_playing;
	Bool is_file, file_loaded;
	Bool initial_play_done;

	GF_FilterPacket *src_pck;

	LATMIdx *indexes;
	u32 index_alloc_size, index_size;
	u32 resume_from;

	Bool prev_sap;
	u32 bitrate;
	GF_Err in_error;
} GF_LATMDmxCtx;

/* ---- harness-controlled upstream-pid state: this IS "constructing the arguments" --
 * the two knobs a real filter session would drive latm_dmx_process's caller with. ---- */
static Bool g_pid_is_eos = GF_TRUE;
static GF_FilterPacket *g_next_pck = NULL;   /* harness never hands back a fresh packet */

/* filter_core/filter.c gf_filter_get_udta(), verbatim */
GF_EXPORT
void *gf_filter_get_udta(GF_Filter *filter)
{
	assert(filter);
	return filter->filter_udta;
}

/* filter_core/filter_pid.c gf_filter_pid_get_packet() -- real signature; body is the
 * harness knob described above (incidental to the bug: not the crash site). */
GF_EXPORT
GF_FilterPacket *gf_filter_pid_get_packet(GF_FilterPid *PID)
{
	(void) PID;
	return g_next_pck;
}

/* filter_core/filter_pid.c gf_filter_pid_is_eos() -- real signature; body is the
 * harness knob described above (incidental to the bug: not the crash site). */
GF_EXPORT
Bool gf_filter_pid_is_eos(GF_FilterPid *PID)
{
	(void) PID;
	return g_pid_is_eos;
}

/* filter_core/filter_pck.c gf_filter_pck_get_data() -- THE CRASH SITE: dereferences
 * pck unconditionally. Logically verbatim; the one dereference is routed through a
 * volatile-qualified pointer so a single-TU build can't prove it dead and delete it
 * (see the header comment's "Single-TU DCE note" -- the real, separately-compiled
 * codebase never has that visibility, so this restores its behavior, it changes
 * nothing about which bytes are read). */
GF_EXPORT
const u8 *gf_filter_pck_get_data(GF_FilterPacket *pck, u32 *size)
{
	assert(pck);
	assert(size);
	//get true packet pointer
	volatile GF_FilterPacket *vpck = pck;
	pck = (GF_FilterPacket *) vpck->pck;
	*size = pck->data_length;
	return (const char *)pck->data;
}

/* ---- everything below this line is NEVER reached by this harness's corpus: every
 * input either returns before reaching any of these, or crashes at
 * gf_filter_pck_get_data() above. Kept only so the pasted function links -- minimal,
 * real-signature stand-ins for the rest of the filter/bitstream API surface. ---- */

void *gf_realloc(void *ptr, size_t size) { return realloc(ptr, size); }

GF_EXPORT
void gf_filter_pid_set_eos(GF_FilterPid *PID) { (void) PID; }

GF_EXPORT
void gf_filter_pck_unref(GF_FilterPacket *pck) { (void) pck; }

GF_EXPORT
void gf_filter_pid_drop_packet(GF_FilterPid *PID) { (void) PID; }

GF_EXPORT
GF_Err gf_filter_pck_ref_props(GF_FilterPacket **pck) { (void) pck; return GF_OK; }

GF_EXPORT
u64 gf_filter_pck_get_cts(GF_FilterPacket *pck) { (void) pck; return 0; }

GF_EXPORT
GF_FilterPacket *gf_filter_pck_new_alloc(GF_FilterPid *PID, u32 data_size, u8 **data)
{ (void) PID; (void) data_size; if (data) *data = NULL; return NULL; }

GF_EXPORT
GF_Err gf_filter_pck_merge_properties(GF_FilterPacket *pck_src, GF_FilterPacket *pck_dst)
{ (void) pck_src; (void) pck_dst; return GF_OK; }

GF_EXPORT
GF_Err gf_filter_pck_set_cts(GF_FilterPacket *pck, u64 cts) { (void) pck; (void) cts; return GF_OK; }

GF_EXPORT
GF_Err gf_filter_pck_set_duration(GF_FilterPacket *pck, u32 duration) { (void) pck; (void) duration; return GF_OK; }

GF_EXPORT
GF_Err gf_filter_pck_set_framing(GF_FilterPacket *pck, Bool is_start, Bool is_end)
{ (void) pck; (void) is_start; (void) is_end; return GF_OK; }

GF_EXPORT
GF_Err gf_filter_pck_set_sap(GF_FilterPacket *pck, GF_FilterSAPType sap_type) { (void) pck; (void) sap_type; return GF_OK; }

GF_EXPORT
GF_Err gf_filter_pck_send(GF_FilterPacket *pck) { (void) pck; return GF_OK; }

GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode) { (void) buffer; (void) size; (void) mode; return NULL; }

GF_Err gf_bs_reassign_buffer(GF_BitStream *bs, const u8 *buffer, u64 size) { (void) bs; (void) buffer; (void) size; return GF_OK; }

GF_Err gf_bs_seek(GF_BitStream *bs, u64 offset) { (void) bs; (void) offset; return GF_OK; }

u64 gf_bs_get_position(GF_BitStream *bs) { (void) bs; return 0; }

static void latm_dmx_check_dur(GF_Filter *filter, GF_LATMDmxCtx *ctx) { (void) filter; (void) ctx; }

static void latm_dmx_check_pid(GF_Filter *filter, GF_LATMDmxCtx *ctx) { (void) filter; (void) ctx; }

static void latm_dmx_update_cts(GF_LATMDmxCtx *ctx) { (void) ctx; }

static Bool latm_dmx_sync_frame_bs(GF_BitStream *bs, GF_M4ADecSpecInfo *acfg, u32 *nb_bytes, u8 *buffer, u32 *nb_skipped)
{ (void) bs; (void) acfg; (void) nb_bytes; (void) buffer; (void) nb_skipped; return GF_FALSE; }

/* ==== VERBATIM from data_cve/cve_759d94e1/target/original_function.c ==== */
GF_Err latm_dmx_process(GF_Filter *filter)
{
	GF_LATMDmxCtx *ctx = gf_filter_get_udta(filter);
	GF_FilterPacket *pck, *dst_pck;
	u32 pos;
	u8 *data, *output;
	u32 pck_size, prev_pck_size;
	u64 cts = GF_FILTER_NO_TS;

	if (ctx->in_error)
		return ctx->in_error;

	//always reparse duration
	if (!ctx->duration.num)
		latm_dmx_check_dur(filter, ctx);

	if (ctx->opid && !ctx->is_playing)
		return GF_OK;

	pck = gf_filter_pid_get_packet(ctx->ipid);
	if (!pck) {
		if (gf_filter_pid_is_eos(ctx->ipid)) {
			if (!ctx->latm_buffer_size) {
				if (ctx->opid)
					gf_filter_pid_set_eos(ctx->opid);
				if (ctx->src_pck) gf_filter_pck_unref(ctx->src_pck);
				ctx->src_pck = NULL;
				return GF_EOS;
			}
		} else {
			return GF_OK;
		}
	}

	data = (char *) gf_filter_pck_get_data(pck, &pck_size);

	//input pid sets some timescale - we flushed pending data , update cts
	if (ctx->timescale && pck) {
		cts = gf_filter_pck_get_cts(pck);
	}

	prev_pck_size = ctx->latm_buffer_size;

	if (pck && !ctx->resume_from) {
		if (ctx->latm_buffer_size + pck_size > ctx->latm_buffer_alloc) {
			ctx->latm_buffer_alloc = ctx->latm_buffer_size + pck_size;
			ctx->latm_buffer = gf_realloc(ctx->latm_buffer, ctx->latm_buffer_alloc);
		}
		memcpy(ctx->latm_buffer + ctx->latm_buffer_size, data, pck_size);
		ctx->latm_buffer_size += pck_size;
	}

	if (!ctx->bs) ctx->bs = gf_bs_new(ctx->latm_buffer, ctx->latm_buffer_size, GF_BITSTREAM_READ);
	else gf_bs_reassign_buffer(ctx->bs, ctx->latm_buffer, ctx->latm_buffer_size);

	if (ctx->resume_from) {
		gf_bs_seek(ctx->bs, ctx->resume_from-1);
		ctx->resume_from = 0;
	}

	if (cts == GF_FILTER_NO_TS)
		prev_pck_size = 0;


	while (1) {
		pos = (u32) gf_bs_get_position(ctx->bs);
		u8 latm_buffer[4096];
		u32 latm_frame_size = 4096;
		if (!latm_dmx_sync_frame_bs(ctx->bs,&ctx->acfg, &latm_frame_size, latm_buffer, NULL)) break;

		if (ctx->in_seek) {
			u64 nb_samples_at_seek = (u64) (ctx->start_range * GF_M4ASampleRates[ctx->sr_idx]);
			if (ctx->cts + ctx->dts_inc >= nb_samples_at_seek) {
				//u32 samples_to_discard = (ctx->cts + ctx->dts_inc) - nb_samples_at_seek;
				ctx->in_seek = GF_FALSE;
			}
		}

		latm_dmx_check_pid(filter, ctx);

		if (!ctx->is_playing) {
			ctx->resume_from = pos+1;
			return GF_OK;
		}

		if (!ctx->in_seek) {
			GF_FilterSAPType sap = GF_FILTER_SAP_1;

			dst_pck = gf_filter_pck_new_alloc(ctx->opid, latm_frame_size, &output);
			if (ctx->src_pck) gf_filter_pck_merge_properties(ctx->src_pck, dst_pck);

			memcpy(output, latm_buffer, latm_frame_size);

			gf_filter_pck_set_cts(dst_pck, ctx->cts);
			gf_filter_pck_set_duration(dst_pck, ctx->dts_inc);
			gf_filter_pck_set_framing(dst_pck, GF_TRUE, GF_TRUE);

			/*xHE-AAC, check RAP*/
			if (ctx->acfg.base_object_type==GF_CODECID_USAC) {
				if (latm_frame_size && (output[0] & 0x80) && !ctx->prev_sap) {
					sap = GF_FILTER_SAP_1;
					ctx->prev_sap = GF_TRUE;
				} else {
					sap = GF_FILTER_SAP_NONE;
					ctx->prev_sap = GF_FALSE;
				}
			}
			gf_filter_pck_set_sap(dst_pck, sap);

			gf_filter_pck_send(dst_pck);
		}
		latm_dmx_update_cts(ctx);

		if (prev_pck_size) {
			pos = (u32) gf_bs_get_position(ctx->bs);
			if (prev_pck_size<=pos) {
				prev_pck_size=0;
				if (ctx->src_pck) gf_filter_pck_unref(ctx->src_pck);
				ctx->src_pck = pck;
				if (pck)
					gf_filter_pck_ref_props(&ctx->src_pck);
			}
		}
	}

	if (pck) {
		pos = (u32) gf_bs_get_position(ctx->bs);
		assert(ctx->latm_buffer_size >= pos);
		memmove(ctx->latm_buffer, ctx->latm_buffer+pos, ctx->latm_buffer_size - pos);
		ctx->latm_buffer_size -= pos;
		gf_filter_pid_drop_packet(ctx->ipid);
		assert(!ctx->resume_from);
	} else {
		ctx->latm_buffer_size = 0;
		return latm_dmx_process(filter);
	}
	return GF_OK;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
	if (argc < 2) return 0;
	FILE *f = fopen(argv[1], "rb");
	if (!f) return 0;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long sz = ftell(f);
	if (sz < 0) sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	u32 n = (u32) sz;
	/* HEAP-allocate the raw input (ASAN-guarded) -- stands in for the bytes a real
	 * upstream demuxer would have appended into ctx->latm_buffer over one or more
	 * PREVIOUS latm_dmx_process() calls, still sitting there unconsumed. */
	u8 *buf = NULL;
	if (n > 0) {
		buf = (u8 *) malloc(n);
		if (!buf) { fclose(f); return 0; }
		if (fread(buf, 1, n, f) != n) { fclose(f); free(buf); return 0; }
	}
	fclose(f);

	GF_Filter filter_obj;
	GF_LATMDmxCtx ctx;
	memset(&filter_obj, 0, sizeof(filter_obj));
	memset(&ctx, 0, sizeof(ctx));

	filter_obj.filter_udta = &ctx;
	ctx.ipid = (GF_FilterPid *) 0x1;   /* opaque non-NULL handle: never dereferenced */
	ctx.opid = NULL;                     /* no output pid -> skips set_eos()/pck_unref() */
	ctx.src_pck = NULL;
	ctx.duration.num = 1;                /* duration already known -> skips latm_dmx_check_dur() */
	ctx.in_error = GF_OK;
	ctx.latm_buffer = (char *) buf;
	ctx.latm_buffer_size = n;

	g_next_pck = NULL;   /* the harness never hands latm_dmx_process a fresh packet */

	if (n == 0) {
		/* SAFE-A: nothing buffered, upstream pid at EOS -> clean early `return GF_EOS`. */
		g_pid_is_eos = GF_TRUE;
	} else {
		switch (buf[0] % 3) {
		case 0:
			/* SAFE-B: a prior pass already flagged an error -> immediate propagate,
			 * before the pid is even touched. */
			ctx.in_error = GF_BAD_PARAM;
			g_pid_is_eos = GF_TRUE;
			break;
		case 1:
			/* SAFE-C: upstream pid not yet at EOS, no new packet ready -> benign
			 * `return GF_OK`. */
			g_pid_is_eos = GF_FALSE;
			break;
		default:
			/* TRIGGER (CVE-2021-30199): upstream pid reached EOS, no new packet, but
			 * `n` bytes are still sitting unconsumed in ctx->latm_buffer from a prior
			 * call -> latm_dmx_process falls through every guard with pck still NULL
			 * and calls gf_filter_pck_get_data(NULL, ...) -> NULL dereference. */
			g_pid_is_eos = GF_TRUE;
			break;
		}
	}

	GF_Err e = latm_dmx_process(&filter_obj);
	fprintf(stderr, "vb: latm_dmx_process returned %d\n", (int) e);

	free(buf);
	return 0;
}

/* cve_barebone direct-call harness for CVE-2021-40572 (gpac)
 * Target: gf_av1_reset_state  (src/media_tools/av_parsers.c)
 * Bug class: double free (CWE-415), fix commit
 *   7bb1b4a4dd23c885f9db9f577dfe79ecc5433109 "fixed #1893" (gpac/gpac issue #1893,
 *   "Segmentation fault caused by double free using mp4box in av1dmx_finalize,
 *   reframe_av1.c:1075"). Real crash trace (from the issue, gdb bt):
 *     #5 gf_free (ptr=<optimized out>) at src/utils/alloc.c:165
 *     #6 av1dmx_finalize (filter=<optimized out>) at src/filters/reframe_av1.c:1075
 *
 * Root cause, entirely inside gf_av1_reset_state's own body (the fix diff touches
 * ONLY this function -- 2 lines added, 4 removed, nothing else in the whole repo):
 *   vulnerable (this file, verbatim below):
 *       if (state->bs) {
 *           if (gf_bs_get_position(state->bs)) {
 *               u32 size;
 *               gf_bs_get_content_no_truncate(state->bs, &state->frame_obus, &size, &state->frame_obus_alloc);
 *           }
 *           gf_bs_del(state->bs);
 *       }
 *       state->bs = NULL;
 *   fixed (upstream, NOT what's compiled here):
 *       if (state->bs) {
 *           u32 size;
 *           gf_bs_get_content_no_truncate(state->bs, &state->frame_obus, &size, &state->frame_obus_alloc);
 *           gf_bs_del(state->bs);
 *       }
 *       state->bs = NULL;
 *
 * gf_bs_get_content_no_truncate(bs, out, outSize, alloc_size) is the REAL av1dmx
 * "flush the WRITE_DYN bitstream's buffer out" primitive (src/utils/bitstream.c,
 * verbatim below): whenever it actually runs, it transfers bs->original out through
 * *out and sets bs->original = NULL (so the immediately-following gf_bs_del() cannot
 * also free it -- ownership was transferred). The vulnerable code above SKIPS that
 * call whenever gf_bs_get_position(bs)==0 (nothing written to bs yet, e.g. a parse
 * error on a fuzzed/malformed AV1 OBU aborts the temporal unit before any byte is
 * emitted -- common, attacker-reachable). When skipped, *state->frame_obus is left
 * unmodified while gf_bs_del(state->bs) unconditionally frees bs->original a few
 * lines later -- so if bs->original and state->frame_obus alias the SAME heap block
 * (which real av1dmx code makes them do: gf_av1_parse_obu, src/media_tools/av_parsers.c
 * :2459-2461, reassigns a live state->bs to reuse state->frame_obus as its next
 * buffer -- `else gf_bs_reassign_buffer(state->bs, state->frame_obus,
 * state->frame_obus_alloc);` -- once a prior flush has populated state->frame_obus),
 * state->frame_obus is left dangling at a pointer gf_bs_del() JUST freed. Reproduced
 * here by calling gf_av1_reset_state(&state, GF_TRUE) TWICE on a state whose bs is
 * re-aliased (via the REAL gf_bs_new/gf_bs_get_content_no_truncate/
 * gf_bs_reassign_buffer primitives, copied verbatim below -- exactly the calls
 * gf_av1_parse_obu/reframe_av1.c make) to the same now-freed buffer each time
 * gf_bs_get_position(state.bs)==0: the 1st call's gf_bs_del() frees the aliased
 * buffer (the bug firing once); the 2nd call's OWN, unmodified `gf_bs_del(state->bs);`
 * line -- gf_av1_reset_state's own body -- frees it again: the double free ASAN
 * catches, with gf_av1_reset_state on the crash stack (via its callee gf_bs_del).
 *
 * AV1State/AV1StateFrame below are reduced to the REAL fields (real names, real
 * types, verbatim from include/gpac/internal/media_dev.h) gf_av1_reset_state's own
 * body actually dereferences (bs, frame_obus, frame_obus_alloc, frame_state.{
 * is_first_frame, header_obus, frame_obus}); the rest of the real AV1State (AV1
 * sequence-header/tile-grid/golden-motion/ref-frame decode state, AV1Config, ...) is
 * never touched by this function and is omitted -- the same field-trimming already
 * used for mrb_state/mrb_gc in the sibling cve_barebone harness for CVE-2020-36401.
 * GF_List/GF_BitStream are copied whole (the REAL private structs from
 * src/utils/list.c and src/utils/bitstream.c) since gf_av1_reset_state's callees
 * dereference their internals directly.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==== gpac/setup.h : primitive typedefs, verbatim names (64-bit Linux branch) ==== */
typedef unsigned long long u64;
typedef long long s64;
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

#define GF_EXPORT

/* ==== gpac/tools.h : GF_Err, trimmed to the values the copied bitstream/list
 * functions actually return/compare (real names/values). GF_LOG is diagnostic-only
 * in every copied function below (never affects control flow or memory safety) --
 * no-op it out rather than pull in the whole gpac log subsystem. ==== */
typedef enum {
	GF_OK = 0,
	GF_BAD_PARAM = -2,
	GF_OUT_OF_MEM = -3,
	GF_IO_ERR = -6
} GF_Err;

#define GF_LOG(_lvl, _tool, _msg) ((void)0)
#define GF_LOG_ERROR 0
#define GF_LOG_WARNING 0
#define GF_LOG_CORE 0

/* ==== gpac/list.h : GF_List, the REAL private struct from src/utils/list.c's
 * GF_LIST_ARRAY_GROW branch (the default non-WINCE mode -- see the #else
 * "GF_LIST_ARRAY_GROW" branch, src/utils/list.c:586-708). ==== */
typedef struct _tag_array {
	void **slots;
	u32 entryCount;
	u32 allocSize;
} GF_List;

/* ==== gpac/bitstream.h : GF_BitStream, the REAL private struct from
 * src/utils/bitstream.c (struct __tag_bitstream), verbatim. ==== */
typedef struct __tag_bitstream {
	FILE *stream;
	char *original;
	u64 size;
	u64 position;
	u32 current;
	u32 nbBits;
	u32 bsmode;

	void (*EndOfStream)(void *par);
	void *par;

	char *cache_write;
	u32 cache_write_size, buffer_written;

	Bool remove_emul_prevention_byte;
	u32 nb_zeros;

	GF_Err (*on_block_out)(void *cbk, u8 *data, u32 block_size);
	void *usr_data;
	u64 bytes_out;
	u32 prevent_dispatch;

	u64 cookie;

	u8 *cache_read;
	u32 cache_read_size, cache_read_pos, cache_read_alloc;

	void (*on_log)(void *udta, const char *field_name, u32 nb_bits, u64 field_val, s32 idx1, s32 idx2, s32 idx3);
	void *log_udta;
} GF_BitStream;

/* ==== gpac/bitstream.h : mode constants, real values. ==== */
#define GF_BITSTREAM_READ		0
#define GF_BITSTREAM_WRITE		1
#define GF_BITSTREAM_WRITE_DYN	2
/* ==== src/utils/bitstream.c : "private types" enum, verbatim (bitstream.c:31-35) --
 * FILE-mode variants, real values, only ever compared-against (never reached, no
 * GF_BitStream this harness builds is ever put in FILE mode) but referenced by the
 * verbatim gf_bs_align/BS_SeekIntern bodies below. ==== */
enum
{
	GF_BITSTREAM_FILE_READ = GF_BITSTREAM_WRITE_DYN + 1,
	GF_BITSTREAM_FILE_WRITE
};

/* ==== gpac/mpeg4_odf.h : GF_AV1_OBUArrayEntry, verbatim. ==== */
typedef struct {
	u64 obu_length;
	int obu_type; /*ObuType*/
	u8 *obu;
} GF_AV1_OBUArrayEntry;

/* ==== gpac/internal/media_dev.h : AV1StateFrame / AV1State, trimmed to the REAL
 * fields gf_av1_reset_state's own body dereferences (real names/types) -- see the
 * file header comment above for the trimming rationale. ==== */
typedef struct {
	Bool is_first_frame;
	GF_List *header_obus, *frame_obus; /*GF_AV1_OBUArrayEntry*/
} AV1StateFrame;

typedef struct {
	/*bitstream object for mem mode - this bitstream is NOT destroyed by
	gf_av1_reset_state(state, GF_TRUE) */
	GF_BitStream *bs;
	u8 *frame_obus;
	u32 frame_obus_alloc;

	/*frame parsing state*/
	AV1StateFrame frame_state;
} AV1State;

/* forward decls for the handful of low-level primitives stubbed below (never
 * invoked at runtime by any state this harness constructs -- see each stub's own
 * comment) so the verbatim functions that textually reference them can be defined
 * in real source order. */
static void gf_bs_write_int(GF_BitStream *bs, s32 _value, s32 nBits);
static u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits);
static s32 BS_CutBuffer(GF_BitStream *bs);
static u64 gf_fseek(FILE *fp, s64 offset, s32 whence);
static u32 gf_fwrite(const void *ptr, u32 nb_bytes, FILE *stream);
static void bs_flush_write_cache(GF_BitStream *bs);
u8 gf_bs_align(GF_BitStream *bs);

/* ==== src/utils/alloc.c : gf_malloc/gf_free/gf_realloc, verbatim for the default
 * (non-GPAC_MEMORY_TRACKING) build -- MALLOC/FREE/REALLOC are #define'd to plain
 * malloc/free/realloc in that configuration (src/utils/alloc.c:63-67,121-125). ==== */
GF_EXPORT
void *gf_malloc(size_t size)
{
	return malloc(size);
}
GF_EXPORT
void *gf_realloc(void *ptr, size_t size)
{
	return realloc(ptr, size);
}
GF_EXPORT
void gf_free(void *ptr)
{
	free(ptr);
}

/* ==== src/utils/list.c : GF_LIST_ARRAY_GROW branch, verbatim (list.c:39-47 picks
 * this branch by default on every non-WINCE platform). ==== */
#define GF_LIST_REALLOC(a) (a = a ? (3*a/2) : 10)

GF_EXPORT
GF_List * gf_list_new()
{
	GF_List *nlist;

	nlist = (GF_List *) gf_malloc(sizeof(GF_List));
	if (! nlist) return NULL;

	nlist->slots = NULL;
	nlist->entryCount = 0;
	nlist->allocSize = 0;
	return nlist;
}

GF_EXPORT
void gf_list_del(GF_List *ptr)
{
	if (!ptr) return;
	gf_free(ptr->slots);
	gf_free(ptr);
}

static void realloc_chain(GF_List *ptr)
{
	GF_LIST_REALLOC(ptr->allocSize);
	ptr->slots = (void**)gf_realloc(ptr->slots, ptr->allocSize*sizeof(void*));
}

GF_EXPORT
GF_Err gf_list_add(GF_List *ptr, void* item)
{
	if (! ptr) return GF_BAD_PARAM;
	if (! item)
		return GF_BAD_PARAM;
	if (ptr->allocSize==ptr->entryCount) realloc_chain(ptr);
	if (!ptr->slots) return GF_OUT_OF_MEM;

	ptr->slots[ptr->entryCount] = item;
	ptr->entryCount ++;
	return GF_OK;
}

GF_EXPORT
u32 gf_list_count(const GF_List *ptr)
{
	if (!ptr) return 0;
	return ptr->entryCount;
}

GF_EXPORT
void *gf_list_get(GF_List *ptr, u32 itemNumber)
{
	if(!ptr || (itemNumber >= ptr->entryCount))
		return NULL;
	return ptr->slots[itemNumber];
}

GF_EXPORT
void *gf_list_last(GF_List *ptr)
{
	if(!ptr || !ptr->entryCount) return NULL;
	return ptr->slots[ptr->entryCount-1];
}

/*WARNING: itemNumber is from 0 to entryCount - 1*/
GF_EXPORT
GF_Err gf_list_rem(GF_List *ptr, u32 itemNumber)
{
	u32 i;
	if ( !ptr || !ptr->slots || !ptr->entryCount) return GF_BAD_PARAM;
	if (ptr->entryCount < itemNumber) return GF_BAD_PARAM;

	i = ptr->entryCount - itemNumber - 1;
	if (i) memmove(&ptr->slots[itemNumber], & ptr->slots[itemNumber +1], sizeof(void *)*i);
	ptr->slots[ptr->entryCount-1] = NULL;
	ptr->entryCount -= 1;
	return GF_OK;
}

GF_EXPORT
GF_Err gf_list_rem_last(GF_List *ptr)
{
	if ( !ptr || !ptr->slots || !ptr->entryCount) return GF_BAD_PARAM;
	ptr->slots[ptr->entryCount-1] = NULL;
	ptr->entryCount -= 1;
	return GF_OK;
}

GF_EXPORT
void* gf_list_pop_back(GF_List *ptr) {
	void * item;
	if (!ptr) return NULL;

	item = gf_list_last(ptr);
	gf_list_rem_last(ptr);

	return item;
}

/* ==== src/utils/bitstream.c, verbatim. ==== */
#define BS_MEM_BLOCK_ALLOC_SIZE		512

GF_EXPORT
GF_BitStream *gf_bs_new(const u8 *buffer, u64 BufferSize, u32 mode)
{
	GF_BitStream *tmp = (GF_BitStream *)gf_malloc(sizeof(GF_BitStream));
	if (!tmp) return NULL;
	memset(tmp, 0, sizeof(GF_BitStream));

	tmp->original = (char*)buffer;
	tmp->size = BufferSize;

	tmp->bsmode = mode;

	switch (tmp->bsmode) {
	case GF_BITSTREAM_READ:
		tmp->nbBits = 8;
		tmp->current = 0;
		break;
	case GF_BITSTREAM_WRITE:
	case GF_BITSTREAM_WRITE_DYN:
		tmp->nbBits = 0;
		if (! buffer) {
			/*if BufferSize is specified, use it. This is typically used when AvgSize of
			some buffers is known, but some exceed it.*/
			if (BufferSize) {
				tmp->size = BufferSize;
			} else {
				tmp->size = BS_MEM_BLOCK_ALLOC_SIZE;
			}
			tmp->original = (char *) gf_malloc(sizeof(char) * ((u32) tmp->size));
			if (! tmp->original) {
				gf_free(tmp);
				return NULL;
			}
			tmp->bsmode = GF_BITSTREAM_WRITE_DYN;
		} else {
			tmp->original = (char*)buffer;
			tmp->size = BufferSize;
		}
		break;
	default:
		/*the stream constructor is not the same...*/
		gf_free(tmp);
		return NULL;
	}
	return tmp;
}

GF_Err gf_bs_reassign_buffer(GF_BitStream *bs, const u8 *buffer, u64 BufferSize)
{
	if (!bs) return GF_BAD_PARAM;
	if (bs->bsmode == GF_BITSTREAM_READ) {
		bs->original = (char*)buffer;
		bs->size = BufferSize;
		bs->position = 0;
		bs->current = 0;
		bs->nbBits = 8;
		bs->current = 0;
		bs->nb_zeros = 0;
		return GF_OK;
	}
	if (bs->bsmode==GF_BITSTREAM_WRITE) {
		if (!buffer || !BufferSize) return GF_BAD_PARAM;
		bs->original = (char*)buffer;
		bs->size = BufferSize;
		bs->position = 0;
		bs->current = 0;
		bs->nbBits = 0;
		bs->current = 0;
		return GF_OK;
	}
	if (bs->bsmode!=GF_BITSTREAM_WRITE_DYN) return GF_BAD_PARAM;
	if (bs->original) return GF_BAD_PARAM;

	bs->position = 0;
	bs->current = 0;
	bs->nbBits = 0;
	bs->current = 0;
	bs->size = BufferSize ? BufferSize : BS_MEM_BLOCK_ALLOC_SIZE;
	if (buffer) {
		bs->original = (char *) buffer;
	} else {
		bs->original = (char *) gf_malloc(sizeof(char) * ((u32) bs->size));
		if (! bs->original) {
			return GF_OUT_OF_MEM;
		}
	}
	return GF_OK;
}

GF_EXPORT
void gf_bs_del(GF_BitStream *bs)
{
	if (!bs) return;
	if (bs->on_block_out && bs->position>bs->bytes_out) {
		bs->on_block_out(bs->usr_data, bs->original, (u32) (bs->position - bs->bytes_out) );
	}
	/*if we are in dynamic mode (alloc done by the bitstream), free the buffer if still present*/
	if ((bs->bsmode == GF_BITSTREAM_WRITE_DYN) && bs->original) gf_free(bs->original);
	if (bs->cache_write) {
		bs_flush_write_cache(bs);
		gf_free(bs->cache_write);
	}
	if (bs->cache_read)
		gf_free(bs->cache_read);
	gf_free(bs);
}

GF_EXPORT
u64 gf_bs_get_position(GF_BitStream *bs)
{
	if (bs->cache_write)
		return bs->position + bs->buffer_written;
	return bs->position;
}

/*For DYN mode, this gets the content out without cutting the buffer to the number of written bytes*/
GF_EXPORT
void gf_bs_get_content_no_truncate(GF_BitStream *bs, u8 **output, u32 *outSize, u32 *alloc_size)
{
	/*only in WRITE MEM mode*/
	if (bs->bsmode != GF_BITSTREAM_WRITE_DYN) return;

	if (bs->on_block_out && bs->position>bs->bytes_out) {
		bs->on_block_out(bs->usr_data, bs->original, (u32) (bs->position - bs->bytes_out) );
	}

	if (!bs->position && !bs->nbBits) {
		if (!alloc_size) {
			*output = NULL;
			gf_free(bs->original);
		} else {
			*alloc_size = (u32) bs->size;
			*output = bs->original;
		}
		*outSize = 0;
	} else {
		if (alloc_size) {
			/*Align our buffer or we're dead!*/
			gf_bs_align(bs);
			*alloc_size = (u32) bs->size;
			*outSize = (u32) bs->position;
			*output = bs->original;
		} else {
			s32 copy = BS_CutBuffer(bs);
			if (copy < 0) {
				*output = NULL;
			} else
				*output = bs->original;
			*outSize = (u32) bs->size;
		}
	}
	bs->original = NULL;
	bs->size = 0;
	bs->position = 0;
}

GF_EXPORT
u8 gf_bs_align(GF_BitStream *bs)
{
	u8 res = 8 - bs->nbBits;
	if ( (bs->bsmode == GF_BITSTREAM_READ) || (bs->bsmode == GF_BITSTREAM_FILE_READ)) {
		if (res > 0) {
			gf_bs_read_int(bs, res);
		}
		return res;
	}
	if (bs->nbBits > 0) {
		gf_bs_write_int (bs, 0, res);
		return res;
	}
	return 0;
}

static void bs_flush_write_cache(GF_BitStream *bs)
{
	if (bs->buffer_written) {
		u32 nb_write;
		nb_write = (u32) gf_fwrite(bs->cache_write, bs->buffer_written, bs->stream);

		//check we didn't rewind the bitstream
		if (bs->size == bs->position)
			bs->size += nb_write;
		bs->position += nb_write;
		bs->buffer_written = 0;
	}
}

static GF_Err BS_SeekIntern(GF_BitStream *bs, u64 offset)
{
	u32 i;
	/*if mem, do it */
	if ((bs->bsmode == GF_BITSTREAM_READ) || (bs->bsmode == GF_BITSTREAM_WRITE) || (bs->bsmode == GF_BITSTREAM_WRITE_DYN)) {
		if (offset > 0xFFFFFFFF) return GF_IO_ERR;
		if (!bs->original) return GF_BAD_PARAM;
		/*0 for write, read will be done automatically*/
		if (offset >= bs->size) {
			if ( (bs->bsmode == GF_BITSTREAM_READ) || (bs->bsmode == GF_BITSTREAM_WRITE) ) {
				if (offset > bs->size) {
					GF_LOG(GF_LOG_WARNING, GF_LOG_CORE, ("[BS] Attempt to seek to %d after end of bitstream %d, assuming seek to end\n", offset, bs->size));
				}
				bs->position = bs->size;
				bs->nbBits = (bs->bsmode == GF_BITSTREAM_READ) ? 8 : 0;
				return GF_OK;
			}
			/*in DYN, gf_realloc ...*/
			bs->original = (char*)gf_realloc(bs->original, (u32) (offset + 1));
			if (!bs->original)
				return GF_OUT_OF_MEM;
			for (i = 0; i < (u32) (offset + 1 - bs->size); i++) {
				bs->original[bs->size + i] = 0;
			}
			bs->size = offset + 1;
		}
		bs->current = bs->original[offset];
		bs->position = offset;
		bs->nbBits = (bs->bsmode == GF_BITSTREAM_READ) ? 8 : 0;
		return GF_OK;
	}

	if (bs->cache_write)
		bs_flush_write_cache(bs);

	if (bs->cache_read) {
		bs->cache_read_pos = bs->cache_read_size;
	}

	gf_fseek(bs->stream, offset, SEEK_SET);

	bs->position = offset;
	bs->current = 0;
	/*setup NbBits so that next acccess to the buffer will trigger read/write*/
	bs->nbBits = (bs->bsmode == GF_BITSTREAM_FILE_READ) ? 8 : 0;
	return GF_OK;
}

/*seek from beginning of stream: align before anything else*/
GF_EXPORT
GF_Err gf_bs_seek(GF_BitStream *bs, u64 offset)
{
	if (bs->on_block_out) {
		GF_Err e;
		if (offset < bs->bytes_out) {
			GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("[BS] Attempt to seek on byte range already forwarded\n"));
			return GF_BAD_PARAM;
		}
		/*warning: we allow offset = bs->size for WRITE buffers*/
		if (offset - bs->bytes_out > bs->size)
			return GF_BAD_PARAM;
		gf_bs_align(bs);
		e = BS_SeekIntern(bs, offset - bs->bytes_out);
		bs->position += bs->bytes_out;
		return e;
	}
	if (bs->cache_write)
		bs_flush_write_cache(bs);

	/*warning: we allow offset = bs->size for WRITE buffers*/
	if (offset > bs->size) return GF_BAD_PARAM;

	gf_bs_align(bs);
	return BS_SeekIntern(bs, offset);
}

/* ---- incidental stubs: real signatures, minimal bodies. None of these is ever
 * actually invoked by any state this harness constructs: every GF_BitStream here
 * has bsmode==GF_BITSTREAM_WRITE_DYN and nbBits==0 throughout its life (nothing
 * ever calls a bit-level write/read primitive), stream/cache_write/cache_read stay
 * NULL (memset-zeroed by gf_bs_new and never assigned), and alloc_size is always
 * passed non-NULL to gf_bs_get_content_no_truncate (mirroring gf_av1_reset_state's
 * own call site) so BS_CutBuffer's branch is never reached either. ---- */
static void gf_bs_write_int(GF_BitStream *bs, s32 _value, s32 nBits) { (void)bs; (void)_value; (void)nBits; }
static u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits) { (void)bs; (void)nBits; return 0; }
static s32 BS_CutBuffer(GF_BitStream *bs) { (void)bs; return 0; }
static u64 gf_fseek(FILE *fp, s64 offset, s32 whence) { (void)fp; (void)offset; (void)whence; return 0; }
static u32 gf_fwrite(const void *ptr, u32 nb_bytes, FILE *stream) { (void)ptr; (void)nb_bytes; (void)stream; return 0; }

/* ==== VERBATIM from data_cve/cve_4ce4fe2e/target/original_function.c
 * (src/media_tools/av_parsers.c:3954-3997). Do not edit. ==== */
GF_EXPORT
void gf_av1_reset_state(AV1State *state, Bool is_destroy)
{
	GF_List *l1, *l2;

	if (state->frame_state.header_obus) {
		while (gf_list_count(state->frame_state.header_obus)) {
			GF_AV1_OBUArrayEntry *a = (GF_AV1_OBUArrayEntry*)gf_list_pop_back(state->frame_state.header_obus);
			if (a->obu) gf_free(a->obu);
			gf_free(a);
		}
	}

	if (state->frame_state.frame_obus) {
		while (gf_list_count(state->frame_state.frame_obus)) {
			GF_AV1_OBUArrayEntry *a = (GF_AV1_OBUArrayEntry*)gf_list_pop_back(state->frame_state.frame_obus);
			if (a->obu) gf_free(a->obu);
			gf_free(a);
		}
	}
	l1 = state->frame_state.frame_obus;
	l2 = state->frame_state.header_obus;
	memset(&state->frame_state, 0, sizeof(AV1StateFrame));
	state->frame_state.is_first_frame = GF_TRUE;

	if (is_destroy) {
		gf_list_del(l1);
		gf_list_del(l2);
		if (state->bs) {
			if (gf_bs_get_position(state->bs)) {
				u32 size;
				gf_bs_get_content_no_truncate(state->bs, &state->frame_obus, &size, &state->frame_obus_alloc);
			}
			gf_bs_del(state->bs);
		}
		state->bs = NULL;
	}
	else {
		state->frame_state.frame_obus = l1;
		state->frame_state.header_obus = l2;
		if (state->bs)
			gf_bs_seek(state->bs, 0);
	}
}
/* ==== end verbatim target ==== */

/* ---- harness driver ---- */

__attribute__((noinline))
static unsigned char *
read_file(const char *path, size_t *out_n)
{
	unsigned char *buf = NULL;
	size_t n = 0;
	FILE *f = fopen(path, "rb");
	if (f) {
		if (fseek(f, 0, SEEK_END) == 0) {
			long sz = ftell(f);
			if (sz > 0) {
				rewind(f);
				buf = (unsigned char *)malloc((size_t)sz);
				if (buf) {
					n = fread(buf, 1, (size_t)sz, f);
				}
			}
		}
		fclose(f);
	}
	*out_n = n;
	return buf;
}

/* Populate frame_state.{header_obus,frame_obus} with a small, input-sized number of
 * REAL heap GF_AV1_OBUArrayEntry entries (real struct, real gf_list_new/gf_list_add),
 * so gf_av1_reset_state's own list-cleanup loops run on every call, both triggering
 * and safe -- genuine extra coverage of the function's other real logic, orthogonal
 * to the bs/frame_obus double-free mechanism under test. */
__attribute__((noinline))
static GF_List *
build_obu_list(u32 n_entries, u32 fill_byte, u32 sz_seed)
{
	u32 i;
	GF_List *l;
	if (!n_entries) return NULL;
	l = gf_list_new();
	for (i = 0; i < n_entries; i++) {
		GF_AV1_OBUArrayEntry *e = (GF_AV1_OBUArrayEntry*)gf_malloc(sizeof(GF_AV1_OBUArrayEntry));
		u32 sz = 1 + ((sz_seed + i) % 8);
		e->obu = (u8*)gf_malloc(sz);
		memset(e->obu, (int)fill_byte, sz);
		e->obu_length = sz;
		e->obu_type = (int)(i & 0xF);
		gf_list_add(l, e);
	}
	return l;
}

int
main(int argc, char **argv)
{
	if (argc < 2) return 0;

	size_t n = 0;
	unsigned char *data = read_file(argv[1], &n);
	unsigned char b0 = n > 0 ? data[0] : 0;
	unsigned char b1 = n > 1 ? data[1] : 0;
	unsigned char b2 = n > 2 ? data[2] : 0;
	unsigned char b3 = n > 3 ? data[3] : 0;
	unsigned char b4 = n > 4 ? data[4] : 0;
	free(data);

	Bool trigger = (b0 & 1) ? GF_TRUE : GF_FALSE;

	AV1State state;
	memset(&state, 0, sizeof(state));

	/* real, heap-backed OBU lists sized from attacker input; exercised by every call
	 * below regardless of trigger/safe branch. */
	state.frame_state.header_obus = build_obu_list(b1 % 4, 0xAA, b3);
	state.frame_state.frame_obus  = build_obu_list(b2 % 4, 0xBB, b4);

	if (trigger) {
		/* TRIGGERING: reproduce CVE-2021-40572 (double free, CWE-415).
		 *
		 * Real av1dmx flow this mirrors (gf_av1_parse_obu, src/media_tools/
		 * av_parsers.c:2459-2461):
		 *     if (!state->bs) state->bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		 *     else gf_bs_reassign_buffer(state->bs, state->frame_obus, state->frame_obus_alloc);
		 * i.e. once a WRITE_DYN bs's content has been flushed out into
		 * state->frame_obus (gf_bs_get_content_no_truncate -- e.g. reframe_av1.c:771
		 * when a packet is emitted), a live state->bs is reassigned to alias that
		 * very buffer for the next temporal unit. Build that real alias using only
		 * the real primitives copied above, exactly as gf_av1_parse_obu does: */
		state.bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		{
			u32 discard_size = 0;
			gf_bs_get_content_no_truncate(state.bs, &state.frame_obus, &discard_size, &state.frame_obus_alloc);
		}
		gf_bs_reassign_buffer(state.bs, state.frame_obus, state.frame_obus_alloc);
		/* state.bs->original now ALIASES state.frame_obus (same heap pointer). An
		 * upstream parse error on the next temporal unit (malformed/truncated OBU
		 * header -- routine on fuzzed AV1 bitstreams) aborts before any byte is
		 * written to it, so gf_bs_get_position(state.bs)==0 when destroy runs --
		 * exactly the condition the fix commit's removed `if` used to guard. */
		gf_av1_reset_state(&state, GF_TRUE);
		/* BUG (this file's unmodified body, above): is_destroy skipped the
		 * position==0 extraction (the diff's removed `if`), so state.frame_obus is
		 * left pointing at the buffer gf_bs_del() just freed inside that call.
		 * state.bs is NULL again (unconditionally cleared at the end of every
		 * gf_av1_reset_state call); repopulate it the same real way so it
		 * re-aliases the now-dangling state.frame_obus for a second temporal unit,
		 * exactly mirroring the same real gf_av1_parse_obu call sequence again: */
		state.bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		{
			u8 *discard_ptr = NULL;
			u32 discard_size = 0, discard_alloc = 0;
			gf_bs_get_content_no_truncate(state.bs, &discard_ptr, &discard_size, &discard_alloc);
			gf_free(discard_ptr);
		}
		gf_bs_reassign_buffer(state.bs, state.frame_obus, state.frame_obus_alloc);
		/* Second temporal unit also aborts before writing anything (position stays
		 * 0): gf_av1_reset_state's own, unmodified `gf_bs_del(state->bs);` line
		 * frees state.bs->original == state.frame_obus a SECOND time here -- the
		 * double free ASAN catches, with gf_av1_reset_state itself on the crash
		 * stack (as gf_bs_del's caller). */
		gf_av1_reset_state(&state, GF_TRUE);
	} else {
		/* SAFE: identical call shape (fresh bs, position 0, is_destroy driven by
		 * input) WITHOUT the frame_obus aliasing step, so the same position==0
		 * skip branch inside gf_av1_reset_state still runs, but gf_bs_del() only
		 * ever frees the bs's own unshared buffer -- no corruption, clean exit. */
		state.bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		if (b3 & 1) {
			gf_av1_reset_state(&state, GF_TRUE);
		} else {
			gf_av1_reset_state(&state, GF_FALSE);
			if (state.bs) gf_bs_del(state.bs);
		}
	}

	return 0;
}

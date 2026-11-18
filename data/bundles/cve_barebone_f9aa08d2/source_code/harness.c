/* cve_barebone direct-call harness for cve_f9aa08d2 (gpac)
 * Fix commit:      8e05648d6b4459facbc783025c5c42d301fef5c3
 * Vulnerable rev:  ce01bd15f711d4575b7424b54b3a395ec64c1784
 * Target:          abst_box_read  (src/isomedia/box_code_adobe.c)
 * Bug class:       heap-based buffer overflow, WRITE (CWE-787)
 *
 * See the module docstring of scripts/gen_dc_cve_f9aa08d2.py for the full mechanism.  In
 * short: abst_box_read allocates tmp_str sized `ptr->size-8` bytes, but every later string
 * field in the same function re-derives its OWN write bound as the box's CURRENT
 * `ptr->size` (unreduced) instead of the buffer's real (8-byte-smaller) capacity -- the
 * fix is the one-line removal of that `-8`. This harness constructs the box the way
 * abst_box_new() + a real box-header parse leave it, then calls abst_box_read directly on
 * a hand-built in-memory GF_BitStream.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ---- real gpac base typedefs (include/gpac/setup.h, "UNIX likes" branch, verbatim) ---- */
typedef uint64_t u64;
typedef int64_t  s64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint8_t  u8;
typedef int8_t   s8;

#ifndef Bool
typedef enum { GF_FALSE = 0, GF_TRUE } Bool;
#endif

/* ---- real GF_Err subset this call path / its incidental callees use (include/gpac/
 * tools.h, verbatim numeric values) ---- */
typedef enum {
    GF_OK                  = 0,
    GF_BAD_PARAM           = -1,
    GF_OUT_OF_MEM          = -2,
    GF_ISOM_INVALID_FILE   = -20
} GF_Err;

/* ---- real 4CC helper (include/gpac/tools.h, verbatim) ---- */
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))
#define GF_ISOM_BOX_TYPE_ABST GF_4CC( 'a', 'b', 's', 't' )

/* ---- GF_LOG: the real DISABLED-logging definition (include/gpac/tools.h:709,
 * `#define GF_LOG(_ll, _lm, __args)` with an empty body). ISOM_DECREASE_SIZE's error
 * branch calls this; taking the real "logging compiled out" arm means the macro's own
 * arguments (gf_4cc_to_str(...), GF_LOG_ERROR, GF_LOG_CONTAINER, __FILE__/__LINE__) are
 * never evaluated by the preprocessor, so none of that incidental logging machinery needs
 * to exist here at all -- this is not a stub, it IS the real macro's disabled arm. ---- */
#define GF_LOG(_ll, _lm, __args)

/* ---- ISOM_DECREASE_SIZE: real macro, byte-for-byte (include/gpac/internal/
 * isomedia_dev.h:594-598), used verbatim by abst_box_read's own body below. ---- */
#define ISOM_DECREASE_SIZE(__ptr, bytes)	if (__ptr->size < (bytes) ) {\
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[isom] not enough bytes in box %s: %d left, reading %d (file %s, line %d)\n", gf_4cc_to_str(__ptr->type), (u32) __ptr->size, (bytes), __FILE__, __LINE__ )); \
			return GF_ISOM_INVALID_FILE; \
		}\
		__ptr->size -= bytes; \

/* ---- box_registry_entry: opaque in real gpac (isomedia_dev.h); GF_ISOM_BOX only carries
 * a pointer to it and abst_box_read never dereferences it. ---- */
struct box_registry_entry;

/* ---- GF_List: opaque in real gpac (`typedef struct _tag_array GF_List;`, gpac/list.h).
 * abst_box_read only ever touches it through gf_list_insert/gf_list_add -- never a field
 * directly -- so a minimal faithful dynamic array behind the real API is enough; the
 * exact internal representation is invisible to the target function. ---- */
typedef struct __gf_list_tag {
    void **entries;
    u32 count;
    u32 alloc;
} GF_List;

static GF_List *gf_list_new(void) { return (GF_List *)calloc(1, sizeof(GF_List)); }

/* real signature: GF_Err gf_list_add(GF_List *ptr, void* item); (include/gpac/list.h) */
static GF_Err gf_list_add(GF_List *ptr, void *item)
{
    if (!ptr) return GF_BAD_PARAM;
    if (ptr->count == ptr->alloc) {
        u32 na = ptr->alloc ? ptr->alloc * 2 : 8;
        void **ne = (void **)realloc(ptr->entries, na * sizeof(void *));
        if (!ne) return GF_OUT_OF_MEM;
        ptr->entries = ne;
        ptr->alloc = na;
    }
    ptr->entries[ptr->count++] = item;
    return GF_OK;
}

/* real signature: GF_Err gf_list_insert(GF_List *ptr, void *item, u32 position);
 * (include/gpac/list.h) -- real gf_list_insert falls back to gf_list_add whenever
 * position>=count (list.c); every call abst_box_read makes uses position==the loop index,
 * which has always tracked count exactly (one insert per successful entry, strictly in
 * order), so that is the only case this incidental callee ever needs to handle. */
static GF_Err gf_list_insert(GF_List *ptr, void *item, u32 position)
{
    (void)position;
    return gf_list_add(ptr, item);
}

/* ---- GF_ISOM_BOX / GF_ISOM_FULL_BOX (real macros, isomedia_dev.h:556-566, verbatim) +
 * GF_Box (real typedef, isomedia_dev.h:573-576). ---- */
#define GF_ISOM_BOX			\
	u32 type;				\
	u64 size;				\
	const struct box_registry_entry *registry;\
	GF_List *child_boxes; 	\
	u16 internal_flags;		\
	u16 version;				\

#define GF_ISOM_FULL_BOX		\
	GF_ISOM_BOX			\
	u32 flags;			\

typedef struct
{
	GF_ISOM_BOX
} GF_Box;

/* ---- real struct (include/gpac/internal/isomedia_dev.h:3068-3091, field-for-field
 * verbatim). ---- */
typedef struct __adobe_bootstrap_info_box
{
	GF_ISOM_FULL_BOX
	u32 bootstrapinfo_version;
	u8 profile;
	Bool live;
	Bool update;
	u8 reserved;
	u32 time_scale;
	u64 current_media_time;
	u64 smpte_time_code_offset;
	char *movie_identifier;
	u8 server_entry_count;
	GF_List *server_entry_table;
	u8 quality_entry_count;
	GF_List *quality_entry_table;
	char *drm_data;
	char *meta_data;
	u8 segment_run_table_count;
	GF_List *segment_run_table_entries;
	u8 fragment_run_table_count;
	GF_List *fragment_run_table_entries;
} GF_AdobeBootstrapInfoBox;

/* ---- real sibling structs (isomedia_dev.h:3099-3124, field-for-field verbatim).
 * abst_box_read references these only by pointer, through gf_isom_box_parse -- and every
 * corpus input below keeps segment_run_table_count==fragment_run_table_count==0, so those
 * for-loops always run zero iterations and gf_isom_box_parse is never actually invoked
 * (see the driver comment below). Kept verbatim anyway so the pointer types match exactly
 * what abst_box_read's own body declares (`GF_AdobeSegmentRunTableBox *asrt = NULL;` /
 * `GF_AdobeFragmentRunTableBox *afrt = NULL;`). ---- */
typedef struct __adobe_segment_run_table_box
{
	GF_ISOM_FULL_BOX
	u8 quality_entry_count;
	GF_List *quality_segment_url_modifiers;
	u32 segment_run_entry_count;
	GF_List *segment_run_entry_table;
} GF_AdobeSegmentRunTableBox;

typedef struct __adobe_fragment_run_table_box
{
	GF_ISOM_FULL_BOX
	u32 timescale;
	u8 quality_entry_count;
	GF_List *quality_segment_url_modifiers;
	u32 fragment_run_entry_count;
	GF_List *fragment_run_entry_table;
} GF_AdobeFragmentRunTableBox;

/* ---- gf_malloc/gf_free/gf_strdup: real non-memory-tracking bodies (src/utils/alloc.c,
 * `#ifndef GPAC_MEMORY_TRACKING` branch: plain libc passthrough -- MALLOC/FREE/STRDUP
 * alias malloc/free/strdup directly). ---- */
static void *gf_malloc(size_t size) { return malloc(size); }
static void gf_free(void *ptr) { free(ptr); }
static char *gf_strdup(const char *str) { return strdup(str); }

/* ---- GF_BitStream: opaque in real gpac (src/utils/bitstream.c, `struct
 * __tag_bitstream`). Minimal in-memory reader reproducing the real struct's READ-mode
 * semantics verified against bitstream.c: byte-position cursor (BS_ReadByte returns 0
 * past end-of-buffer without faulting -- GF_BITSTREAM_READ mode never signals an error on
 * overread, bitstream.c:351-353), MSB-first bit accumulation in gf_bs_read_bit
 * (`current<<=1; ret=(current&0x100)>>8`, bitstream.c:417-435, the NO_OPTS arm) feeding
 * gf_bs_read_int (bitstream.c:438-455), and big-endian multi-byte reads in
 * gf_bs_read_u32/u64 (bitstream.c:543+). ---- */
typedef struct __gf_bs_tag {
    const u8 *buffer;
    u64 size;
    u64 position;
    u32 current;
    u32 nbBits;
} GF_BitStream;

#define GF_BITSTREAM_READ 0

/* real signature: GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode); */
static GF_BitStream *gf_bs_new(const u8 *buffer, u64 size, u32 mode)
{
    (void)mode;
    GF_BitStream *bs = (GF_BitStream *)calloc(1, sizeof(GF_BitStream));
    bs->buffer = buffer;
    bs->size = size;
    bs->position = 0;
    bs->nbBits = 8;
    return bs;
}

static void gf_bs_del(GF_BitStream *bs) { if (bs) free(bs); }

static u8 BS_ReadByte(GF_BitStream *bs)
{
    if (bs->position >= bs->size) return 0;   /* real: EndOfStream callback, then return 0 */
    return bs->buffer[bs->position++];
}

static u8 gf_bs_read_bit(GF_BitStream *bs)
{
    if (bs->nbBits == 8) {
        bs->current = BS_ReadByte(bs);
        bs->nbBits = 0;
    }
    bs->current <<= 1;
    bs->nbBits++;
    return (u8)((bs->current & 0x100) >> 8);
}

static u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits)
{
    u32 ret = 0;
    while (nBits-- > 0) {
        ret <<= 1;
        ret |= gf_bs_read_bit(bs);
    }
    return ret;
}

static u32 gf_bs_read_u8(GF_BitStream *bs)
{
    return (u32)BS_ReadByte(bs);
}

static u32 gf_bs_read_u32(GF_BitStream *bs)
{
    u32 ret = BS_ReadByte(bs);
    ret = (ret << 8) | BS_ReadByte(bs);
    ret = (ret << 8) | BS_ReadByte(bs);
    ret = (ret << 8) | BS_ReadByte(bs);
    return ret;
}

static u64 gf_bs_read_u64(GF_BitStream *bs)
{
    u64 ret = 0;
    int k;
    for (k = 0; k < 8; k++) ret = (ret << 8) | BS_ReadByte(bs);
    return ret;
}

/* ---- gf_isom_box_parse / gf_isom_box_del: real signatures (isomedia_dev.h:607,612).
 * INCIDENTAL -- every corpus input below keeps segment_run_table_count ==
 * fragment_run_table_count == 0 (see driver comment), so their for-loops always run zero
 * iterations and neither function is ever actually invoked; these exist only so the
 * identifiers resolve at compile time. ---- */
static GF_Err gf_isom_box_parse(GF_Box **outBox, GF_BitStream *bs)
{
    u32 bsize = gf_bs_read_u32(bs);
    u32 btype = gf_bs_read_u32(bs);
    if (!bsize) { *outBox = NULL; return GF_ISOM_INVALID_FILE; }
    GF_Box *box = (GF_Box *)calloc(1, sizeof(GF_Box));
    box->type = btype;
    box->size = bsize;
    *outBox = box;
    return GF_OK;
}

static void gf_isom_box_del(GF_Box *ptr) { if (ptr) free(ptr); }

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) ================= */
__attribute__((noinline))
GF_Err abst_box_read(GF_Box *s, GF_BitStream *bs)
{
	GF_AdobeBootstrapInfoBox *ptr = (GF_AdobeBootstrapInfoBox *)s;
	int i;
	u32 tmp_strsize;
	char *tmp_str;
	GF_Err e;

	ISOM_DECREASE_SIZE(ptr, 25)
	ptr->bootstrapinfo_version = gf_bs_read_u32(bs);
	ptr->profile = gf_bs_read_int(bs, 2);
	ptr->live = gf_bs_read_int(bs, 1);
	ptr->update = gf_bs_read_int(bs, 1);
	ptr->reserved = gf_bs_read_int(bs, 4);
	ptr->time_scale = gf_bs_read_u32(bs);
	ptr->current_media_time = gf_bs_read_u64(bs);
	ptr->smpte_time_code_offset = gf_bs_read_u64(bs);

	i=0;
	if (ptr->size<8) return GF_ISOM_INVALID_FILE;
	tmp_strsize =(u32)ptr->size-8;
	tmp_str = gf_malloc(sizeof(char)*tmp_strsize);
	if (!tmp_str) return GF_OUT_OF_MEM;
	memset(tmp_str, 0, sizeof(char)*tmp_strsize);

	while (tmp_strsize) {
		ISOM_DECREASE_SIZE(ptr, 1)
		tmp_str[i] = gf_bs_read_u8(bs);
		tmp_strsize--;
		if (!tmp_str[i])
			break;
		i++;
	}
	if (i) {
		ptr->movie_identifier = gf_strdup(tmp_str);
	}

	ISOM_DECREASE_SIZE(ptr, 1)
	ptr->server_entry_count = gf_bs_read_u8(bs);
	for (i=0; i<ptr->server_entry_count; i++) {
		int j=0;
		tmp_strsize=(u32)ptr->size;
		while (tmp_strsize) {
			ISOM_DECREASE_SIZE(ptr, 1)
			tmp_str[j] = gf_bs_read_u8(bs);
			tmp_strsize--;
			if (!tmp_str[j])
				break;
			j++;
		}
		if (j) {
			gf_list_insert(ptr->server_entry_table, gf_strdup(tmp_str), i);
		}
	}

	ISOM_DECREASE_SIZE(ptr, 1)
	ptr->quality_entry_count = gf_bs_read_u8(bs);
	for (i=0; i<ptr->quality_entry_count; i++) {
		int j=0;
		tmp_strsize=(u32)ptr->size;
		while (tmp_strsize) {
			ISOM_DECREASE_SIZE(ptr, 1)
			tmp_str[j] = gf_bs_read_u8(bs);
			tmp_strsize--;
			if (!tmp_str[j])
				break;
			j++;
		}

		if (j) {
			gf_list_insert(ptr->quality_entry_table, gf_strdup(tmp_str), i);
		}
	}

	i=0;
	tmp_strsize=(u32)ptr->size;
	while (tmp_strsize) {
		ISOM_DECREASE_SIZE(ptr, 1)
		tmp_str[i] = gf_bs_read_u8(bs);
		tmp_strsize--;
		if (!tmp_str[i])
			break;
		i++;
	}
	if (i) {
		ptr->drm_data = gf_strdup(tmp_str);
	}

	i=0;
	tmp_strsize=(u32)ptr->size;
	while (tmp_strsize) {
		ISOM_DECREASE_SIZE(ptr, 1)
		tmp_str[i] = gf_bs_read_u8(bs);
		tmp_strsize--;
		if (!tmp_str[i])
			break;
		i++;
	}
	if (i) {
		ptr->meta_data = gf_strdup(tmp_str);
	}

	ISOM_DECREASE_SIZE(ptr, 1)
	ptr->segment_run_table_count = gf_bs_read_u8(bs);
	for (i=0; i<ptr->segment_run_table_count; i++) {
		GF_AdobeSegmentRunTableBox *asrt = NULL;
		e = gf_isom_box_parse((GF_Box **)&asrt, bs);
		if (e) {
			if (asrt) gf_isom_box_del((GF_Box*)asrt);
			gf_free(tmp_str);
			return e;
		}
		gf_list_add(ptr->segment_run_table_entries, asrt);
	}

	ISOM_DECREASE_SIZE(ptr, 1)
	ptr->fragment_run_table_count = gf_bs_read_u8(bs);
	for (i=0; i<ptr->fragment_run_table_count; i++) {
		GF_AdobeFragmentRunTableBox *afrt = NULL;
		e = gf_isom_box_parse((GF_Box **)&afrt, bs);
		if (e) {
			if (afrt) gf_isom_box_del((GF_Box*)afrt);
			gf_free(tmp_str);
			return e;
		}
		gf_list_add(ptr->fragment_run_table_entries, afrt);
	}

	gf_free(tmp_str);

	return GF_OK;
}
/* ==== end verbatim target function ==== */

/* ---- driver ---------------------------------------------------------------------------
 * Input format (attacker-controlled file, read into a HEAP buffer):
 *   bytes[0..7] : box_size (u64 LE) -> the constructed box's own `.size` (the box's
 *                 declared remaining-content length, exactly what a real caller sets
 *                 right after parsing the box header + full-box version/flags, before
 *                 dispatching to abst_box_read).
 *   bytes[8..]  : fed verbatim as the GF_BitStream's own backing buffer (position 0 ==
 *                 the first byte abst_box_read's own body reads -- abst_box_read never
 *                 touches anything before that).
 *
 * TRIGGER (input/0..24): box_size == 33, so ptr->size==8 right after the 25-byte fixed
 * header -- tmp_str is allocated with (8-8)==0 BYTES -- and the bitstream's 26th byte
 * (server_entry_count) is non-zero. abst_box_read's own server_entry_table loop then
 * writes gf_bs_read_u8() straight into tmp_str[0]: an immediate heap-buffer-overflow
 * WRITE of size 1, inside abst_box_read's own body (CWE-787).
 * SAFE (input/25..49): either box_size too small to even clear the fixed-header /
 * size>=8 guards (a clean, early GF_ISOM_INVALID_FILE return, no allocation at all), or
 * box_size generous with movie_identifier long enough (>=8 content bytes) that by the
 * time any LATER string field is reached, enough of the box's declared size has already
 * been consumed that every subsequent `tmp_strsize=ptr->size` reset lands at or below
 * tmp_str's real capacity for the rest of the call (ptr->size only decreases, so once one
 * reset is in-bounds every later one stays in-bounds too) -- exercising
 * server_entry_table / quality_entry_table / drm_data / meta_data safely all the way to
 * abst_box_read's own `gf_free(tmp_str); return GF_OK;`.
 */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 64; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 64; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

    size_t n = (size_t)fsz;
    u8 *data = (u8 *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
    if (!data) { fclose(fp); return 64; }
    size_t got = n ? fread(data, 1, n, fp) : 0;
    fclose(fp);
    if (got != n) { free(data); return 64; }

    if (n < 8) { free(data); return 0; }   /* too small to carry box_size -> clean exit */

    u64 box_size = 0;
    { int k; for (k = 0; k < 8; k++) box_size |= ((u64)data[k]) << (8 * k); }

    const u8 *bsbuf = data + 8;
    u64 bslen = (u64)(n - 8);

    /* ---- construct the box the way abst_box_new() + a real header parse leave it ---- */
    GF_AdobeBootstrapInfoBox box;
    memset(&box, 0, sizeof(box));
    box.type = GF_ISOM_BOX_TYPE_ABST;
    box.size = box_size;
    box.server_entry_table = gf_list_new();
    box.quality_entry_table = gf_list_new();
    box.segment_run_table_entries = gf_list_new();
    box.fragment_run_table_entries = gf_list_new();

    GF_BitStream *bs = gf_bs_new(bsbuf, bslen, GF_BITSTREAM_READ);

    /* volatile function pointer: forbids inlining abst_box_read into main() so it keeps
     * its own frame in the ASAN report (dc_batch requires the target function name in the
     * crash stack). Same arguments/semantics as a direct call. */
    GF_Err (*volatile vb_call)(GF_Box *, GF_BitStream *) = abst_box_read;
    GF_Err e = vb_call((GF_Box *)&box, bs);
    (void)e;

    /* Only reached on a SAFE run (a triggering run aborts inside the call above).
     * detect_leaks=0 for this harness family -- no need to walk/free the GF_List entries
     * or the movie_identifier/drm_data/meta_data strings abst_box_read may have
     * allocated; freeing just the top-level objects this driver itself owns. */
    gf_bs_del(bs);
    free(data);
    return 0;
}

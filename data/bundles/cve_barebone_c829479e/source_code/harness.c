/* cve_barebone direct-call harness for cve_c829479e (gpac), fixed by
 * 758135e91e623d7dfe7f6aaad7aeb3f791b7a4e5 ("fixed possible issue in abst reading").
 * Target: abst_box_read  (src/isomedia/box_code_adobe.c)
 * Bug class: CWE-125 heap-buffer-overflow READ (missing NUL terminator -> strdup overread).
 * See the module docstring in scripts/gen_dc_cve_c829479e.py for the full root-cause writeup.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

/* ---- gpac/include/gpac/setup.h fixed-width typedefs (real names; hand-written -- the header
 * has 3 platform variants (Win32/__int64, WinCE, stdint.h) behind #ifdefs, this harness always
 * builds with the plain stdint.h branch that a Linux/clang build uses) ---- */
typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef uint8_t  u8;

/* gpac/include/gpac/setup.h (real names/values) */
typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

/* gpac/include/gpac/tools.h GF_Err enum (real names/values; subset actually referenced by
 * abst_box_read's own body -- GF_OK/GF_OUT_OF_MEM/GF_ISOM_INVALID_FILE -- plus GF_BAD_PARAM used
 * by the GF_List stand-in below) */
typedef enum {
	GF_OK                = 0,
	GF_BAD_PARAM          = -1,
	GF_OUT_OF_MEM          = -2,
	GF_ISOM_INVALID_FILE   = -20
} GF_Err;

/* gpac/include/gpac/setup.h / gpac/include/gpac/tools.h -- both are REAL "disabled" variants
 * already present in the header (non-Windows non-export-visibility build; no-log build), used
 * here to avoid pulling in the whole logging subsystem for a call that is purely diagnostic
 * (ISOM_DECREASE_SIZE's control flow -- the `if (size<bytes) return ...; size-=bytes;` part --
 * is unchanged either way; GF_LOG's own argument list, including the embedded gf_4cc_to_str()
 * call, is a macro PARAMETER this expansion never uses, so the preprocessor discards it whole --
 * gf_4cc_to_str need not even be declared). */
#define GF_EXPORT
#define GF_LOG(_ll, _lm, __args)

/* ---- gpac/src/utils/alloc.c STD_MALLOC path (real behavior: gf_malloc/gf_free/gf_strdup are
 * thin wrappers over malloc/free/strdup on a non-Windows non-memory-tracking build) ---- */
static void *gf_malloc(size_t size) { return malloc(size); }
static void gf_free(void *ptr) { free(ptr); }
static void *gf_realloc(void *ptr, size_t size) { return realloc(ptr, size); }
static char *gf_strdup(const char *str) { return str ? strdup(str) : NULL; }

/* ---- gpac/include/gpac/list.h: GF_List (real type name + real gf_list_new/del/add/insert
 * signatures). Never exercised by any input this harness's corpus constructs: abst_box_read only
 * touches server_entry_table/quality_entry_table via gf_list_insert, and only when
 * server_entry_count/quality_entry_count are nonzero -- every input here makes those bytes read
 * back as 0 (see the module docstring). A minimal array-backed stand-in is a faithful-enough
 * incidental dependency. */
typedef struct _tag_array { void **vals; u32 count; u32 alloc; } GF_List;
static GF_List *gf_list_new(void) {
	GF_List *l = (GF_List *) gf_malloc(sizeof(GF_List));
	if (l) { l->vals = NULL; l->count = 0; l->alloc = 0; }
	return l;
}
static void gf_list_del(GF_List *ptr) {
	if (!ptr) return;
	if (ptr->vals) gf_free(ptr->vals);
	gf_free(ptr);
}
static GF_Err gf_list_add(GF_List *ptr, void *item) {
	if (!ptr) return GF_BAD_PARAM;
	if (ptr->count == ptr->alloc) {
		u32 na = ptr->alloc ? ptr->alloc * 2 : 8;
		void **nv = (void **) gf_realloc(ptr->vals, sizeof(void *) * na);
		if (!nv) return GF_OUT_OF_MEM;
		ptr->vals = nv; ptr->alloc = na;
	}
	ptr->vals[ptr->count++] = item;
	return GF_OK;
}
static GF_Err gf_list_insert(GF_List *ptr, void *item, u32 position) {
	(void) position;   /* not on any path this harness's corpus reaches -- see comment above */
	return gf_list_add(ptr, item);
}

/* ---- gpac/include/gpac/bitstream.h L52-60 (verbatim): bitstream creation modes ---- */
enum
{
	/*! read-only mode*/
	GF_BITSTREAM_READ = 0,
	/*! read-write mode*/
	GF_BITSTREAM_WRITE,
	/*! allows reallocating the buffer passed in WRITE mode*/
	GF_BITSTREAM_WRITE_DYN
};

typedef struct __tag_bitstream GF_BitStream;

/* ---- gpac/src/utils/bitstream.c L38-78 (verbatim): struct __tag_bitstream ---- */
struct __tag_bitstream
{
	/*original stream data*/
	FILE *stream;

	/*or original data*/
	char *original;
	/*the size of our buffer in bytes*/
	u64 size;
	/*current position in BYTES*/
	u64 position;
	/*the byte readen/written*/
	u32 current;
	/*the number of bits in the current byte*/
	u32 nbBits;
	/*the bitstream mode*/
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
};


/* gpac/src/utils/bitstream.c L29 (verbatim constant, needed by the WRITE/WRITE_DYN branches of
 * the gf_bs_new slice below -- dead code here since this harness only ever passes
 * GF_BITSTREAM_READ, but the identifier must still resolve at compile time). */
#define BS_MEM_BLOCK_ALLOC_SIZE		512

/* ---- gpac/src/utils/bitstream.c L123-167 (verbatim): gf_bs_new, all 3 modes ---- */
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


/* ---- BS_ReadByte: faithful reduction of gpac/src/utils/bitstream.c's real BS_ReadByte to the
 * GF_BITSTREAM_READ branch -- the only mode this harness ever constructs. Bounds check is
 * byte-exact to the original (`if (bs->position >= bs->size) ... return 0;`), which is what makes
 * reads past the supplied input return 0 instead of an out-of-bounds access. The FILE-mode branch
 * (gf_feof/gf_bs_load_byte/gf_bs_seek) and the remove_emul_prevention_byte re-sync block are both
 * unreachable here (bsmode is always GF_BITSTREAM_READ; remove_emul_prevention_byte is left
 * GF_FALSE by gf_bs_new's memset) and are omitted rather than pulled in as extra
 * dead-code-only stub functions. ---- */
static u8 BS_ReadByte(GF_BitStream *bs)
{
	if (bs->position >= bs->size) {
		if (bs->EndOfStream) bs->EndOfStream(bs->par);
		return 0;
	}
	return (u8) bs->original[bs->position++];
}

/* ---- gpac/src/utils/bitstream.c L411-471 (verbatim): gf_bs_read_bit / gf_bs_read_int /
 * gf_bs_read_u8 (the #ifndef NO_OPTS branches fold out at preprocess time since NO_OPTS is
 * #define'd unconditionally right here, exactly as in the real file) ---- */
#define NO_OPTS

#ifndef NO_OPTS
static u32 bit_mask[] = {0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1};
static u32 bits_mask[] = {0x0, 0x1, 0x3, 0x7, 0xF, 0x1F, 0x3F, 0x7F};
#endif

GF_EXPORT
u8 gf_bs_read_bit(GF_BitStream *bs)
{
	if (bs->nbBits == 8) {
		bs->current = BS_ReadByte(bs);
		bs->nbBits = 0;
	}
#ifdef NO_OPTS
	{
		s32 ret;
		bs->current <<= 1;
		bs->nbBits++;
		ret = (bs->current & 0x100) >> 8;
		return (u8) ret;
	}
#else
	return (u8) (bs->current & bit_mask[bs->nbBits++]) ? 1 : 0;
#endif

}

GF_EXPORT
u32 gf_bs_read_int(GF_BitStream *bs, u32 nBits)
{
	u32 ret;

#ifndef NO_OPTS
	if (nBits + bs->nbBits <= 8) {
		bs->nbBits += nBits;
		ret = (bs->current >> (8 - bs->nbBits) ) & bits_mask[nBits];
		return ret;
	}
#endif
	ret = 0;
	while (nBits-- > 0) {
		ret <<= 1;
		ret |= gf_bs_read_bit(bs);
	}
	return ret;
}

GF_EXPORT
u32 gf_bs_read_u8(GF_BitStream *bs)
{
	assert(bs->nbBits==8);
	if (bs->cache_read && (bs->cache_read_pos+1<bs->cache_read_size) ) {
		u32 ret = bs->cache_read[bs->cache_read_pos];
		bs->cache_read_pos+=1;
		bs->position+=1;
		return ret;
	}

	return (u32) BS_ReadByte(bs);
}


/* ---- gpac/src/utils/bitstream.c L544-601 (verbatim): gf_bs_read_u32 + gf_bs_read_u64 ---- */
GF_EXPORT
u32 gf_bs_read_u32(GF_BitStream *bs)
{
	u32 ret;
	assert(bs->nbBits==8);

	if (bs->cache_read && (bs->cache_read_pos+4<bs->cache_read_size) ) {
		ret = bs->cache_read[bs->cache_read_pos];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+1];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+2];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+3];
		bs->cache_read_pos+=4;
		bs->position+=4;
		return ret;
	}
	ret = BS_ReadByte(bs);
	ret<<=8;
	ret |= BS_ReadByte(bs);
	ret<<=8;
	ret |= BS_ReadByte(bs);
	ret<<=8;
	ret |= BS_ReadByte(bs);
	return ret;
}

GF_EXPORT
u64 gf_bs_read_u64(GF_BitStream *bs)
{
	u64 ret;

	if (bs->cache_read && (bs->cache_read_pos+8<bs->cache_read_size) ) {
		ret = bs->cache_read[bs->cache_read_pos];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+1];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+2];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+3];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+4];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+5];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+6];
		ret<<=8;
		ret |= bs->cache_read[bs->cache_read_pos+7];
		bs->cache_read_pos+=8;
		bs->position+=8;
		return ret;
	}
	ret = gf_bs_read_u32(bs);
	ret<<=32;
	ret |= gf_bs_read_u32(bs);
	return ret;
}


/* ---- gpac/include/gpac/internal/isomedia_dev.h L556-576 (verbatim): GF_ISOM_BOX /
 * GF_ISOM_FULL_BOX / GF_ISOM_UUID_BOX field-list macros + GF_Box ---- */
struct box_registry_entry;   /* opaque -- only ever used as a pointer field, never dereferenced */

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

#define GF_ISOM_UUID_BOX	\
	GF_ISOM_BOX			\
	u8 uuid[16];		\
	u32 internal_4cc;		\

typedef struct
{
	GF_ISOM_BOX
} GF_Box;


/* ---- gpac/include/gpac/internal/isomedia_dev.h L594-598 (verbatim): ISOM_DECREASE_SIZE ---- */
#define ISOM_DECREASE_SIZE(__ptr, bytes)	if (__ptr->size < (bytes) ) {\
			GF_LOG(GF_LOG_ERROR, GF_LOG_CONTAINER, ("[isom] not enough bytes in box %s: %d left, reading %d (file %s, line %d)\n", gf_4cc_to_str(__ptr->type), (u32) __ptr->size, (bytes), __FILE__, __LINE__ )); \
			return GF_ISOM_INVALID_FILE; \
		}\
		__ptr->size -= bytes; \


/* ---- gpac/include/gpac/internal/isomedia_dev.h: the two child-box types abst_box_read only ever
 * NAMES (local pointer variables asrt/afrt) -- kept opaque since gf_isom_box_parse below is never
 * invoked by any input this harness constructs (segment_run_table_count and
 * fragment_run_table_count both always read back as 0 -- see the module docstring). */
typedef struct GF_AdobeSegmentRunTableBox GF_AdobeSegmentRunTableBox;
typedef struct GF_AdobeFragmentRunTableBox GF_AdobeFragmentRunTableBox;

/* ---- gpac/include/gpac/internal/isomedia_dev.h L3178-3201 (verbatim): struct
 * __adobe_bootstrap_info_box / GF_AdobeBootstrapInfoBox -- this is the field layout
 * abst_box_read's `ptr` operates on, so it must be byte-exact to the real header. ---- */
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
	//entries in these two lists are NOT registered with the box child_boxes because of the in-between 8 bits !!
	u8 segment_run_table_count;
	GF_List *segment_run_table_entries;
	u8 fragment_run_table_count;
	GF_List *fragment_run_table_entries;
} GF_AdobeBootstrapInfoBox;


/* ---- gpac/include/gpac/internal/isomedia_dev.h real signatures; minimal stand-ins -- never
 * invoked on this harness's crash path (see comment on the Adobe child-box typedefs above), so
 * their bodies are incidental. ---- */
static GF_Err gf_isom_box_parse(GF_Box **outBox, GF_BitStream *bs)
{
	(void) bs;
	if (outBox) *outBox = NULL;
	return GF_OK;
}
static void gf_isom_box_del(GF_Box *ptr)
{
	if (ptr) gf_free(ptr);
}

/* ============================================================================================
 * TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_c829479e/target/original_function.c
 * noinline is a pure codegen hint (added before the pasted text, not inside it) so the crash
 * keeps its own ASAN backtrace frame; main() also calls it through a volatile function pointer
 * for the same reason (belt-and-braces -- abst_box_read has external linkage and a single call
 * site, so -O1 is unlikely to inline it either way).
 * ============================================================================================ */
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
	tmp_strsize =(u32)ptr->size;
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

/* ---- driver ---------------------------------------------------------------------------------
 * Reads argv[1] into a HEAP buffer (malloc, ASAN-guarded) and feeds the WHOLE file to a
 * GF_BitStream, mirroring the real call site (the generic ISOBMFF box parser hands
 * abst_box_read a bitstream positioned at the box payload, with ptr->size already set to the
 * box's declared remaining size). box.size is set to the input length itself -- the normal
 * "declared box size == available bytes" relationship -- which is what makes the input file's
 * own layout directly control tmp_strsize for the movie_identifier field (see the module
 * docstring for the exact byte layout: 25 fixed-field bytes, then S0 = n-25
 * "movie_identifier" bytes). ---- */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 2; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 2; }
	long fsz = ftell(fp);
	if (fsz <= 0) { fclose(fp); return 0; }   /* empty/degenerate input: nothing to exercise */
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 2; }

	size_t n = (size_t) fsz;
	u8 *buf = (u8 *) malloc(n);                 /* HEAP input buffer, ASAN-guarded */
	if (!buf) { fclose(fp); return 2; }
	size_t got = fread(buf, 1, n, fp);
	fclose(fp);
	if (got != n) { free(buf); return 2; }

	GF_AdobeBootstrapInfoBox box;
	memset(&box, 0, sizeof(box));
	box.type = 0x61627374u;   /* 'abst', real 4CC -- not read anywhere in abst_box_read's body */
	box.size = (u64) n;       /* box declares its size == the bytes actually supplied */
	box.server_entry_table         = gf_list_new();
	box.quality_entry_table        = gf_list_new();
	box.segment_run_table_entries  = gf_list_new();
	box.fragment_run_table_entries = gf_list_new();

	GF_BitStream *bs = gf_bs_new(buf, (u64) n, GF_BITSTREAM_READ);
	if (!bs) { free(buf); return 2; }

	GF_Err (* volatile fn)(GF_Box *, GF_BitStream *) = abst_box_read;
	GF_Err e = fn((GF_Box *) &box, bs);
	(void) e;

	/* only reached on a SAFE run -- a triggering run aborts inside abst_box_read/strdup */
	if (box.movie_identifier) gf_free(box.movie_identifier);
	if (box.drm_data) gf_free(box.drm_data);
	if (box.meta_data) gf_free(box.meta_data);
	gf_list_del(box.server_entry_table);
	gf_list_del(box.quality_entry_table);
	gf_list_del(box.segment_run_table_entries);
	gf_list_del(box.fragment_run_table_entries);
	gf_free(bs);
	free(buf);
	return 0;
}

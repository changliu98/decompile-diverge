/*
 * cve_barebone direct-call harness for CVE (gpac Media_CheckDataEntry, src/isomedia/media.c)
 *
 * Target: Media_CheckDataEntry(GF_MediaBox *mdia, u32 dataEntryIndex)
 * Fix commit: 328def7d3b93847d64ecb6e9e0399684e57c3eca ("fixed #1766 (fuzz)")
 *
 * Pre-fix body (verbatim below):
 *     entry = (GF_DataEntryURLBox*) gf_list_get(mdia->information->dataInformation->dref->child_boxes,
 *                                                dataEntryIndex - 1);
 *     if (!entry) return GF_ISOM_INVALID_FILE;
 *     if (entry->flags == 1) return GF_OK;
 *     if (entry->type == GF_ISOM_BOX_TYPE_URN) return GF_NOT_SUPPORTED;
 *     ... gf_isom_datamap_new(entry->location, ...)
 *
 * `entry` is whatever box object actually sits in the "dref" box's child list, blindly cast to
 * GF_DataEntryURLBox*. Pre-fix, the ONLY rejected type is 'urn '; any other box type is treated as
 * if it had the entry's flags/location layout. The fix (this commit) tightens that to an allow-list
 * ("we only support alias and URL boxes"): only 'url ' and QuickTime 'alis' pass; everything else is
 * now rejected via `return GF_NOT_SUPPORTED` BEFORE the flags/location fields are ever read.
 *
 * Real GPAC box layout (include/gpac/internal/isomedia_dev.h):
 *   #define GF_ISOM_BOX  u32 type; u64 size; const struct box_registry_entry *registry;
 *                        GF_List *child_boxes; u16 internal_flags; u16 version;
 *   #define GF_ISOM_FULL_BOX  GF_ISOM_BOX  u32 flags;
 *   #define GF_ISOM_DATAENTRY_FIELDS  char *location;
 *   typedef struct { GF_ISOM_FULL_BOX GF_ISOM_DATAENTRY_FIELDS } GF_DataEntryURLBox;   // 48 bytes
 *   typedef struct { GF_ISOM_BOX } GF_WideBox; /-* Apple *-/                            // 40 bytes
 * GF_WideBox is a REAL, registered GPAC box type -- the QuickTime "wide" placeholder/reserve box,
 * box_funcs.c: `BOX_DEFINE_S(GF_QT_BOX_TYPE_WIDE, wide, "*", "apple")` -- the "*" parents_4cc means
 * it is a globally legal child of ANY container, including "dref". It has no flags/location field:
 * its whole allocation (bare GF_ISOM_BOX header, 40 bytes after struct alignment padding) is exactly
 * 8 bytes SHORTER than GF_DataEntryURLBox (48 bytes) -- the size of the `location` char* field.
 *
 * So: a dref box whose child is a 'wide' box (entirely plausible from a malformed/crafted QuickTime-
 * flavored .mov -- 'wide' commonly appears as a reserve/placeholder box in real files, and GPAC's own
 * registry admits it anywhere) reproduces exactly the class of bug the fix closes. Pre-fix:
 *   - entry->flags   (offset 36, u32) reads the last 4 bytes of the 40-byte GF_WideBox allocation
 *                     -- in bounds (struct tail padding), reads 0 (calloc'd) -- not the early-out.
 *   - entry->type    (offset 0, u32)  is the box's REAL header field -- in bounds, reads
 *                     GF_QT_BOX_TYPE_WIDE, which != GF_ISOM_BOX_TYPE_URN -- pre-fix code proceeds.
 *   - entry->location (offset 40, char*, 8 bytes) is read to build the gf_isom_datamap_new() call
 *                     args -- OUT OF BOUNDS: the 40-byte heap allocation ends exactly at offset 40,
 *                     so this is a clean 8-byte heap-buffer-overflow READ (CWE-125). The load happens
 *                     while Media_CheckDataEntry evaluates the call argument, i.e. entirely inside
 *                     Media_CheckDataEntry's own body/frame -- gf_isom_datamap_new is never actually
 *                     entered on the triggering path.
 *
 * gf_list_count/gf_list_get (src/utils/list.c, GF_LIST_ARRAY_GROW mode -- the active one: only
 * _WIN32_WCE takes the linked-list mode) are copied verbatim, since Media_CheckDataEntry calls them
 * directly. gf_isom_datamap_new/gf_isom_datamap_del (src/isomedia/data_map.c) are incidental to the
 * bug (the triggering path crashes before they would ever run) -- minimal faithful always-OK stand-
 * ins matching their real signatures (isomedia_dev.h:3868-3869), so the SAFE "full execution" input
 * (mode 4 below) can still exercise every line of the function without doing real file/network I/O.
 *
 * Harness I/O contract (single HEAP-allocated attacker buffer, argv[1]):
 *   byte[0] selects the mode (clamped to [0,4], default 1 if empty/out of range):
 *     0 = TRIGGER  : dref's one child is a 'wide' box (GF_WideBox, 40 B)      -> heap-OOB READ
 *     1 = SAFE     : dref's one child is a well-formed self-contained 'url '
 *                    entry (GF_DataEntryURLBox, 48 B, flags=1)                -> early GF_OK
 *     2 = SAFE     : dref's one child is a well-formed 'urn ' entry
 *                    (GF_DataEntryURNBox, 56 B, flags=0)                      -> GF_NOT_SUPPORTED
 *     3 = SAFE     : dataEntryIndex == 0 (invalid)                            -> GF_BAD_PARAM
 *     4 = SAFE     : well-formed 'url ' entry, flags=0, location = heap
 *                    NUL-terminated copy of byte[1..] (attacker content)      -> full body incl.
 *                                                                                the (stubbed) datamap
 *                                                                                open/close, GF_OK
 *   byte[1..] are only consumed by mode 4 (become the `location` string, verbatim, NUL-terminated).
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ==== primitive typedefs (include/gpac/setup.h, Linux/64-bit branch) ==== */
typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

/* ==== include/gpac/tools.h ==== */
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))

/* ==== include/gpac/tools.h: GF_Err (trimmed to the values this file needs) ==== */
typedef enum
{
	GF_OK                   = 0,
	GF_BAD_PARAM             = -1,
	GF_OUT_OF_MEM            = -2,
	GF_NOT_SUPPORTED         = -4,
	GF_ISOM_INVALID_FILE     = -20
} GF_Err;

/* ==== include/gpac/internal/isomedia_dev.h: box header macros (verbatim) ==== */
struct box_registry_entry; /* opaque, only ever referenced by pointer */
typedef struct _tag_array GF_List;

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

/* ==== include/gpac/list.h + src/utils/list.c (GF_LIST_ARRAY_GROW mode -- the active one; only
 * _WIN32_WCE takes GF_LIST_LINKED). Media_CheckDataEntry calls gf_list_count/gf_list_get directly,
 * so these are copied VERBATIM, not stubbed. gf_malloc/gf_free/gf_realloc resolve, in a non
 * GPAC_MEMORY_TRACKING build, to plain malloc/free/realloc (src/utils/alloc.c: gf_malloc ==
 * MALLOC(size) == malloc(size) by default) -- faithful non-tracking-build behavior. ==== */
#define gf_malloc  malloc
#define gf_free    free
#define gf_realloc realloc

struct _tag_array
{
	void **slots;
	u32 entryCount;
	u32 allocSize;
};

#define GF_LIST_REALLOC(a) (a = a ? (3*a/2) : 10)

GF_List *gf_list_new(void)
{
	GF_List *nlist = (GF_List *) gf_malloc(sizeof(GF_List));
	if (! nlist) return NULL;

	nlist->slots = NULL;
	nlist->entryCount = 0;
	nlist->allocSize = 0;
	return nlist;
}

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

u32 gf_list_count(const GF_List *ptr)
{
	if (!ptr) return 0;
	return ptr->entryCount;
}

void *gf_list_get(GF_List *ptr, u32 itemNumber)
{
	if(!ptr || (itemNumber >= ptr->entryCount))
		return NULL;
	return ptr->slots[itemNumber];
}

/* ==== include/gpac/internal/isomedia_dev.h: the box types on the access chain, trimmed to the
 * fields Media_CheckDataEntry actually dereferences (real names throughout). ==== */

typedef struct
{
	GF_ISOM_FULL_BOX
} GF_DataReferenceBox;

typedef struct
{
	GF_ISOM_BOX
	GF_DataReferenceBox *dref;
} GF_DataInformationBox;

typedef struct
{
	GF_ISOM_BOX
	GF_DataInformationBox *dataInformation;
} GF_MediaInformationBox;

/* include/gpac/isomedia.h: GF_ISOOpenMode (verbatim, small enum) */
typedef enum
{
	GF_ISOM_OPEN_READ_DUMP = 0,
	GF_ISOM_OPEN_READ,
	GF_ISOM_OPEN_WRITE,
	GF_ISOM_OPEN_EDIT,
	GF_ISOM_WRITE_EDIT,
	GF_ISOM_OPEN_KEEP_FRAGMENTS,
	GF_ISOM_OPEN_READ_EDIT,
} GF_ISOOpenMode;

/* struct __tag_isom (isomedia_dev.h), trimmed to the two fields read on the access chain */
typedef struct
{
	GF_ISOOpenMode openMode;
	char *fileName;
} GF_ISOFile;

typedef struct
{
	GF_ISOM_BOX
	GF_ISOFile *mov;
} GF_MovieBox;

typedef struct
{
	GF_ISOM_BOX
	GF_MovieBox *moov;
} GF_TrackBox;

typedef struct __tag_media_box
{
	GF_ISOM_BOX
	GF_TrackBox *mediaTrack;
	GF_MediaInformationBox *information;
} GF_MediaBox;

/* ==== the data-entry box family (isomedia_dev.h) -- real macro + real struct names ==== */
#define GF_ISOM_DATAENTRY_FIELDS	\
	char *location;

typedef struct
{
	GF_ISOM_FULL_BOX
	GF_ISOM_DATAENTRY_FIELDS
} GF_DataEntryURLBox;                 /* 48 bytes: header(36) + flags(4) + location(8) */

typedef struct
{
	GF_ISOM_FULL_BOX
	GF_ISOM_DATAENTRY_FIELDS
	char *nameURN;
} GF_DataEntryURNBox;                 /* 56 bytes */

/* the QuickTime "wide" placeholder box -- bare GF_ISOM_BOX, no flags/location field (40 bytes) */
typedef struct
{
	GF_ISOM_BOX
} GF_WideBox; /*Apple*/

/* box type FourCCs actually tested by Media_CheckDataEntry / used to build test entries
 * (isomedia_dev.h enum, real byte sequences via the real GF_4CC macro) */
#define GF_ISOM_BOX_TYPE_URL	GF_4CC( 'u', 'r', 'l', ' ' )
#define GF_ISOM_BOX_TYPE_URN	GF_4CC( 'u', 'r', 'n', ' ' )
#define GF_QT_BOX_TYPE_WIDE	GF_4CC('w','i','d','e')

/* ==== include/gpac/internal/isomedia_dev.h: GF_DataMap + gf_isom_datamap_new/del ====
 * (src/isomedia/data_map.c). Real opaque-handle name + real prototypes (isomedia_dev.h:3868-3869).
 * Incidental to the bug (see header comment) -- minimal always-OK stand-ins, never dereference
 * *location (only the pointer VALUE is consumed, via the volatile sink below -- this stub is not
 * where the fault is). ==== */
typedef struct __tag_data_map
{
	int _unused;
} GF_DataMap;

#define GF_ISOM_DATA_MAP_READ 1

/* `location` is dead-on-arrival in the stub below (never dereferenced), which is enough for an
 * optimizing compiler to prove Media_CheckDataEntry's `entry->location` LOAD has no observable
 * effect and eliminate it *before* ASan instrumentation ever sees it -- silently defeating the
 * whole reproduction (confirmed empirically at -O1: without this sink the harness runs clean).
 * Routing the pointer VALUE through a volatile-QUALIFIED-POINTER global forces the load to
 * actually happen; the load itself (offset 40 of the 40-byte GF_WideBox allocation, see header
 * comment) is the fault, independent of whatever value ends up in the sink.
 *   NOTE the qualifier placement: `T * volatile p` makes the POINTER VARIABLE p volatile (every
 * store to p is a distinct, non-elidable side effect); `volatile T * p` (what an earlier version
 * of this stub used) instead makes the POINTEE volatile and leaves p itself an ordinary variable,
 * so two back-to-back assignments to it are just a ordinary dead store the optimizer legitimately
 * removes -- confirmed empirically to silently reproduce the exact same false-clean symptom. Two
 * separate sink variables (rather than one sink written twice) sidesteps the question entirely. */
static const void * volatile g_vb_sink_location;
static const void * volatile g_vb_sink_parent;

GF_Err gf_isom_datamap_new(const char *location, const char *parentPath, u8 mode, GF_DataMap **outDataMap)
{
	g_vb_sink_location = location;
	g_vb_sink_parent = parentPath;
	(void)mode;
	GF_DataMap *dm = (GF_DataMap *) calloc(1, sizeof(GF_DataMap));
	if (!dm) return GF_OUT_OF_MEM;
	*outDataMap = dm;
	return GF_OK;
}

void gf_isom_datamap_del(GF_DataMap *ptr)
{
	free(ptr);
}

/* ==== VERBATIM from data_cve/cve_9d1b049c/target/original_function.c ==== */
GF_Err Media_CheckDataEntry(GF_MediaBox *mdia, u32 dataEntryIndex)
{

	GF_DataEntryURLBox *entry;
	GF_DataMap *map;
	GF_Err e;
	if (!mdia || !dataEntryIndex || dataEntryIndex > gf_list_count(mdia->information->dataInformation->dref->child_boxes)) return GF_BAD_PARAM;

	entry = (GF_DataEntryURLBox*)gf_list_get(mdia->information->dataInformation->dref->child_boxes, dataEntryIndex - 1);
	if (!entry) return GF_ISOM_INVALID_FILE;
	if (entry->flags == 1) return GF_OK;

	//ok, not self contained, let's go for it...
	//we don't know what's a URN yet
	if (entry->type == GF_ISOM_BOX_TYPE_URN) return GF_NOT_SUPPORTED;
	if (mdia->mediaTrack->moov->mov->openMode == GF_ISOM_OPEN_WRITE) {
		e = gf_isom_datamap_new(entry->location, NULL, GF_ISOM_DATA_MAP_READ, &map);
	} else {
		e = gf_isom_datamap_new(entry->location, mdia->mediaTrack->moov->mov->fileName, GF_ISOM_DATA_MAP_READ, &map);
	}
	if (e) return e;
	gf_isom_datamap_del(map);
	return GF_OK;
}
/* ==== end verbatim ==== */

static unsigned char *read_file(const char *path, size_t *out_n)
{
	FILE *f = fopen(path, "rb");
	if (!f) return NULL;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
	long sz = ftell(f);
	if (sz < 0) { fclose(f); return NULL; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
	unsigned char *buf = (unsigned char *) malloc((size_t) sz > 0 ? (size_t) sz : 1);
	if (!buf) { fclose(f); return NULL; }
	size_t n = fread(buf, 1, (size_t) sz, f);
	fclose(f);
	*out_n = n;
	return buf;
}

int main(int argc, char **argv)
{
	if (argc < 2) return 0;
	size_t n = 0;
	unsigned char *in = read_file(argv[1], &n);
	if (!in) return 0;

	unsigned mode = (n >= 1) ? in[0] : 1;
	if (mode > 4) mode = 1;

	/* mdia -> mediaTrack -> moov -> mov -> {openMode, fileName}
	 * mdia -> information -> dataInformation -> dref -> child_boxes  (one entry) */
	GF_ISOFile *isof = (GF_ISOFile *) calloc(1, sizeof(GF_ISOFile));
	isof->openMode = (mode == 4) ? GF_ISOM_OPEN_READ : GF_ISOM_OPEN_WRITE;
	isof->fileName = "vb_dc_input.mp4";

	GF_MovieBox *moov = (GF_MovieBox *) calloc(1, sizeof(GF_MovieBox));
	moov->mov = isof;

	GF_TrackBox *trak = (GF_TrackBox *) calloc(1, sizeof(GF_TrackBox));
	trak->moov = moov;

	GF_DataReferenceBox *dref = (GF_DataReferenceBox *) calloc(1, sizeof(GF_DataReferenceBox));
	dref->child_boxes = gf_list_new();

	GF_DataInformationBox *dinf = (GF_DataInformationBox *) calloc(1, sizeof(GF_DataInformationBox));
	dinf->dref = dref;

	GF_MediaInformationBox *minf = (GF_MediaInformationBox *) calloc(1, sizeof(GF_MediaInformationBox));
	minf->dataInformation = dinf;

	GF_MediaBox *mdia = (GF_MediaBox *) calloc(1, sizeof(GF_MediaBox));
	mdia->mediaTrack = trak;
	mdia->information = minf;

	u32 dataEntryIndex = 1;
	void *entry_obj = NULL;

	if (mode == 0) {
		/* TRIGGER: real 'wide' placeholder box (40 B) where a GF_DataEntryURLBox (48 B) is
		 * expected -- see header comment. */
		GF_WideBox *wide = (GF_WideBox *) calloc(1, sizeof(GF_WideBox));
		wide->type = GF_QT_BOX_TYPE_WIDE;
		entry_obj = wide;
	} else if (mode == 1) {
		/* SAFE: well-formed self-contained 'url ' entry -- flags==1 early return. */
		GF_DataEntryURLBox *url = (GF_DataEntryURLBox *) calloc(1, sizeof(GF_DataEntryURLBox));
		url->type = GF_ISOM_BOX_TYPE_URL;
		url->flags = 1;
		url->location = NULL;
		entry_obj = url;
	} else if (mode == 2) {
		/* SAFE: well-formed 'urn ' entry -- rejected by the pre-fix URN check before location
		 * is ever touched (the one case the pre-fix code got right). */
		GF_DataEntryURNBox *urn = (GF_DataEntryURNBox *) calloc(1, sizeof(GF_DataEntryURNBox));
		urn->type = GF_ISOM_BOX_TYPE_URN;
		urn->flags = 0;
		urn->location = NULL;
		urn->nameURN = NULL;
		entry_obj = urn;
	} else if (mode == 3) {
		/* SAFE: invalid dataEntryIndex (0) -- rejected by the function's own bounds check
		 * before any list access. */
		GF_DataEntryURLBox *url = (GF_DataEntryURLBox *) calloc(1, sizeof(GF_DataEntryURLBox));
		url->type = GF_ISOM_BOX_TYPE_URL;
		url->flags = 0;
		url->location = (char *) "x";
		entry_obj = url;
		dataEntryIndex = 0;
	} else {
		/* mode == 4: SAFE, full-execution path -- well-formed 'url ' entry, not self-
		 * contained, real heap NUL-terminated location string built from the input bytes ->
		 * falls through to the (stubbed) gf_isom_datamap_new/gf_isom_datamap_del. */
		GF_DataEntryURLBox *url = (GF_DataEntryURLBox *) calloc(1, sizeof(GF_DataEntryURLBox));
		url->type = GF_ISOM_BOX_TYPE_URL;
		url->flags = 0;
		size_t rem = (n > 1) ? (n - 1) : 0;
		char *loc = (char *) malloc(rem + 1);
		if (rem) memcpy(loc, in + 1, rem);
		loc[rem] = '\0';
		url->location = loc;
		entry_obj = url;
	}

	gf_list_add(dref->child_boxes, entry_obj);

	/* indirect call: keeps Media_CheckDataEntry a real, un-inlined ASAN frame */
	GF_Err (*target)(GF_MediaBox *, u32) = Media_CheckDataEntry;
	GF_Err e = target(mdia, dataEntryIndex);
	fprintf(stderr, "mode=%u dataEntryIndex=%u e=%d\n", mode, dataEntryIndex, (int) e);

	free(in);
	return 0;
}

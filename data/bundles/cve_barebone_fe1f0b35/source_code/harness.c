/*
 * Direct-call crash harness for cve_fe1f0b35 (gpac, src/isomedia/hint_track.c,
 * GetHintFormat()). Embeds the vulnerable function VERBATIM and calls it
 * directly on a hand-built `GF_TrackBox` object graph, so ASan catches the
 * exact NULL-pointer dereference this CVE describes with no dependency on
 * the rest of libgpac (box parsing, the ISO-BMFF reader, etc.).
 *
 * Bug recap (fix commit ad18ece95fa064efc0995c4ab2c985f77fb166ec):
 *
 *     GF_HintMediaHeaderBox *hmhd = (GF_HintMediaHeaderBox *)trak->Media->information->InfoHeader;
 *     if (hmhd->type != GF_ISOM_BOX_TYPE_HMHD)      <-- CWE-476: hmhd deref'd with NO NULL check
 *         return 0;
 *
 *     if (!hmhd || !hmhd->subType) { ... }          <-- the "!hmhd" guard here is dead code:
 *                                                        by this point hmhd was ALREADY dereferenced
 *
 * `trak->Media->information->InfoHeader` is a `GF_Box *` that a track's media-
 * information box carries when a "hint media header" (hmhd) box is present in
 * the file; for a track whose hinting media-info box has NOT been read/created
 * (e.g. malformed or truncated moov with a hint-track handler but no hmhd
 * child), `InfoHeader` is NULL, `hmhd` is NULL, and the very first statement
 * dereferences it -> SIGSEGV at address 0, inside GetHintFormat() itself. The
 * fix (commit ad18ece9) adds the missing `!hmhd ||` to the FIRST check. The
 * fault is entirely local to GetHintFormat(): it only needs a `GF_TrackBox`
 * whose Media/information chain is wired up but whose InfoHeader is NULL.
 *
 * `original_function.c` is embedded byte-for-byte below (see the VERBATIM
 * markers) -- logic, names, and signature untouched.
 *
 * harness.flags: `-fno-delete-null-pointer-checks`. GetHintFormat's own
 * SECOND check (`if (!hmhd || ...)`) textually re-tests the SAME pointer
 * already dereferenced by the FIRST check one line above; at -O1 clang's
 * default `-fdelete-null-pointer-checks` legally exploits "dereferencing
 * NULL is UB" to reason backward from that redundant later check and elides
 * the materialization of the FIRST (real, attacker-triggerable) load, so the
 * SIGSEGV silently disappears -- not a change to the bug, just clang
 * optimizing around it the same way `-fno-delete-null-pointer-checks`
 * exists to prevent for this exact source pattern elsewhere (e.g. the Linux
 * kernel builds with it project-wide for the identical reason).
 *
 * Build (dc_batch.py/dc_try.py, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm \
 *     -fno-delete-null-pointer-checks
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- gpac/setup.h: real base typedefs ---- */
typedef uint64_t u64;
typedef int64_t  s64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef int16_t  s16;
typedef uint8_t  u8;
typedef int8_t   s8;

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

/* ---- gpac/tools.h: real 4CC constant builder ---- */
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))

/* ---- gpac/internal/isomedia_dev.h: real box-type constant GetHintFormat
 * compares hmhd->type against ---- */
#define GF_ISOM_BOX_TYPE_HMHD	GF_4CC( 'h', 'm', 'h', 'd' )

/* ---- gpac/list.h: real opaque list typedef; `struct box_registry_entry` is
 * likewise only ever forward-referenced (as a pointer) in the real header,
 * never defined there either -- both incomplete types are reproduced exactly
 * at the level the real macro needs. ---- */
typedef struct _tag_array GF_List;
struct box_registry_entry;

/* ---- gpac/internal/isomedia_dev.h: the real GF_ISOM_BOX / GF_ISOM_FULL_BOX
 * field-list macros, copied verbatim, and the real box structs GetHintFormat's
 * pointer chain walks through (trimmed to the fields it actually touches --
 * the omitted sibling fields of these (large, many-hundred-line) box structs
 * play no role in this function and are not referenced). ---- */
#define GF_ISOM_BOX			\
	u32 type;				\
	u64 size;				\
	const struct box_registry_entry *registry;\
	GF_List *child_boxes; 	\
	u16 internal_flags;		\
	u16 version;

#define GF_ISOM_FULL_BOX		\
	GF_ISOM_BOX			\
	u32 flags;

typedef struct
{
	GF_ISOM_BOX
} GF_Box;

typedef struct
{
	GF_ISOM_FULL_BOX
	/*this is used for us INTERNALLY*/
	u32 subType;
	u32 maxPDUSize;
	u32 avgPDUSize;
	u32 maxBitrate;
	u32 avgBitrate;
	u32 slidingAverageBitrate;
} GF_HintMediaHeaderBox;

typedef struct
{
	GF_ISOM_FULL_BOX
} GF_SampleDescriptionBox;

typedef struct
{
	GF_ISOM_BOX
	GF_SampleDescriptionBox *SampleDescription;
} GF_SampleTableBox;

typedef struct __tag_media_info_box
{
	GF_ISOM_BOX
	GF_SampleTableBox *sampleTable;
	GF_Box *InfoHeader;
} GF_MediaInformationBox;

typedef struct __tag_media_box
{
	GF_ISOM_BOX
	struct __tag_media_info_box *information;
} GF_MediaBox;

typedef struct
{
	GF_ISOM_BOX
	struct __tag_media_box *Media;
} GF_TrackBox;

/* ---- gpac/list.h callee (only reached on the SAFE `subType==0` fallback
 * path, never on the crash path): `struct _tag_array` is opaque in the real
 * public header (defined only in list.c), so this is a minimal faithful
 * stand-in implementing gf_list_get()'s documented contract exactly --
 * "Gets an item from the list given its position ... return the item or NULL
 * if not found" -- real function name/signature/semantics, array layout is
 * an internal implementation detail the real header never exposes either. */
struct _tag_array {
	void **entries;
	u32 count;
};

void *gf_list_get(GF_List *ptr, u32 position)
{
	if (!ptr) return NULL;
	if (position >= ptr->count) return NULL;
	return ptr->entries[position];
}

/* ==== VERBATIM from data_cve/cve_fe1f0b35/target/original_function.c ==== */
u32 GetHintFormat(GF_TrackBox *trak)
{
	GF_HintMediaHeaderBox *hmhd = (GF_HintMediaHeaderBox *)trak->Media->information->InfoHeader;
	if (hmhd->type != GF_ISOM_BOX_TYPE_HMHD)
		return 0;
		
	if (!hmhd || !hmhd->subType) {
		GF_Box *a = (GF_Box *)gf_list_get(trak->Media->information->sampleTable->SampleDescription->child_boxes, 0);
		if (!hmhd) return a ? a->type : 0;
		if (a) hmhd->subType = a->type;
		return hmhd->subType;
	}
	return hmhd->subType;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long len = ftell(f);
	if (len < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* REQUIRED: heap buffer for the attacker-controlled bytes. */
	size_t alloc = (len > 0) ? (size_t)len : 1;
	unsigned char *buf = (unsigned char *)malloc(alloc);
	if (!buf) { fclose(f); return 1; }
	size_t rd = fread(buf, 1, alloc, f);
	fclose(f);
	if (rd < 1) { free(buf); return 1; }

	unsigned char mode = buf[0];
	unsigned char b1 = (rd > 1) ? buf[1] : 0;
	unsigned char b2 = (rd > 2) ? buf[2] : 0;

	/* Build the GF_TrackBox object graph GetHintFormat() walks. Everything
	 * except InfoHeader is always wired up to a valid, zeroed object so the
	 * ONLY thing an input controls is exactly the condition the fix commit
	 * guards against (InfoHeader present or NULL) plus, on the safe side,
	 * which of GetHintFormat's own non-crashing branches runs. */
	GF_TrackBox trak; memset(&trak, 0, sizeof(trak));
	GF_MediaBox media; memset(&media, 0, sizeof(media));
	GF_MediaInformationBox minf; memset(&minf, 0, sizeof(minf));
	GF_SampleTableBox stbl; memset(&stbl, 0, sizeof(stbl));
	GF_SampleDescriptionBox stsd; memset(&stsd, 0, sizeof(stsd));
	GF_HintMediaHeaderBox hmhd; memset(&hmhd, 0, sizeof(hmhd));
	GF_Box childbox; memset(&childbox, 0, sizeof(childbox));
	void *entries[1];
	struct _tag_array childlist; memset(&childlist, 0, sizeof(childlist));

	trak.Media = &media;
	media.information = &minf;
	minf.sampleTable = &stbl;
	stbl.SampleDescription = &stsd;

	/*
	 * Harness-only convention (there is no such marker in the real ISOBMFF
	 * wire format -- direct-call harnesses necessarily invent SOME mapping
	 * from "a corpus file" to "the argument the target function actually
	 * takes"): the LSB of the first input byte selects the crash path,
	 * reproducing InfoHeader==NULL exactly as an under-populated media-
	 * information box would produce it for a hint track parsed without a
	 * hmhd child box present. Because the CWE-476 crash depends ONLY on the
	 * pointer being NULL (GetHintFormat faults on hmhd->type before it ever
	 * looks at any other field), whatever bytes follow the mode byte are
	 * irrelevant to the crash outcome -- they exist purely to give the
	 * corpus files length/byte-pattern variety.
	 *
	 * Any OTHER (mode-bit-clear) input builds a real, valid hmhd box, so the
	 * fixed guard is a no-op and GetHintFormat runs its normal logic to
	 * completion (the safe / non-null path, matching a well-formed hint
	 * track). A second bit further selects between GetHintFormat's two
	 * non-crashing branches (direct subType return vs. the gf_list_get()
	 * child-box fallback when subType==0), both exercised safely.
	 */
	if (mode & 1) {
		/* TRIGGERING: InfoHeader missing -> hmhd is NULL -> hmhd->type is a
		 * NULL-pointer dereference (CWE-476), exactly the bug the fix commit
		 * closes by adding "!hmhd ||" to this first check. */
		minf.InfoHeader = NULL;
	} else {
		/* SAFE: a real, well-formed hmhd box is present. */
		hmhd.type = GF_ISOM_BOX_TYPE_HMHD;
		minf.InfoHeader = (GF_Box *)&hmhd;
		if (b1 & 1) {
			/* non-zero subType -> direct return, no sampleTable walk */
			hmhd.subType = b1 ? (u32)b1 : 1u;
		} else {
			/* subType == 0 -> exercises the gf_list_get() fallback with a
			 * fully-wired, valid one-entry child list */
			hmhd.subType = 0;
			childbox.type = 0x61626364u ^ (u32)b2;
			entries[0] = &childbox;
			childlist.entries = entries;
			childlist.count = 1;
			stsd.child_boxes = (GF_List *)&childlist;
		}
	}

	u32 result = GetHintFormat(&trak);
	printf("GetHintFormat -> %u\n", (unsigned)result);

	free(buf);
	return 0;
}

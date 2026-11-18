/* cve_barebone direct-call harness for cve_b5e1e10a (gpac)
 * Target: print_udta  (applications/mp4box/filedump.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * fix_commit eb71812fcc10e9c5348a5d1c61bd25b6fa06eaed guarded
 * `if (gf_utf8_is_legal(udta, udta_size))` with `udta_size &&` and replaced
 * `fprintf(stderr, "\t%s\n", (char *) udta)` with a loop bounded by udta_size. The
 * pre-fix code assumes the (udta, udta_size) buffer returned by gf_isom_get_user_data()
 * -- raw, attacker-controlled box bytes -- is NUL-terminated within udta_size. It is not:
 * a zero-length item (gf_utf8_is_legal(ptr,0) is vacuously TRUE) or a fully-legal-UTF8
 * item with no embedded NUL both make `%s` scan past the heap allocation.
 *
 * TRIGGER: udta content is legal-UTF8 (or empty) and contains NO NUL byte anywhere in
 *          [0, udta_size) -> `%s` reads past the udta_size-byte heap allocation ->
 *          ASAN heap-buffer-overflow READ inside print_udta's own fprintf call.
 * SAFE:    udta content either contains an embedded NUL within bounds (the `%s` scan
 *          terminates in-bounds) or opens with an illegal-UTF8 byte (gf_utf8_is_legal
 *          returns FALSE, the print is skipped entirely) -> no crash.
 *
 * Isolation: the ISOM box-accessor layer (gf_isom_get_udta_count/get_udta_type/
 * get_user_data_count/get_user_data) is stubbed -- one udta entry, one item, whose
 * (udta, udta_size) IS the raw input file, exactly what those accessors would return for
 * a crafted single-item box without replaying the whole ISOM box-tree parser.
 * gf_utf8_is_legal is copied VERBATIM (with its private helper tables) from
 * src/utils/utf.c since it is literally the predicate the fix re-guards, not incidental.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- gpac base typedefs (real names, include/gpac/setup.h, non-Win32/non-Symbian
 * "Unix" branch, setup.h:296-355) ---- */
typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t  s32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef u8 bin128[16];                       /* include/gpac/setup.h:374 */
typedef enum { GF_FALSE = 0, GF_TRUE } Bool; /* include/gpac/setup.h:413-418 */

/* ---- include/gpac/tools.h: GF_Err (only GF_OK is ever produced here; print_udta
 * itself never inspects the return value of any gf_isom_get_* call). ---- */
typedef enum { GF_OK = 0, GF_BAD_PARAM = -1 } GF_Err;

/* ---- include/gpac/tools.h:73 / isomedia_dev.h:249 (verbatim macros) ---- */
#define GF_4CC(a,b,c,d) ((((u32)a)<<24)|(((u32)b)<<16)|(((u32)c)<<8)|((u32)d))
#define GF_ISOM_BOX_TYPE_META GF_4CC( 'm', 'e', 't', 'a' )

/* ---- include/gpac/isomedia.h:510 -- opaque file handle. print_udta never
 * dereferences `file`, only threads it through the (stubbed) accessor calls below, so
 * an incomplete type is faithful -- the real struct's ~40-field layout is irrelevant. */
typedef struct __tag_isom GF_ISOFile;

/* =====================================================================================
 * gf_utf8_is_legal + its private helper tables/functions, copied VERBATIM from
 * src/utils/utf.c (Unicode, Inc. reference implementation) -- this is literally the
 * predicate the fix wraps in `udta_size &&`, so it is on the crash path, not incidental.
 * ===================================================================================== */
typedef u32 UTF32;
typedef u8 UTF8;
typedef u8 Boolean;

#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF

typedef enum {
	conversionOK, 		/* conversion successful */
	sourceExhausted,	/* partial character in source, but hit end */
	targetExhausted,	/* insuff. room in target for conversion */
	sourceIllegal		/* source sequence is illegal/malformed */
} ConversionResult;

#define UNI_SUR_HIGH_START  (UTF32)0xD800
#define UNI_SUR_HIGH_END    (UTF32)0xDBFF
#define UNI_SUR_LOW_START   (UTF32)0xDC00
#define UNI_SUR_LOW_END     (UTF32)0xDFFF

static const char trailingBytesForUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
                                          0x03C82080UL, 0xFA082080UL, 0x82082080UL
                                        };

Boolean isLegalUTF8(const UTF8 *source, int length) {
	UTF8 a;
	const UTF8 *srcptr = source+length;
	switch (length) {
	default:
		return 0;
	/* Everything else falls through when "true"... */
	case 4:
		if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return 0;
	case 3:
		if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return 0;
	case 2:
		if ((a = (*--srcptr)) > 0xBF) return 0;

		switch (*source) {
		/* no fall-through in this inner switch */
		case 0xE0:
			if (a < 0xA0) return 0;
			break;
		case 0xED:
			if (a > 0x9F) return 0;
			break;
		case 0xF0:
			if (a < 0x90) return 0;
			break;
		case 0xF4:
			if (a > 0x8F) return 0;
			break;
		default:
			if (a < 0x80) return 0;
		}

	case 1:
		if (*source >= 0x80 && *source < 0xC2) return 0;
	}
	if (*source > 0xF4) return 0;
	return 1;
}

Bool gf_utf8_is_legal(const u8 *data, u32 length)
{
	//we simply run ConvertUTF8toUTF16 without target
	const UTF8** sourceStart = (const UTF8**) &data;
	const UTF8* sourceEnd = (const UTF8*) ( data + length );
	ConversionResult result = conversionOK;
	const UTF8* source = *sourceStart;

	while (source < sourceEnd) {
		UTF32 ch = 0;
		unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
		if (source + extraBytesToRead >= sourceEnd) {
			result = sourceExhausted;
			break;
		}
		/* Do this check whether lenient or strict */
		if (! isLegalUTF8(source, extraBytesToRead+1)) {
			result = sourceIllegal;
			break;
		}
		/*
		 * The cases all fall through. See "Note A" below.
		 */
		switch (extraBytesToRead) {
		case 5:
			ch += *source++;
			ch <<= 6; /* remember, illegal UTF-8 */
		case 4:
			ch += *source++;
			ch <<= 6; /* remember, illegal UTF-8 */
		case 3:
			ch += *source++;
			ch <<= 6;
		case 2:
			ch += *source++;
			ch <<= 6;
		case 1:
			ch += *source++;
			ch <<= 6;
		case 0:
			ch += *source++;
		}
		ch -= offsetsFromUTF8[extraBytesToRead];

		if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
			/* UTF-16 surrogate values are illegal in UTF-32 */
			if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
				result = sourceIllegal;
				break;
			}
		} else if (ch > UNI_MAX_UTF16) {
			result = sourceIllegal;
			break; /* Bail out; shouldn't continue */
		}
	}
	return (result==conversionOK) ? GF_TRUE : GF_FALSE;
}

/* =====================================================================================
 * Stubbed ISOM box-accessor layer -- incidental to the bug (they only supply loop
 * bounds / the udta payload); the real implementations walk a parsed box tree this
 * harness does not construct. One udta entry, one item, content == the raw input file.
 * ===================================================================================== */
static u8 *g_udta_bytes = NULL;
static u32 g_udta_size = 0;

u32 gf_isom_get_udta_count(GF_ISOFile *isom_file, u32 trackNumber)
{
	(void)isom_file; (void)trackNumber;
	return 1; /* exactly one udta entry in this crafted file */
}

GF_Err gf_isom_get_udta_type(GF_ISOFile *isom_file, u32 trackNumber, u32 udta_idx, u32 *UserDataType, bin128 *UUID)
{
	(void)isom_file; (void)trackNumber; (void)udta_idx;
	if (UserDataType) *UserDataType = GF_4CC('t','e','s','t'); /* cosmetic only */
	if (UUID) memset(*UUID, 0, sizeof(bin128));
	return GF_OK;
}

u32 gf_isom_get_user_data_count(GF_ISOFile *isom_file, u32 trackNumber, u32 UserDataType, bin128 UUID)
{
	(void)isom_file; (void)trackNumber; (void)UserDataType; (void)UUID;
	return 1; /* exactly one item under that type */
}

GF_Err gf_isom_get_user_data(GF_ISOFile *isom_file, u32 trackNumber, u32 UserDataType, bin128 UUID,
                              u32 UserDataIndex, u8 **userData, u32 *userDataSize)
{
	(void)isom_file; (void)trackNumber; (void)UserDataType; (void)UUID; (void)UserDataIndex;
	/* Real gf_isom_get_user_data heap-allocates a FRESH copy of the box's raw data
	 * field and hands ownership to the caller (freed via gf_free below), with no
	 * NUL appended -- exactly reproduced here: the "box data" IS the attacker file.
	 * A true malloc(0) for a zero-length item (NOT a defensive malloc(1)) so that
	 * offset 0 itself is redzone -- the crash must come from ASAN's allocation-boundary
	 * tracking, never from an incidental uninitialized-fill byte. */
	u8 *out = (u8 *) malloc(g_udta_size);
	if (g_udta_size && out) memcpy(out, g_udta_bytes, g_udta_size);
	if (userData) *userData = out;
	if (userDataSize) *userDataSize = g_udta_size;
	return GF_OK;
}

const char *gf_4cc_to_str(u32 type)
{
	static char buf[5];
	buf[0] = (char)((type >> 24) & 0xFF);
	buf[1] = (char)((type >> 16) & 0xFF);
	buf[2] = (char)((type >> 8) & 0xFF);
	buf[3] = (char)(type & 0xFF);
	buf[4] = 0;
	return buf;
}

void gf_free(void *ptr) { free(ptr); }

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the overflow keeps its own stack frame (dc_batch requires the target
 * function name in the ASAN backtrace). */
__attribute__((noinline))
void print_udta(GF_ISOFile *file, u32 track_number, Bool has_itags)
{
	u32 i, count;

	count =  gf_isom_get_udta_count(file, track_number);
	if (!count) return;

	if (has_itags) {
		for (i=0; i<count; i++) {
			u32 type;
			bin128 uuid;
			gf_isom_get_udta_type(file, track_number, i+1, &type, &uuid);
			if (type == GF_ISOM_BOX_TYPE_META) {
				count--;
				break;
			}
		}
		if (!count) return;
	}

	fprintf(stderr, "%d UDTA types: ", count);

	for (i=0; i<count; i++) {
		u32 j, type, nb_items, first=GF_TRUE;
		bin128 uuid;
		gf_isom_get_udta_type(file, track_number, i+1, &type, &uuid);
		nb_items = gf_isom_get_user_data_count(file, track_number, type, uuid);
		fprintf(stderr, "%s (%d) ", gf_4cc_to_str(type), nb_items);
		for (j=0; j<nb_items; j++) {
			u8 *udta=NULL;
			u32 udta_size;
			gf_isom_get_user_data(file, track_number, type, uuid, j+1, &udta, &udta_size);
			if (!udta) continue;
			if (gf_utf8_is_legal(udta, udta_size)) {
				if (first) {
					fprintf(stderr, "\n");
					first = GF_FALSE;
				}
				fprintf(stderr, "\t%s\n", (char *) udta);
			}
			gf_free(udta);
		}
	}
	fprintf(stderr, "\n");
}


/* ================= driver ================= */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 2; }
	fseek(fp, 0, SEEK_END);
	long ln = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (ln < 0) ln = 0;
	/* cap: plenty for this corpus, avoids a pathological huge-file allocation */
	if (ln > (1 << 16)) ln = (1 << 16);
	size_t n = (size_t)ln;

	u8 *filebuf = NULL;
	if (n > 0) {
		filebuf = (u8 *) malloc(n);       /* HEAP input, ASAN-guarded */
		if (!filebuf) { fclose(fp); return 2; }
		size_t got = fread(filebuf, 1, n, fp);
		n = got;
	}
	fclose(fp);

	/* the entire input file *is* the crafted udta box's raw content: a real 'udta'
	 * child box's data field is fully attacker-controlled in both length and bytes. */
	g_udta_bytes = filebuf;
	g_udta_size = (u32)n;

	static u8 dummy_handle;
	print_udta((GF_ISOFile *) &dummy_handle, 1, GF_FALSE);

	free(filebuf);
	return 0;
}

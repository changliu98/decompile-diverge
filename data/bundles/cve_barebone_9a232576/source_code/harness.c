/* cve_barebone harness for CVE-2021-43814 (rizin) -- parse_die() heap-buffer-overflow WRITE.
 *
 * Isolation of librz/bin/dwarf.c:parse_die. In the vulnerable code init_die() allocates
 * die->attr_values with abbrev->count slots (calloc(sizeof(RzBinDwarfAttrValue), count)),
 * while parse_die() loops `for (i = 0; i < abbrev->count - 1; i++)`. When abbrev->count == 0
 * the size_t subtraction underflows to SIZE_MAX, the loop runs unbounded, and the very first
 * iteration's memset(&die->attr_values[0], 0, sizeof(...)) writes into a zero-length
 * allocation -> AddressSanitizer heap-buffer-overflow WRITE in __asan_memset (CWE-787).
 * Baseline dedup: __asan_memset--parse_die--parse_comp_unit.
 *
 * Everything below the target function is the REAL rizin vocabulary (types/enums/#defines
 * copied verbatim from librz/include/rz_bin_dwarf.h and rz_types_base.h). parse_attr_value
 * and ht_up_insert are downstream of / off the crash path, so they are minimal faithful
 * stubs (their real bodies pull in the whole DWARF/RzBuf machinery and never affect the bug).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* --- REAL basic types (librz/include/rz_types_base.h) --- */
typedef uint8_t ut8;
typedef uint16_t ut16;
typedef uint32_t ut32;
typedef uint64_t ut64;
typedef int64_t st64;
#define UT64_MAX 0xFFFFFFFFFFFFFFFFULL

/* --- REAL DWARF constants (librz/include/rz_bin_dwarf.h) --- */
#define DW_AT_stmt_list 0x10
#define DW_AT_comp_dir 0x1b
#define DW_FORM_string 0x08
#define DW_FORM_strp 0x0e

/* HtUP is opaque here; only referenced behind the stubbed ht_up_insert(). */
typedef struct ht_up_t HtUP;

/* --- REAL RzBinDwarfAttrKind (rz_bin_dwarf.h) --- */
typedef enum {
	DW_AT_KIND_ADDRESS,
	DW_AT_KIND_BLOCK,
	DW_AT_KIND_CONSTANT,
	DW_AT_KIND_EXPRLOC,
	DW_AT_KIND_FLAG,
	DW_AT_KIND_LINEPTR,
	DW_AT_KIND_LOCLISTPTR,
	DW_AT_KIND_MACPTR,
	DW_AT_KIND_RANGELISTPTR,
	DW_AT_KIND_REFERENCE,
	DW_AT_KIND_STRING,
} RzBinDwarfAttrKind;

/* --- REAL RzBinDwarfBlock (rz_bin_dwarf.h) --- */
typedef struct {
	ut64 length;
	ut8 *data;
} RzBinDwarfBlock;

/* --- REAL RzBinDwarfAttrValue (rz_bin_dwarf.h) --- */
typedef struct dwarf_attr_kind {
	ut64 attr_name;
	ut64 attr_form;
	RzBinDwarfAttrKind kind;
	union {
		ut64 address;
		RzBinDwarfBlock block;
		ut64 uconstant;
		st64 sconstant;
		ut8 flag;
		ut64 reference;
		struct {
			const char *content;
			ut64 offset;
		} string;
	};
} RzBinDwarfAttrValue;

/* --- REAL RzBinDwarfCompUnitHdr (rz_bin_dwarf.h) --- */
typedef struct {
	ut64 length;
	ut16 version;
	ut64 abbrev_offset;
	ut8 address_size;
	ut8 unit_type;
	ut8 dwo_id;
	ut64 type_sig;
	ut64 type_offset;
	ut64 header_size;
	ut64 unit_offset;
	bool is_64bit;
} RzBinDwarfCompUnitHdr;

/* --- REAL RzBinDwarfDie (rz_bin_dwarf.h) --- */
typedef struct {
	ut64 tag;
	ut64 abbrev_code;
	size_t count;
	size_t capacity;
	ut64 offset;
	bool has_children;
	RzBinDwarfAttrValue *attr_values;
} RzBinDwarfDie;

/* --- REAL RzBinDwarfAttrDef (rz_bin_dwarf.h) --- */
typedef struct {
	ut64 attr_name;
	ut64 attr_form;
	st64 special;
} RzBinDwarfAttrDef;

/* --- REAL RzBinDwarfAbbrevDecl (rz_bin_dwarf.h) --- */
typedef struct {
	ut64 code;
	ut64 tag;
	ut64 offset;
	ut8 has_children;
	size_t count;
	size_t capacity;
	RzBinDwarfAttrDef *defs;
} RzBinDwarfAbbrevDecl;

/* --- REAL RzBinDwarfDebugInfo (rz_bin_dwarf.h) --- */
typedef struct {
	size_t count;
	size_t capacity;
	void *comp_units;
	HtUP *lookup_table;
	HtUP *line_info_offset_comp_dir;
} RzBinDwarfDebugInfo;

/* --- incidental callee stub: ht_up_insert (only reached after the loop, never on the
 *     crash path; a real hashtable is irrelevant to the overflow). --- */
static bool ht_up_insert(HtUP *ht, ut64 key, void *value) {
	(void)ht;
	(void)key;
	(void)value;
	return true;
}

/* --- incidental callee stub: parse_attr_value. The overflow is upstream of this call
 *     (memset at loop-entry), so on triggering inputs this is never executed. On safe
 *     inputs it fills the (in-bounds) attr value, mirroring the real prologue, and stays
 *     within [obuf, buf_end) without dereferencing the buffer out of bounds. --- */
static const ut8 *parse_attr_value(const ut8 *obuf, int obuf_len,
	RzBinDwarfAttrDef *def, RzBinDwarfAttrValue *value,
	const RzBinDwarfCompUnitHdr *hdr,
	const ut8 *debug_str, size_t debug_str_len,
	bool big_endian) {
	(void)hdr;
	(void)debug_str;
	(void)debug_str_len;
	(void)big_endian;
	if (!def || !value || obuf_len < 1) {
		return obuf;
	}
	value->attr_form = def->attr_form;
	value->attr_name = def->attr_name;
	value->block.data = NULL;
	value->string.content = NULL;
	value->string.offset = 0;
	value->kind = DW_AT_KIND_CONSTANT;
	value->uconstant = 0;
	return (obuf_len > 1) ? obuf + 1 : obuf;
}

/* ==== TARGET FUNCTION: parse_die -- VERBATIM from target/original_function.c ==== */
static const ut8 *parse_die(const ut8 *buf, const ut8 *buf_end, RzBinDwarfDebugInfo *info, RzBinDwarfAbbrevDecl *abbrev,
	RzBinDwarfCompUnitHdr *hdr, RzBinDwarfDie *die, const ut8 *debug_str, size_t debug_str_len, bool big_endian) {
	size_t i;
	const char *comp_dir = NULL;
	ut64 line_info_offset = UT64_MAX;
	for (i = 0; i < abbrev->count - 1; i++) {
		memset(&die->attr_values[i], 0, sizeof(die->attr_values[i]));

		buf = parse_attr_value(buf, buf_end - buf, &abbrev->defs[i],
			&die->attr_values[i], hdr, debug_str, debug_str_len, big_endian);

		RzBinDwarfAttrValue *attribute = &die->attr_values[i];

		if (attribute->attr_name == DW_AT_comp_dir && (attribute->attr_form == DW_FORM_strp || attribute->attr_form == DW_FORM_string) && attribute->string.content) {
			comp_dir = attribute->string.content;
		}
		if (attribute->attr_name == DW_AT_stmt_list) {
			if (attribute->kind == DW_AT_KIND_CONSTANT) {
				line_info_offset = attribute->uconstant;
			} else if (attribute->kind == DW_AT_KIND_REFERENCE) {
				line_info_offset = attribute->reference;
			}
		}
		die->count++;
	}

	// If this is a compilation unit dir attribute, we want to cache it so the line info parsing
	// which will need this info can quickly look it up.
	if (comp_dir && line_info_offset != UT64_MAX) {
		char *name = strdup(comp_dir);
		if (name) {
			if (!ht_up_insert(info->line_info_offset_comp_dir, line_info_offset, name)) {
				free(name);
			}
		}
	}

	return buf;
}
/* ==== END TARGET FUNCTION ==== */

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (sz < 0) {
		sz = 0;
	}
	/* HEAP allocation so ASAN guards the input region. */
	ut8 *data = (ut8 *)malloc((size_t)sz ? (size_t)sz : 1);
	size_t n = 0;
	if (sz > 0) {
		n = fread(data, 1, (size_t)sz, f);
	}
	fclose(f);

	/* FDP-style: first byte selects abbrev->count. count == 0 -> the underflow trigger. */
	size_t count = (n >= 1) ? (size_t)data[0] : 0;

	/* --- REAL abbrev decl --- */
	RzBinDwarfAbbrevDecl *abbrev = (RzBinDwarfAbbrevDecl *)calloc(1, sizeof(*abbrev));
	abbrev->code = 1;
	abbrev->tag = (n >= 2) ? (ut64)data[1] : 0x11; /* DW_TAG_compile_unit */
	abbrev->has_children = 0;
	abbrev->count = count;
	/* Attribute defs pool: cover the loop's max index (count-1). On the trigger path the
	 * memset crashes at i==0 before any def is read, so 1 slot is enough there. */
	size_t defcap = count ? count : 1;
	abbrev->capacity = defcap;
	abbrev->defs = (RzBinDwarfAttrDef *)calloc(defcap, sizeof(RzBinDwarfAttrDef));
	for (size_t k = 0; k < defcap; k++) {
		abbrev->defs[k].attr_name = 0x03; /* DW_AT_name -- benign, not comp_dir/stmt_list */
		abbrev->defs[k].attr_form = DW_FORM_string;
		abbrev->defs[k].special = 0;
	}

	/* --- init_die() faithful: attr_values sized by abbrev->count (calloc(sizeof, count)) --- */
	RzBinDwarfDie *die = (RzBinDwarfDie *)calloc(1, sizeof(*die));
	die->attr_values = (RzBinDwarfAttrValue *)calloc(sizeof(RzBinDwarfAttrValue), count);
	die->capacity = count;
	die->count = 0;
	die->abbrev_code = 1;

	/* --- comp unit header --- */
	RzBinDwarfCompUnitHdr *hdr = (RzBinDwarfCompUnitHdr *)calloc(1, sizeof(*hdr));
	hdr->address_size = 8;
	hdr->version = 4;

	/* --- debug info (only touched inside the not-taken comp_dir/stmt_list branch) --- */
	RzBinDwarfDebugInfo *info = (RzBinDwarfDebugInfo *)calloc(1, sizeof(*info));

	/* --- DIE byte region driven by the remaining input --- */
	const ut8 *buf = data;
	const ut8 *buf_end = data + n;
	const ut8 *debug_str = data;
	size_t debug_str_len = n;

	const ut8 *ret = parse_die(buf, buf_end, info, abbrev, hdr, die, debug_str, debug_str_len, false);

	printf("ok count=%zu die_count=%zu ret=%p\n", count, die->count, (const void *)ret);
	free(data);
	return 0;
}

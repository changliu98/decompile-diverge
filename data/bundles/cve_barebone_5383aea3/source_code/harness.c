/* cve_barebone direct-call harness for cve_5383aea3 (radareorg/radare2, CVE-2022-0518)
 * Target: r_bin_java_inner_classes_attr_new  (shlr/java/class.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * fix_commit 9650e3c352f675687bf6c6f65ff2c4a3d0e288fa inserted a bounds check right
 * after `offset += 6;`, BEFORE the function reads the InnerClasses attribute's own
 * `number_of_classes` field:
 *
 *     offset += 6;
 *   + if (buf_offset + offset + 8 > sz) {
 *   +     eprintf ("Invalid amount of inner classes\n");
 *   +     return NULL;
 *   + }
 *     if (attr == NULL) {
 *         return attr;
 *     }
 *     ...
 *     attr->info.inner_classes_attr.number_of_classes = R_BIN_JAVA_USHORT (buffer, offset);
 *
 * Pre-fix, that R_BIN_JAVA_USHORT(buffer, offset) (offset==6 at this point) reads
 * buffer[6] and buffer[7] completely unconditionally -- there is no earlier check that
 * `sz` (the caller-supplied buffer length) actually covers those two bytes. Any caller
 * that hands this function a heap buffer 6 or 7 bytes long makes that macro read 1-2
 * bytes past the end of the allocation: a clean heap-buffer-overflow READ inside
 * r_bin_java_inner_classes_attr_new's OWN body (the macro expands inline; there is no
 * callee frame at the faulting access).
 *
 * The *only* other reads r_bin_java_inner_classes_attr_new performs before that line
 * are inside its first callee r_bin_java_default_attr_new(), which reads buffer[0..5]
 * (name_idx = USHORT(buffer,0), length = UINT(buffer,2)) -- so as long as sz is at
 * least 6, that callee is itself safe and returns a valid (non-NULL) attr, and control
 * reaches the vulnerable line in the target's own body without any earlier fault.
 * Hence: sz==6 or sz==7 isolates the bug precisely (default_attr_new's reads land
 * exactly in-bounds; the target's own number_of_classes read does not); sz>=8 makes
 * that same read safe (matching the post-fix guard, which additionally requires
 * sz>=14 -- more conservative than the 8 bytes this specific macro needs, but any
 * sz>=8 buffer here never has number_of_classes read out of bounds).
 *
 * Once number_of_classes is (safely) read, the function's own for-loop already
 * guards every subsequent 8-byte class-entry read with `if (offset + 8 > sz) break;`
 * -- correct as written for buf_offset==0 (the value this harness always passes), so
 * sz>=8 inputs run the rest of the function cleanly.
 *
 * Isolation: r_bin_java_inner_classes_attr_new and its one real gating callee
 * r_bin_java_default_attr_new (whose non-NULL return is a precondition for reaching
 * the bug) are pasted byte-for-byte from the real source (default_attr_new verbatim
 * from class.c; r_bin_java_inner_classes_attr_new verbatim from
 * target/original_function.c). Their own supporting real callees
 * (r_bin_java_is_old_format, r_bin_java_get_utf8_from_bin_cp_list, r_str_new/r_str_dup)
 * are ALSO copied verbatim -- they are trivial and none of their return values gate
 * whether the crash triggers. The genuinely incidental leaves they (or the target's
 * own dead-until-sz>=16 for-loop) reach into -- constant-pool tree walking
 * (r_bin_java_get_utf8_from_cp_item_list), the attr-type metadata table lookup
 * (r_bin_java_get_attr_type_by_name), the inner-class constant-pool name resolution
 * (r_bin_java_get_item_from_bin_cp_list / r_bin_java_get_item_name_from_bin_cp_list),
 * the access-flags stringifier (retrieve_class_method_access_string), and radare2's
 * RList (r_list_newf/r_list_append) -- are minimal, real-named, real-signature
 * stand-ins that always return "not found"/empty, exactly the already-handled branch
 * real radare2 takes whenever this function runs against an RBinJavaObj whose
 * constant-pool list isn't populated (as it always safely is on this isolated path).
 * All real type/field names throughout; RBinJavaObj/RBinJavaAttrInfo are TRIMMED to
 * the fields these two functions actually touch (each carries dozens more unrelated
 * fields in the real header).
 *
 * TRIGGER: input file is exactly 6 or 7 bytes -> sz in {6,7} -> the number_of_classes
 *          read at buffer[offset..offset+1] (offset==6) runs 1-2 bytes past the
 *          6/7-byte heap allocation.
 * SAFE:    input file is >=8 bytes -> that same read stays in-bounds; the for-loop
 *          either performs 0 iterations (sz<16) or exactly 1 (sz>=16, always freed and
 *          broken out of because the constant-pool stand-ins never resolve a name --
 *          the same "Unable to find the name" branch real radare2 already handles) and
 *          the function returns a valid attr cleanly.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* libr/include/r_types_base.h (real macro names: upstream these ARE #defines, not
 * typedefs). */
#define ut64 uint64_t
#define ut32 uint32_t
#define ut16 uint16_t
#define ut8  uint8_t

/* libr/include/r_types.h */
#define R_API
#define R_NEW0(x) (x*)calloc(1, sizeof(x))
#define eprintf(...) fprintf (stderr, __VA_ARGS__)

/* shlr/java/class.h -- the two field-extraction macros the bug and its callee use
 * (real, verbatim). */
#define R_BIN_JAVA_USHORT(x,y) ((ut16)(((0xff&x[y+1])|((x[y]&0xff)<<8)) & 0xffff))
#define R_BIN_JAVA_UINT(x,y) ((ut32)(((x[y]&0xff)<<24)|((x[y+1]&0xff)<<16)|((x[y+2]&0xff)<<8)|(x[y+3]&0xff)))

/* shlr/java/class.c: #define IFDBG if (DO_THE_DBG) -- DO_THE_DBG defaults to 0 in the
 * real source; this statement sits on the target's own dead-until-sz>=16 for-loop
 * path either way. */
#define IFDBG if (0)

/* r_list.h (real names). RList/RListIter stay OPAQUE: the target's own for-loop only
 * ever stores a pointer into a list / appends to it (through the stand-ins below) --
 * it never walks or reads one, so no real internal list machinery is needed. */
typedef struct r_list_t { int dummy; } RList;
typedef struct r_list_iter_t RListIter;
typedef void (*RListFree)(void *ptr);

/* shlr/java/class.h r_bin_java_field_t / r_bin_java_cp_object_t / r_bin_java_attr_meta_t
 * -- OPAQUE (real tag names): none of the three is ever dereferenced on this path,
 * only carried around as a pointer (RBinJavaClassesAttribute.clint_field, the
 * constant-pool lookup stand-ins' RBinJavaCPTypeObj* result, and default_attr_new's
 * local RBinJavaAttrMetas* type_info, which only ever feeds a field nothing re-reads
 * before the crash). */
typedef struct r_bin_java_field_t RBinJavaField;
typedef struct r_bin_java_cp_object_t RBinJavaCPTypeObj;
typedef struct r_bin_java_attr_meta_t RBinJavaAttrMetas;

/* shlr/java/class.h r_bin_java_meta (real, full -- only 3 fields) */
typedef struct r_bin_java_meta {
	ut64  file_offset;
	void *type_info;
	ut32 ord;
} RBinJavaMetaInfo;

/* shlr/java/class.h r_bin_java_attr_inner_classes_t (real, full) */
typedef struct r_bin_java_attr_inner_classes_t {
	ut16 number_of_classes;
	RList *classes;
} RBinJavaInnerClassesAttribute;

/* shlr/java/class.h r_bin_java_attr_t (real names; TRIMMED to the fields
 * r_bin_java_inner_classes_attr_new/r_bin_java_default_attr_new actually touch -- the
 * real struct's `union info` carries ~18 more sibling attribute-type members and the
 * struct itself carries `bytes`/`pos`/`loadaddr`, none read or written on this path). */
typedef struct r_bin_java_attr_t {
	ut64 size;
	char *name;
	ut64 file_offset;
	RBinJavaMetaInfo *metas;
	int type;
	ut16 name_idx;
	ut32 length;
	bool is_attr_in_old_format;
	union {
		RBinJavaInnerClassesAttribute inner_classes_attr;
	} info;
} RBinJavaAttrInfo;

/* shlr/java/class.h R_BIN_JAVA_ATTR_TYPE (real, full enum) */
typedef enum {
	R_BIN_JAVA_ATTR_TYPE_ANNOTATION_DEFAULT_ATTR = 0,
	R_BIN_JAVA_ATTR_TYPE_BOOTSTRAP_METHODS_ATTR,
	R_BIN_JAVA_ATTR_TYPE_CODE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_CONST_VALUE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_DEPRECATED_ATTR,
	R_BIN_JAVA_ATTR_TYPE_ENCLOSING_METHOD_ATTR,
	R_BIN_JAVA_ATTR_TYPE_EXCEPTIONS_ATTR,
	R_BIN_JAVA_ATTR_TYPE_INNER_CLASSES_ATTR,
	R_BIN_JAVA_ATTR_TYPE_LINE_NUMBER_TABLE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_LOCAL_VARIABLE_TABLE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_LOCAL_VARIABLE_TYPE_TABLE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_RUNTIME_INVISIBLE_ANNOTATION_ATTR,
	R_BIN_JAVA_ATTR_TYPE_RUNTIME_INVISIBLE_PARAMETER_ANNOTATION_ATTR,
	R_BIN_JAVA_ATTR_TYPE_RUNTIME_VISIBLE_ANNOTATION_ATTR,
	R_BIN_JAVA_ATTR_TYPE_RUNTIME_VISIBLE_PARAMETER_ANNOTATION_ATTR,
	R_BIN_JAVA_ATTR_TYPE_SIGNATURE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_SOURCE_DEBUG_EXTENTSION_ATTR,
	R_BIN_JAVA_ATTR_TYPE_SOURCE_FILE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_STACK_MAP_TABLE_ATTR,
	R_BIN_JAVA_ATTR_TYPE_SYNTHETIC_ATTR,
	R_BIN_JAVA_ATTR_TYPE_UNKNOWN_ATTR,
	R_BIN_JAVA_ATTR_TYPE_FAILED_ATTR
} R_BIN_JAVA_ATTR_TYPE;

/* shlr/java/class.h r_bin_java_attr_classes_t (real, full) */
typedef struct r_bin_java_attr_classes_t {
	char *name;
	char *flags_str;
	ut64 file_offset;
	RBinJavaAttrInfo *clint_attr;
	RBinJavaField *clint_field;
	ut16 inner_class_info_idx;
	ut16 outer_class_info_idx;
	ut16 inner_name_idx;
	ut16 inner_class_access_flags;
	ut64 size;
} RBinJavaClassesAttribute;

/* shlr/java/class.h r_bin_java_classfile_t (real, full) + r_bin_java_obj_t (real
 * names; TRIMMED to the 2 fields is_old_format()/default_attr_new() touch: `cf` and
 * `attr_idx`, plus `cp_list` for get_utf8_from_bin_cp_list()'s NULL-list branch -- the
 * real RBinJavaObj carries ~40 more fields for the rest of the java parser's state). */
typedef struct r_bin_java_classfile_t {
	ut8 cafebabe[4];
	ut8 minor[2];
	ut8 major[2];
	ut16 cp_count;
} RBinJavaClass;

typedef struct r_bin_java_obj_t {
	struct r_bin_java_classfile_t cf;
	ut32 attr_idx;
	RList *cp_list;
} RBinJavaObj;

/* shlr/java/class.c:307 (real: file-static, NULL-initialized, exact name) */
static RBinJavaObj *R_BIN_JAVA_GLOBAL_BIN = NULL;

/* ---- incidental callees: minimal, real-named/real-signature stand-ins (see file
 * banner). Each is either unreached before the crash, or (for sz>=16 SAFE inputs)
 * reached only after the crash-relevant read has already passed safely, where it
 * always takes the real "not found" branch real radare2 already handles. */
static char *retrieve_class_method_access_string(ut16 flags) {
	(void)flags;
	return NULL;
}
static RBinJavaCPTypeObj *r_bin_java_get_item_from_bin_cp_list(RBinJavaObj *bin, ut64 idx) {
	(void)bin; (void)idx;
	return NULL;
}
static char *r_bin_java_get_item_name_from_bin_cp_list(RBinJavaObj *bin, RBinJavaCPTypeObj *obj) {
	(void)bin; (void)obj;
	return NULL;
}
static void r_bin_java_inner_classes_attr_entry_free(void *attr) {
	(void)attr;
}
static RList *r_list_newf(RListFree f) {
	(void)f;
	return (RList *)calloc(1, sizeof(RList));
}
static RListIter *r_list_append(RList *list, void *data) {
	(void)list; (void)data;
	return NULL;
}
/* shlr/java/class.c r_bin_java_get_utf8_from_cp_item_list's own constant-pool tree
 * walk (real fn is ~80 lines over RListIter/r_list_get_n) -- stubbed to the SAME
 * "not found" result the real function returns whenever cp_list is NULL, which it
 * always is here: R_BIN_JAVA_GLOBAL_BIN->cp_list is never populated on this path. */
static char *r_bin_java_get_utf8_from_cp_item_list(RList *cp_list, ut64 idx) {
	(void)cp_list; (void)idx;
	return NULL;
}
/* shlr/java/class.c r_bin_java_get_attr_type_by_name's real ~40-entry
 * RBIN_JAVA_ATTRS_METAS dispatch table is irrelevant here: its result only ever feeds
 * attr->metas->type_info, which nothing reads before the crash. */
static RBinJavaAttrMetas *r_bin_java_get_attr_type_by_name(const char *name) {
	(void)name;
	return NULL;
}

/* libr/util/str.c (real, verbatim -- both actually execute on the crash path:
 * default_attr_new's own text calls r_str_dup(NULL,"NULL") once its constant-pool
 * lookup above returns NULL). */
static char *r_str_new(const char *str) {
	return str ? strdup(str) : NULL;
}
static char *r_str_dup(char *ptr, const char *string) {
	char *str = r_str_new(string);
	free (ptr); // in case ptr == string
	return str;
}

/* shlr/java/class.c:513 (real, verbatim) */
R_API bool r_bin_java_is_old_format(RBinJavaObj *bin) {
	return bin->cf.major[1] == 45 && bin->cf.minor[1] <= 2;
}

/* shlr/java/class.c:1673 (real, verbatim) */
R_API char *r_bin_java_get_utf8_from_bin_cp_list(RBinJavaObj *bin, ut64 idx) {
	if (bin == NULL) {
		return NULL;
	}
	return r_bin_java_get_utf8_from_cp_item_list (bin->cp_list, idx);
}

/* shlr/java/class.c:1981 (real, verbatim) -- r_bin_java_inner_classes_attr_new's own
 * first line calls this; its non-NULL return is the precondition for reaching the bug
 * (a NULL here makes the target `return attr;` before ever touching the vulnerable
 * line). */
R_API RBinJavaAttrInfo *r_bin_java_default_attr_new(RBinJavaObj *bin, ut8 *buffer, ut64 sz, ut64 buf_offset) {
	RBinJavaAttrInfo *attr = R_NEW0 (RBinJavaAttrInfo);
	if (!attr) {
		return NULL;
	}
	RBinJavaAttrMetas *type_info = NULL;
	attr->metas = R_NEW0 (RBinJavaMetaInfo);
	if (attr->metas == NULL) {
		free (attr);
		return NULL;
	}
	attr->is_attr_in_old_format = r_bin_java_is_old_format(bin);
	attr->file_offset = buf_offset;
	attr->name_idx = R_BIN_JAVA_USHORT (buffer, 0);
	attr->length = R_BIN_JAVA_UINT (buffer, 2);
	attr->size = R_BIN_JAVA_UINT (buffer, 2) + 6;
	attr->name = r_bin_java_get_utf8_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, attr->name_idx);
	if (attr->name == NULL) {
		// Something bad has happened
		attr->name = r_str_dup (NULL, "NULL");
		eprintf ("r_bin_java_default_attr_new: Unable to find the name for %d index.\n", attr->name_idx);
	}
	type_info = r_bin_java_get_attr_type_by_name (attr->name);
	attr->metas->ord = (R_BIN_JAVA_GLOBAL_BIN->attr_idx++);
	attr->metas->type_info = (void *) type_info;
	// IFDBG eprintf ("	Addrs for type_info [tag=%d]: 0x%08"PFMT64x"\n", type_val, &attr->metas->type_info);
	return attr;
}

/* ==== shlr/java/class.c:3728 -- VERBATIM from data_cve/cve_5383aea3/target/original_function.c ==== */
R_API RBinJavaAttrInfo *r_bin_java_inner_classes_attr_new(RBinJavaObj *bin, ut8 *buffer, ut64 sz, ut64 buf_offset) {
	RBinJavaClassesAttribute *icattr;
	RBinJavaAttrInfo *attr = NULL;
	RBinJavaCPTypeObj *obj;
	ut32 i = 0;
	ut64 offset = 0, curpos;
	attr = r_bin_java_default_attr_new (bin, buffer, sz, buf_offset);
	offset += 6;
	if (attr == NULL) {
		// TODO eprintf
		return attr;
	}
	attr->type = R_BIN_JAVA_ATTR_TYPE_INNER_CLASSES_ATTR;
	attr->info.inner_classes_attr.number_of_classes = R_BIN_JAVA_USHORT (buffer, offset);
	offset += 2;
	attr->info.inner_classes_attr.classes = r_list_newf (r_bin_java_inner_classes_attr_entry_free);
	for (i = 0; i < attr->info.inner_classes_attr.number_of_classes; i++) {
		curpos = buf_offset + offset;
		if (offset + 8 > sz) {
			eprintf ("Invalid amount of inner classes\n");
			break;
		}
		icattr = R_NEW0 (RBinJavaClassesAttribute);
		if (!icattr) {
			break;
		}
		icattr->inner_class_info_idx = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;
		icattr->outer_class_info_idx = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;
		icattr->inner_name_idx = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;
		icattr->inner_class_access_flags = R_BIN_JAVA_USHORT (buffer, offset);
		offset += 2;
		icattr->flags_str = retrieve_class_method_access_string (icattr->inner_class_access_flags);
		icattr->file_offset = curpos;
		icattr->size = 8;

		obj = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, icattr->inner_name_idx);
		if (obj == NULL) {
			eprintf ("BINCPLIS IS HULL %d\n", icattr->inner_name_idx);
		}
		icattr->name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, obj);
		if (!icattr->name) {
			obj = r_bin_java_get_item_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, icattr->inner_class_info_idx);
			if (!obj) {
				eprintf ("BINCPLIST IS NULL %d\n", icattr->inner_class_info_idx);
			}
			icattr->name = r_bin_java_get_item_name_from_bin_cp_list (R_BIN_JAVA_GLOBAL_BIN, obj);
			if (!icattr->name) {
				icattr->name = r_str_dup (NULL, "NULL");
				eprintf ("r_bin_java_inner_classes_attr: Unable to find the name for %d index.\n", icattr->inner_name_idx);
				free (icattr);
				break;
			}
		}

		IFDBG eprintf("r_bin_java_inner_classes_attr: Inner class name %d is %s.\n", icattr->inner_name_idx, icattr->name);
		r_list_append (attr->info.inner_classes_attr.classes, (void *) icattr);
	}
	attr->size = offset;
	// IFDBG r_bin_java_print_inner_classes_attr_summary(attr);
	return attr;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 0;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		return 0;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
	long fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

	/* HEAP-allocate exactly `fsz` bytes (ASAN-guarded): the input file's own byte
	 * length IS `sz`, the parameter whose insufficiency (relative to the unconditional
	 * offset-6 read below) is the entire bug. */
	ut8 *buffer = (ut8 *)malloc(fsz > 0 ? (size_t)fsz : 1);
	if (!buffer) { fclose(f); return 0; }
	size_t n = fsz > 0 ? fread(buffer, 1, (size_t)fsz, f) : 0;
	fclose(f);

	RBinJavaObj fake_bin;
	memset(&fake_bin, 0, sizeof(fake_bin));
	R_BIN_JAVA_GLOBAL_BIN = &fake_bin;

	RBinJavaAttrInfo *attr = r_bin_java_inner_classes_attr_new(&fake_bin, buffer, (ut64)n, 0);
	(void)attr;

	free(buffer);
	return 0;
}

/* cve_barebone harness -- gpac CVE-2022-1035 / gf_dump_vrml_simple_field NULL-deref (CWE-476)
 *
 * Isolated reproduction: gf_dump_vrml_simple_field() is called directly with a GF_FieldInfo
 * of type GF_SG_VRML_SFNODE whose far_ptr is NULL. The pre-fix body dereferences
 * *(GF_Node **)field.far_ptr unconditionally (assert's own condition expression, then again
 * as the gf_dump_vrml_node() call argument) -- no NULL guard anywhere on this path.
 *
 * TRIGGER: field.fieldType = GF_SG_VRML_SFNODE, field.far_ptr = NULL -> SIGSEGV reading
 *          address 0, caught by ASAN as "SEGV on unknown address 0x000000000000" with
 *          gf_dump_vrml_simple_field on the stack.
 * SAFE:    field.fieldType = GF_SG_VRML_SFNODE, field.far_ptr -> a heap slot holding a real
 *          (heap-allocated) GF_Node* -> the assert's dereference reads a valid pointer,
 *          gf_dump_vrml_node (a faithful no-op stub here -- its own body is unrelated to this
 *          CVE) is called, the function returns cleanly.
 *
 * Everything off this exact branch (MFNODE / generic-SF / generic-MF) is never reached by any
 * input this harness constructs; their helpers are minimal no-op stubs kept only so the
 * verbatim function body -- which references all of them -- compiles and links as one TU.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>

/* ---- gpac base typedefs (real names, include/gpac/setup.h) ---- */
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef int             s32;

typedef enum {
	GF_FALSE = 0,
	GF_TRUE
} Bool;

typedef s32 GF_Err;   /* real name; full error enum irrelevant -- only an unused stub's return type */

/* ---- include/gpac/scenegraph.h (real names, verbatim layout) ---- */
#define BASE_NODE	struct _nodepriv *sgprivate;

typedef struct _base_node
{
	BASE_NODE
} GF_Node;

typedef struct _child_node
{
	struct _child_node *next;
	GF_Node *node;
} GF_ChildNodeItem;

typedef struct _route GF_Route;   /* real name; opaque -- only used as a func-ptr param type below */

typedef struct
{
	u32 fieldIndex;
	u32 fieldType;
	void *far_ptr;
	const char *name;
	u32 NDTtype;
	u32 eventType;
	void (*on_event_in)(GF_Node *pNode, GF_Route *from_route);
} GF_FieldInfo;

/* ---- include/gpac/scenegraph_vrml.h (real names + real values, verbatim enum) ---- */
enum
{
	GF_SG_VRML_SFBOOL		=	0,
	GF_SG_VRML_SFFLOAT		=	1,
	GF_SG_VRML_SFTIME		=	2,
	GF_SG_VRML_SFINT32		=	3,
	GF_SG_VRML_SFSTRING		=	4,
	GF_SG_VRML_SFVEC3F		=	5,
	GF_SG_VRML_SFVEC2F		=	6,
	GF_SG_VRML_SFCOLOR		=	7,
	GF_SG_VRML_SFROTATION	=	8,
	GF_SG_VRML_SFIMAGE		=	9,
	GF_SG_VRML_SFNODE		=	10,
	GF_SG_VRML_SFVEC4F		=	11,

	GF_SG_VRML_SFURL,
	GF_SG_VRML_SFSCRIPT,
	GF_SG_VRML_SFCOMMANDBUFFER,
	GF_SG_VRML_SFDOUBLE,
	GF_SG_VRML_SFCOLORRGBA,
	GF_SG_VRML_SFVEC2D,
	GF_SG_VRML_SFVEC3D,

	GF_SG_VRML_FIRST_MF		= 32,
	GF_SG_VRML_MFBOOL		= GF_SG_VRML_FIRST_MF,
	GF_SG_VRML_MFFLOAT,
	GF_SG_VRML_MFTIME,
	GF_SG_VRML_MFINT32,
	GF_SG_VRML_MFSTRING,
	GF_SG_VRML_MFVEC3F,
	GF_SG_VRML_MFVEC2F,
	GF_SG_VRML_MFCOLOR,
	GF_SG_VRML_MFROTATION,
	GF_SG_VRML_MFIMAGE,
	GF_SG_VRML_MFNODE,
	GF_SG_VRML_MFVEC4F,

	GF_SG_VRML_SFATTRREF	=	45,
	GF_SG_VRML_MFATTRREF	=	46,

	GF_SG_VRML_MFURL,
	GF_SG_VRML_MFSCRIPT,
	GF_SG_VRML_MFCOMMANDBUFFER,

	GF_SG_VRML_MFDOUBLE,
	GF_SG_VRML_MFCOLORRGBA,
	GF_SG_VRML_MFVEC2D,
	GF_SG_VRML_MFVEC3D,

	GF_SG_VRML_SCRIPT_FUNCTION,

	GF_SG_VRML_GENERIC_FUNCTION,

	GF_SG_VRML_UNKNOWN
};

typedef struct {
	u32 count;
	u8 *array;
} GenMFField;

/* ---- include/gpac/scene_manager.h (real names) ---- */
typedef enum
{
	GF_SM_DUMP_BT = 0,
	GF_SM_DUMP_XMTA,
	GF_SM_DUMP_VRML,
	GF_SM_DUMP_X3D_VRML,
	GF_SM_DUMP_X3D_XML,
	GF_SM_DUMP_LASER,
	GF_SM_DUMP_SVG,
	GF_SM_DUMP_XML,
	GF_SM_DUMP_AUTO_TXT,
	GF_SM_DUMP_AUTO_XML,
	GF_SM_DUMP_NONE
} GF_SceneDumpFormat;

typedef struct _tag_array GF_List;              /* real name, gpac/list.h; opaque (never deref'd) */
typedef struct __tag_scene_graph GF_SceneGraph; /* real name, gpac/scenegraph.h; opaque */
typedef struct _proto GF_Proto;                 /* real name, gpac/scenegraph_vrml.h; opaque */

typedef struct _scenedump GF_SceneDumper;

/* ---- src/scene_manager/scene_dump.c : struct _scenedump (real name+layout, verbatim) ---- */
struct _scenedump
{
	GF_SceneGraph *sg;
	GF_Proto *current_proto;
	FILE *trace;
	u32 indent;
	char *filename;

	GF_SceneDumpFormat dump_mode;
	u16 CurrentESID;
	u8 ind_char;
	Bool XMLDump, X3DDump, LSRDump;

	GF_List *dump_nodes;

	Bool skip_scene_replace;
	GF_List *current_com_list;
	GF_List *inserted_routes;

	Bool in_text;
};

/* ---- crash-path/incidental callees: minimal faithful no-op stubs (see file header -- none
 * of these is ever actually invoked by an input this harness constructs). ---- */
static void gf_dump_vrml_node(GF_SceneDumper *sdump, GF_Node *node, Bool in_list, char *fieldContainer)
{
	(void)sdump; (void)node; (void)in_list; (void)fieldContainer;
}
Bool gf_sg_vrml_is_sf_field(u32 FieldType)
{
	return (FieldType < GF_SG_VRML_FIRST_MF) ? GF_TRUE : GF_FALSE;
}
u32 gf_sg_vrml_get_sf_type(u32 FieldType)
{
	return FieldType;
}
GF_Err gf_sg_vrml_mf_get_item(void *mf, u32 FieldType, void **new_ptr, u32 ItemPos)
{
	(void)mf; (void)FieldType; (void)ItemPos;
	if (new_ptr) *new_ptr = NULL;
	return 0;
}
int gf_fprintf(FILE *stream, const char *format, ...)
{
	(void)stream; (void)format;
	return 0;
}
static void StartAttribute(GF_SceneDumper *sdump, const char *name)
{
	(void)sdump; (void)name;
}
static void EndAttribute(GF_SceneDumper *sdump)
{
	(void)sdump;
}
static void gf_dump_vrml_sffield(GF_SceneDumper *sdump, u32 type, void *ptr, Bool is_mf, GF_Node *node)
{
	(void)sdump; (void)type; (void)ptr; (void)is_mf; (void)node;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline: pure codegen hint (kept OFF the function's own byte range) so the SIGSEGV keeps
 * its own stack frame -- dc_batch's classifier requires the target function's name in the
 * ASAN backtrace. */
__attribute__((noinline))
static void gf_dump_vrml_simple_field(GF_SceneDumper *sdump, GF_FieldInfo field, GF_Node *parent)
{
	u32 i, sf_type;
	GF_ChildNodeItem *list;
	void *slot_ptr;

	switch (field.fieldType) {
	case GF_SG_VRML_SFNODE:
		assert ( *(GF_Node **)field.far_ptr);
		gf_dump_vrml_node(sdump, *(GF_Node **)field.far_ptr, 0, NULL);
		return;
	case GF_SG_VRML_MFNODE:
		list = * ((GF_ChildNodeItem **) field.far_ptr);
		assert( list );
		sdump->indent++;
		while (list) {
			gf_dump_vrml_node(sdump, list->node, 1, NULL);
			list = list->next;
		}
		sdump->indent--;
		return;
	case GF_SG_VRML_SFCOMMANDBUFFER:
		return;
	}
	if (gf_sg_vrml_is_sf_field(field.fieldType)) {
		if (sdump->XMLDump) StartAttribute(sdump, "value");
		gf_dump_vrml_sffield(sdump, field.fieldType, field.far_ptr, 0, parent);
		if (sdump->XMLDump) EndAttribute(sdump);
	} else {
		GenMFField *mffield;
		mffield = (GenMFField *) field.far_ptr;
		sf_type = gf_sg_vrml_get_sf_type(field.fieldType);
		if (!sdump->XMLDump) {
			gf_fprintf(sdump->trace, "[");
		} else if (sf_type==GF_SG_VRML_SFSTRING) {
			gf_fprintf(sdump->trace, " value=\'");
		} else {
			StartAttribute(sdump, "value");
		}
		for (i=0; i<mffield->count; i++) {
			if (i) gf_fprintf(sdump->trace, " ");
			gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, &slot_ptr, i);
			/*this is to cope with single MFString which shall appear as SF in XMT*/
			gf_dump_vrml_sffield(sdump, sf_type, slot_ptr, 1, parent);
		}
		if (!sdump->XMLDump) {
			gf_fprintf(sdump->trace, "]");
		} else if (sf_type==GF_SG_VRML_SFSTRING) {
			gf_fprintf(sdump->trace, "\'");
		} else {
			EndAttribute(sdump);
		}
	}
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
	size_t n = (size_t)ln;
	unsigned char *data = (unsigned char *)malloc(n ? n : 1);   /* HEAP input, ASAN-guarded */
	size_t got = fread(data, 1, n, fp);
	fclose(fp);
	if (got < 1) { free(data); return 0; }                       /* empty -> clean exit */

	int trigger = data[0] & 1;                        /* odd -> far_ptr==NULL (the CVE) */
	u32 indent_seed = (got > 1) ? data[1] : 0;

	GF_SceneDumper *sdump = (GF_SceneDumper *)malloc(sizeof(GF_SceneDumper));
	memset(sdump, 0, sizeof(*sdump));
	sdump->indent = indent_seed;                      /* unused on this path -- diversity only */
	sdump->XMLDump = (data[0] & 2) ? GF_TRUE : GF_FALSE;

	GF_FieldInfo field;
	memset(&field, 0, sizeof(field));
	field.fieldType = GF_SG_VRML_SFNODE;

	if (trigger) {
		field.far_ptr = NULL;                          /* <-- the exact pre-fix-reachable state */
	} else {
		GF_Node *node = (GF_Node *)malloc(sizeof(GF_Node));      /* real, heap-allocated node */
		memset(node, 0, sizeof(*node));
		GF_Node **far = (GF_Node **)malloc(sizeof(GF_Node *));   /* heap far_ptr slot */
		*far = node;
		field.far_ptr = far;
	}

	GF_Node *parent = NULL;
	free(data);

	/* volatile function pointer: forbid the compiler from inlining/proving-away the call. */
	void (*volatile fn)(GF_SceneDumper *, GF_FieldInfo, GF_Node *) = gf_dump_vrml_simple_field;
	fn(sdump, field, parent);

	return 0;
}

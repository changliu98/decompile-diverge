/* cve_barebone direct-call harness for CVE-2017-6435 (libplist)
 * Target: parse_string_node  (src/bplist.c)
 * Bug class: memcpy-param-overlap (CWE-758, reliance on undefined behavior).
 *
 *   plist_t parse_string_node(const char **bnode, uint64_t size)
 *       data->strval = malloc(size + 1);      // attacker controls `size`
 *       memcpy(data->strval, *bnode, size);   // <-- crash site (src/bplist.c:286)
 *
 * A bplist ASCII-string node header carries an attacker-controlled 64-bit
 * `size`. When `size` is enormous (the reference PoC uses 0xfffffffffffffff0),
 * malloc(size + 1) fails and returns NULL (allocator_may_return_null), and the
 * following memcpy(NULL, *bnode, <enormous>) makes AddressSanitizer's memcpy
 * interceptor flag the destination/source ranges as overlapping -> the
 * memcpy-param-overlap error, an instance of relying on undefined behavior
 * (CWE-758). This is exactly the baseline dedup family
 *   __asan_memcpy -- parse_string_node -- parse_bin_node
 * (here the third frame is main() instead of parse_bin_node, since the function
 * is driven in isolation).
 *
 * The reference build runs libplist's plistutil under ASAN_OPTIONS that include
 * allocator_may_return_null=1; the dc_batch/dc_try runners do NOT set it, so the
 * faithful behavior (huge malloc -> NULL, then the overlapping memcpy) is
 * requested here via __asan_default_options() rather than being reproduced by
 * forcing the alternative "allocation-size-too-big" abort.
 *
 * Everything parse_string_node needs is copied VERBATIM from the vulnerable
 * source tree (data_cve/cve_7163c9da/source_code) with real names:
 *   include/plist/plist.h   plist_type enum, plist_t typedef
 *   src/plist.h             struct plist_data_s / plist_data_t
 *   libcnary/include        list_t / node_list_t / node_t structs, TRUE/FALSE
 *   src/plist.c:150         plist_new_plist_data()   (verbatim)
 *   libcnary/list.c:29      list_init()              (verbatim)
 *   libcnary/node_list.c:38 node_list_create()       (verbatim)
 *   libcnary/node.c:47      node_create()            (verbatim)
 * node_attach()/node_destroy() are referenced only by node_create()'s
 * parent!=NULL branch, which never executes here (parent is always NULL), so
 * faithful minimal stubs stand in for them.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* Request the reference ASAN allocator behavior (huge malloc -> NULL) so the
 * faithful memcpy-param-overlap path is taken; the dc runners' ASAN_OPTIONS do
 * not set allocator_may_return_null, and default options are only overridden by
 * options actually present in the env string. */
const char *__asan_default_options(void) { return "allocator_may_return_null=1"; }

/* ===== Real type/macro definitions (verbatim names from libplist headers) ===== */

/* include/plist/plist.h */
typedef void *plist_t;

typedef enum
{
    PLIST_BOOLEAN,	/**< Boolean, scalar type */
    PLIST_UINT,	/**< Unsigned integer, scalar type */
    PLIST_REAL,	/**< Real, scalar type */
    PLIST_STRING,	/**< ASCII string, scalar type */
    PLIST_ARRAY,	/**< Ordered array, structured type */
    PLIST_DICT,	/**< Unordered dictionary (key/value pair), structured type */
    PLIST_DATE,	/**< Date, scalar type */
    PLIST_DATA,	/**< Binary data, scalar type */
    PLIST_KEY,	/**< Key in dictionaries (ASCII String), scalar type */
    PLIST_UID,      /**< Special type used for 'keyed encoding' */
    PLIST_NONE	/**< No type */
} plist_type;

/* src/plist.h */
struct plist_data_s
{
    union
    {
        char boolval;
        uint64_t intval;
        double realval;
        char *strval;
        uint8_t *buff;
        void *hashtable;
    };
    uint64_t length;
    plist_type type;
};

typedef struct plist_data_s *plist_data_t;

/* libcnary/include/object.h */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* libcnary/include/list.h */
typedef struct list_t {
	void* next;
	void* prev;
} list_t;

/* libcnary/include/node_list.h */
struct node_t;
typedef struct node_list_t {
	// list_t members
	struct node_t* begin;
	struct node_t* end;

	// node_list_t members
	unsigned int count;

} node_list_t;

/* libcnary/include/node.h */
typedef struct node_t {
	// Super class
	struct node_t* next;
	struct node_t* prev;
	unsigned int count;

	// Local Properties
	int isRoot;
	int isLeaf;

	// Local Members
	void *data;
	unsigned int depth;
	struct node_t* parent;
	struct node_list_t* children;

	// Virtual Functions
	int(*attach)(struct node_t* parent, struct node_t* child);
	int(*detach)(struct node_t* parent, struct node_t* child);

} node_t;

/* ===== Callees on the exercised (safe) path ===== */

/* Referenced only by node_create()'s parent!=NULL branch, which never runs here
 * (parent is always NULL); faithful minimal stubs. */
void node_destroy(node_t* node) { (void)node; }
int node_attach(node_t* parent, node_t* child) { (void)parent; (void)child; return 0; }

/* libcnary/list.c:29 (verbatim) */
void list_init(list_t* list) {
	list->next = NULL;
	list->prev = list;
}

/* libcnary/node_list.c:38 (verbatim) */
node_list_t* node_list_create(node_t* node) {
	node_list_t* list = (node_list_t*) malloc(sizeof(node_list_t));
	if(list == NULL) {
		return NULL;
	}
	memset(list, '\0', sizeof(node_list_t));

	// Initialize structure
	list_init((list_t*) list);
	list->count = 0;
	return list;
}

/* libcnary/node.c:47 (verbatim) */
node_t* node_create(node_t* parent, void* data) {
	int error = 0;

	node_t* node = (node_t*) malloc(sizeof(node_t));
	if(node == NULL) {
		return NULL;
	}
	memset(node, '\0', sizeof(node_t));

	node->data = data;
	node->depth = 0;
	node->next = NULL;
	node->prev = NULL;
	node->count = 0;
	node->isLeaf = TRUE;
	node->isRoot = TRUE;
	node->parent = NULL;
	node->children = node_list_create(node);

	// Pass NULL to create a root node
	if(parent != NULL) {
		// This is a child node so attach it to it's parent
		error = node_attach(parent, node);
		if(error < 0) {
			// Unable to attach nodes
			printf("ERROR: %d \"Unable to attach nodes\"\n", error);
			node_destroy(node);
			return NULL;
		}
	}

	return node;
}

/* src/plist.c:150 (verbatim) */
plist_data_t plist_new_plist_data(void)
{
    plist_data_t data = (plist_data_t) calloc(sizeof(struct plist_data_s), 1);
    return data;
}

/* Keep the target as its own frame in the ASAN backtrace (matches the reference
 * dedup where parse_string_node is frame #1 under __asan_memcpy). Separate
 * declaration only -- does not touch the verbatim definition below. */
static plist_t parse_string_node(const char **bnode, uint64_t size) __attribute__((noinline));

/* ==== VERBATIM from data_cve/cve_7163c9da/target/original_function.c ==== */
static plist_t parse_string_node(const char **bnode, uint64_t size)
{
    plist_data_t data = plist_new_plist_data();

    data->type = PLIST_STRING;
    data->strval = (char *) malloc(sizeof(char) * (size + 1));
    memcpy(data->strval, *bnode, size);
    data->strval[size] = '\0';
    data->length = strlen(data->strval);

    return node_create(NULL, data);
}
/* ==== end verbatim ==== */

/* ===== FDP-style driver =====
 * Input layout: first 8 bytes = little-endian uint64_t `size` (the bplist string
 * node's attacker-controlled length), remaining bytes = the string payload that
 * *bnode points at. Both the size field and the payload live in one HEAP buffer
 * so the overflowing memcpy is fully ASAN-visible. */

/* Observable sink for parse_string_node's return value. Without this, at -O1 the
 * optimizer proves the (discarded) result -- and hence the internal malloc'd
 * buffer, its strlen read, and the memcpy that fills it -- dead, and elides the
 * crash site. Escaping the pointer to a volatile global keeps the memcpy live so
 * the reference crash reproduces at the runners' native -O1. */
static void *volatile g_sink;

int main(int argc, char **argv)
{
    if (argc < 2) return 0;
    FILE *f = fopen(argv[1], "rb");
    if (!f) return 0;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
    long fsz = ftell(f);
    if (fsz < 0) { fclose(f); return 0; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

    size_t n = (size_t) fsz;
    unsigned char *buf = (unsigned char *) malloc(n ? n : 1);
    if (!buf) { fclose(f); return 0; }
    size_t got = fread(buf, 1, n, f);
    fclose(f);

    if (got < 8) { free(buf); return 0; }  /* need 8 bytes for the size field */

    uint64_t size = 0;
    for (int i = 0; i < 8; i++)
        size |= (uint64_t) buf[i] << (8 * i);

    /* payload = the heap bytes after the size field; *bnode points here */
    const char *bnode = (const char *) (buf + 8);

    plist_t node = parse_string_node(&bnode, size);
    g_sink = node;  /* escape the result so the memcpy stays live at -O1 */

    free(buf);
    return 0;
}

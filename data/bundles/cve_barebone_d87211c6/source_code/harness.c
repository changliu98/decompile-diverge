/* cve_barebone harness -- cve_d87211c6 (nokogiri) / rb_xml_reader_attribute_hash
 * NULL Pointer Dereference (CWE-476). See the generator script header (scripts/
 * gen_dc_cve_d87211c6.py) for the full bug writeup and isolation-strategy rationale.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---------------------------------------------------------------------
 * Ruby C-API surface (real names from ruby.h) -- incidental object-model
 * scaffolding, minimal faithful stubs (no libruby link).
 * --------------------------------------------------------------------- */
typedef unsigned long VALUE;
#define Qnil ((VALUE)0)

/* real macro: unwraps the C pointer a Ruby T_DATA object wraps. Here rb_reader IS
 * that raw pointer (the harness constructs it directly and casts it to VALUE), so
 * unwrapping is the identity cast back. */
#define Data_Get_Struct(obj, type, sval) ((sval) = (type *)(obj))

static VALUE rb_hash_new(void) {
    /* stand-in Ruby Hash object: any non-NULL heap handle is sufficient -- nothing
     * downstream of rb_xml_reader_attribute_hash inspects its contents. */
    return (VALUE)(uintptr_t)malloc(1);
}

static VALUE rb_hash_aset(VALUE hash, VALUE key, VALUE val) {
    (void)key; (void)val;
    return hash;
}

/* NOKOGIRI_STR_NEW2(str) (ext/nokogiri/nokogiri.h) wraps a C string into a Ruby String
 * (real body: rb_external_str_new_with_enc(str, strlen(str), rb_utf8_encoding())).
 * Stand-in: heap-duplicate the bytes into an opaque handle. */
static VALUE nokogiri_str_new2_stub(const char *cstr) {
    size_t len = strlen(cstr);
    char *buf = (char *)malloc(len + 1);
    if (buf) memcpy(buf, cstr, len + 1);
    return (VALUE)(uintptr_t)buf;
}
#define NOKOGIRI_STR_NEW2(str) nokogiri_str_new2_stub((const char *)(str))

/* ---------------------------------------------------------------------
 * libxml2 tree types (real field names, verbatim from libxml/tree.h)
 * --------------------------------------------------------------------- */
typedef unsigned char xmlChar;

typedef enum {
    XML_ELEMENT_NODE=          1,
    XML_ATTRIBUTE_NODE=        2,
    XML_TEXT_NODE=             3,
    XML_CDATA_SECTION_NODE=    4,
    XML_ENTITY_REF_NODE=       5,
    XML_ENTITY_NODE=           6,
    XML_PI_NODE=                7,
    XML_COMMENT_NODE=          8,
    XML_DOCUMENT_NODE=          9,
    XML_DOCUMENT_TYPE_NODE=    10,
    XML_DOCUMENT_FRAG_NODE=    11,
    XML_NOTATION_NODE=         12,
    XML_HTML_DOCUMENT_NODE=    13,
    XML_DTD_NODE=                14,
    XML_ELEMENT_DECL=          15,
    XML_ATTRIBUTE_DECL=        16,
    XML_ENTITY_DECL=            17,
    XML_NAMESPACE_DECL=        18,
    XML_XINCLUDE_START=        19,
    XML_XINCLUDE_END=          20
} xmlElementType;
typedef xmlElementType xmlNsType;   /* real: "xmlNsType is unified with xmlElementType" */

typedef enum {
    XML_ATTRIBUTE_CDATA = 1,
    XML_ATTRIBUTE_ID,
    XML_ATTRIBUTE_IDREF,
    XML_ATTRIBUTE_IDREFS,
    XML_ATTRIBUTE_ENTITY,
    XML_ATTRIBUTE_ENTITIES,
    XML_ATTRIBUTE_NMTOKEN,
    XML_ATTRIBUTE_NMTOKENS,
    XML_ATTRIBUTE_ENUMERATION,
    XML_ATTRIBUTE_NOTATION
} xmlAttributeType;

struct _xmlDoc;   /* opaque here: never dereferenced by the code under test */

typedef struct _xmlNs {
    struct _xmlNs  *next;
    xmlNsType       type;
    const xmlChar  *href;
    const xmlChar  *prefix;
    void           *_private;
    struct _xmlDoc *context;
} xmlNs;
typedef xmlNs *xmlNsPtr;

typedef struct _xmlAttr {
    void             *_private;
    xmlElementType    type;
    const xmlChar    *name;
    struct _xmlNode  *children;
    struct _xmlNode  *last;
    struct _xmlNode  *parent;
    struct _xmlAttr  *next;
    struct _xmlAttr  *prev;
    struct _xmlDoc   *doc;
    xmlNs            *ns;
    xmlAttributeType  atype;
    void             *psvi;
} xmlAttr;
typedef xmlAttr *xmlAttrPtr;

typedef struct _xmlNode {
    void             *_private;
    xmlElementType    type;
    const xmlChar    *name;
    struct _xmlNode  *children;
    struct _xmlNode  *last;
    struct _xmlNode  *parent;
    struct _xmlNode  *next;
    struct _xmlNode  *prev;
    struct _xmlDoc   *doc;
    /* End of common part (shared prefix with _xmlAttr, matching the real libxml2
     * layout -- this is exactly what makes the target's own
     * `xmlNodeGetContent((xmlNode *)c_property)` cast well-defined). */
    xmlNs            *ns;
    xmlChar          *content;
    struct _xmlAttr  *properties;
    xmlNs            *nsDef;
    void             *psvi;
    unsigned short    line;
    unsigned short    extra;
} xmlNode;
typedef xmlNode *xmlNodePtr;

/* xmlNodeGetContent(cur) (tree.c): concatenates a node's text content into a fresh
 * xmlChar* the caller xmlFree()s. Stand-in: fabricate a small heap string from the
 * value we stashed in the node/attr's own _private slot at construction time (real,
 * generic "application data" field -- not stretching its documented purpose, and at
 * the SAME offset in both _xmlNode and _xmlAttr, so this is well-defined for the
 * target's xmlAttr-cast-to-xmlNode call exactly as in real libxml2). */
static xmlChar *xmlNodeGetContent(const xmlNode *cur) {
    if (!cur) return NULL;
    const char *v = (const char *)cur->_private;
    if (!v) return NULL;
    size_t len = strlen(v);
    xmlChar *out = (xmlChar *)malloc(len + 1);
    if (out) memcpy(out, v, len + 1);
    return out;
}
/* xmlFree really IS just free() by default (libxml2's xmlMemSetup, unless overridden). */
#define xmlFree free

/* ---------------------------------------------------------------------
 * xmlTextReader: opaque handle by design (`typedef struct _xmlTextReader xmlTextReader;`
 * in libxml/xmlreader.h -- the real struct body is PRIVATE to libxml2's own xmlreader.c
 * and not part of any public header). The harness's own bookkeeping fields are the only
 * reasonable stand-in for an intentionally-opaque type; xmlTextReaderCurrentNode() and
 * xmlTextReaderExpand() are the only two libxml2 entry points the code under test calls
 * (transitively, via has_attributes()), both minimal faithful stubs driven by the fields
 * below.
 * --------------------------------------------------------------------- */
typedef struct _xmlTextReader {
    xmlNodePtr current_node;   /* what xmlTextReaderCurrentNode() reports */
    xmlNodePtr expand_node;    /* what xmlTextReaderExpand() reports (NULL == parse error) */
} xmlTextReader;
typedef xmlTextReader *xmlTextReaderPtr;

static xmlNodePtr xmlTextReaderCurrentNode(xmlTextReaderPtr reader) {
    return reader ? reader->current_node : NULL;
}

/* The actual libxml2 API this bug is about: on well-formed-so-far-but-ultimately-broken
 * markup, the real xmlTextReaderExpand() returns NULL after failing to read ahead far
 * enough to build the full subtree -- exactly modelled here via expand_node. */
static xmlNodePtr xmlTextReaderExpand(xmlTextReaderPtr reader) {
    return reader ? reader->expand_node : NULL;
}

/* ================= real callee, VERBATIM from ext/nokogiri/xml_reader.c ================= */
static int
has_attributes(xmlTextReaderPtr reader)
{
  /*
   *  this implementation of xmlTextReaderHasAttributes explicitly includes
   *  namespaces and properties, because some earlier versions ignore
   *  namespaces.
   */
  xmlNodePtr node ;
  node = xmlTextReaderCurrentNode(reader);
  if (node == NULL) {
    return (0);
  }

  if ((node->type == XML_ELEMENT_NODE) &&
      ((node->properties != NULL) || (node->nsDef != NULL))) {
    return (1);
  }
  return (0);
}
/* ================= end verbatim has_attributes ================= */

/* ================= TARGET FUNCTION, byte-for-byte from
 * data_cve/cve_d87211c6/target/original_function.c ================= */
static VALUE
rb_xml_reader_attribute_hash(VALUE rb_reader)
{
  VALUE rb_attributes = rb_hash_new();
  xmlTextReaderPtr c_reader;
  xmlNodePtr c_node;
  xmlAttrPtr c_property;

  Data_Get_Struct(rb_reader, xmlTextReader, c_reader);

  if (!has_attributes(c_reader)) {
    return rb_attributes;
  }

  c_node = xmlTextReaderExpand(c_reader);
  c_property = c_node->properties;
  while (c_property != NULL) {
    VALUE rb_name = NOKOGIRI_STR_NEW2(c_property->name);
    VALUE rb_value = Qnil;
    xmlChar *c_value = xmlNodeGetContent((xmlNode *)c_property);

    if (c_value) {
      rb_value = NOKOGIRI_STR_NEW2(c_value);
      xmlFree(c_value);
    }

    rb_hash_aset(rb_attributes, rb_name, rb_value);

    c_property = c_property->next;
  }

  return rb_attributes;
}
/* ================= end verbatim target function ================= */

/* ---------------------------------------------------------------------
 * main(): builds a reader whose current node LOOKS like the already-consumed
 * `<foo bar="asdf" ...>` start tag (a real ELEMENT node with a real property -- so
 * has_attributes() truthfully reports 1 via the verbatim code path, exactly like the
 * real broken-markup repro), then drives the expand step from the input bytes:
 *   TRIGGER: expand_node = NULL          (models the parse-error/broken-markup path)
 *   SAFE:    expand_node = a real node with 0..3 real xmlAttr entries, walked cleanly.
 * --------------------------------------------------------------------- */
static xmlAttr *vb_make_attr(const char *name, const char *value) {
    xmlAttr *a = (xmlAttr *)calloc(1, sizeof(xmlAttr));
    a->type = XML_ATTRIBUTE_NODE;
    a->name = (const xmlChar *)strdup(name);
    a->_private = value ? (void *)strdup(value) : NULL;   /* read by our xmlNodeGetContent stub */
    return a;
}

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { fprintf(stderr, "cannot open %s\n", argv[1]); return 2; }
    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (sz < 0) sz = 0;
    size_t n = (size_t)sz;

    /* HEAP-allocate the raw input so it, and everything derived from it, is ASAN-guarded. */
    unsigned char *buf = (unsigned char *)malloc(n ? n : 1);
    if (!buf) { fclose(fp); return 2; }
    if (n) {
        if (fread(buf, 1, n, fp) != n) { fclose(fp); free(buf); return 2; }
    }
    fclose(fp);

    unsigned char mode = n > 0 ? buf[0] : 0;

    /* The reader's CURRENT node: the start tag <foo bar="asdf" xmlns:quux="qwer"> the real
     * repro has already read -- a real ELEMENT node carrying a real property, so
     * has_attributes() genuinely returns 1 (not bypassed). */
    xmlNode *current = (xmlNode *)calloc(1, sizeof(xmlNode));
    current->type = XML_ELEMENT_NODE;
    current->name = (const xmlChar *)"foo";
    current->properties = vb_make_attr("bar", "asdf");

    xmlTextReader reader;
    reader.current_node = current;

    if (mode & 1) {
        /* TRIGGER: broken markup downstream -> xmlTextReaderExpand() fails -> NULL.
         * rb_xml_reader_attribute_hash then dereferences c_node->properties on a NULL
         * c_node -> SIGSEGV inside rb_xml_reader_attribute_hash itself. */
        reader.expand_node = NULL;
    } else {
        /* SAFE: well-formed enough that expand succeeds; build 0..3 real properties
         * from the remaining input bytes and let the verbatim loop walk them to
         * completion (including the c_value-NULL branch via a NULL-valued attr). */
        xmlNode *expanded = (xmlNode *)calloc(1, sizeof(xmlNode));
        expanded->type = XML_ELEMENT_NODE;
        expanded->name = (const xmlChar *)"foo";

        unsigned int k = n > 1 ? (unsigned int)(buf[1] % 4) : 0;   /* 0..3 attributes */
        static const char *names[]  = {"bar", "id", "xmlns:quux", "data-x"};
        static const char *values[] = {"asdf", "7", "qwer", NULL};
        xmlAttr *head = NULL, *tail = NULL;
        for (unsigned int i = 0; i < k; i++) {
            xmlAttr *a = vb_make_attr(names[i % 4], values[i % 4]);
            if (!head) { head = a; } else { tail->next = a; }
            tail = a;
        }
        expanded->properties = head;
        reader.expand_node = expanded;
    }

    VALUE rb_reader = (VALUE)(uintptr_t)&reader;
    VALUE result = rb_xml_reader_attribute_hash(rb_reader);
    (void)result;

    free(buf);
    return 0;
}

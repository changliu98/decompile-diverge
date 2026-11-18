/* cve_barebone direct-call harness for CVE-2026-4224 (cpython / Modules/pyexpat.c)
 * Target: conv_content_model
 *
 * Bug class: CWE-674, Uncontrolled Recursion (ASAN reports it as `stack-overflow`).
 * conv_content_model() walks an expat XML_Content model tree (the data structure expat
 * builds while parsing a DTD <!ELEMENT ...> content-model declaration) and converts it
 * into a nested Python tuple, recursing ONE C stack frame per nesting level:
 *
 *     PyObject *child = conv_content_model(&model->children[i], conv_string);
 *
 * There is NO depth guard anywhere in the original function. A content model with N
 * nested groups -- fully attacker-controlled via an ordinary DTD like
 *     <!ELEMENT root (a, (a, (a, ... (a) ... )))>            (N levels of nesting)
 * -- makes conv_content_model recurse N C stack frames deep with no bound, exhausting the
 * thread's stack and crashing (a native SIGSEGV on the guard page, which ASAN reports as
 * `stack-overflow`). Upstream's own regression test reproduces it with N=500_000 nested
 * groups (Lib/test/test_pyexpat.py:test_deeply_nested_content_model). The fix
 * (196edfb06a7458377d4d0f4b3cd41724c1f3bd4a) adds a paired
 * _Py_EnterRecursiveCall()/_Py_LeaveRecursiveCall() guard around the recursive descent so
 * a bounded RecursionError is raised instead of a hard crash -- it does not otherwise touch
 * the function's logic.
 *
 * conv_content_model's own body is the ENTIRE crash mechanism (self-recursion on
 * attacker-shaped input); nothing outside it participates. Its three callees --
 * PyTuple_New / PyTuple_SET_ITEM / Py_XDECREF (CPython's tuple object API) and
 * Py_BuildValue (CPython's variadic object-builder) plus conv_string_to_unicode (real
 * pyexpat.c helper, the only conv_string implementation ever passed to
 * conv_content_model, see my_ElementDeclHandler) -- are all INCIDENTAL to the fault: they
 * only need to (a) let the recursive branch execute at every level (PyTuple_New must
 * return non-NULL whenever numchildren>0, exactly like the real CPython allocator, which
 * only returns NULL on genuine OOM) and (b) let a *shallow* call complete and return
 * normally so the safe/non-crashing inputs observe ordinary success -- the process
 * crashes from raw C call-stack exhaustion in conv_content_model's own recursive call
 * long before Py_BuildValue's real tuple-building semantics could matter. They are
 * minimal faithful stand-ins (same names/signatures as the real CPython C-API entry
 * points pyexpat.c itself calls), not reimplementations of CPython's object system.
 *
 * Official description: "xml.parsers.expat: Fixed a crash caused by unbounded C
 * recursion when converting deeply nested XML content models with
 * xml.parsers.expat.xmlparser.ElementDeclHandler." (CVE-2026-4224, GH-145986)
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <limits.h>     /* INT_MAX -- used by the verbatim assert() below */

/* ==== real Modules/expat/expat_external.h + expat.h type definitions (verbatim names/
 * shapes; XML_UNICODE is not defined in this build's expat_config.h, so XML_Char == char,
 * the "Information is UTF-8 encoded" branch). ================================= */

typedef char XML_Char;

enum XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};

typedef struct XML_cp XML_Content;

struct XML_cp {
  enum XML_Content_Type type;
  enum XML_Content_Quant quant;
  XML_Char *name;
  unsigned int numchildren;
  XML_Content *children;
};

/* ---- minimal faithful stand-ins for the CPython C-API calls conv_content_model makes
 * (real names/signatures from CPython's Include headers; incidental to the crash -- see
 * header comment). We deliberately never fail PyTuple_New (barring true OOM, same as the real
 * allocator) and never let Py_BuildValue return NULL, so the recursive branch always
 * executes at every level and only the raw C stack depth decides the outcome, exactly
 * like production CPython. Our harness only ever builds numchildren in {0,1} (see main),
 * so a tuple needs at most one storage slot. ------------------------------------- */

typedef struct PyObject {
    size_t n;              /* PyTuple_New: requested slot count (0 or 1 here) */
    struct PyObject *item0; /* PyTuple_SET_ITEM(t, 0, v) storage */
} PyObject;

static PyObject *
PyTuple_New(long size)
{
    PyObject *t = (PyObject *) malloc(sizeof(PyObject));
    if (t == NULL) {
        return NULL;
    }
    t->n = (size > 0) ? (size_t) size : 0;
    t->item0 = NULL;
    return t;
}

static void
PyTuple_SET_ITEM(PyObject *tup, int i, PyObject *v)
{
    if (tup != NULL && i == 0) {
        tup->item0 = v;
    }
}

static void
Py_XDECREF(PyObject *o)
{
    if (o != NULL) {
        free(o);
    }
}

/* Real pyexpat.c helper (Modules/pyexpat.c) -- the only function ever passed as
 * conv_content_model's `conv_string` argument (my_ElementDeclHandler calls
 * conv_content_model(model, (conv_string_to_unicode))). Real body decodes `str` as UTF-8
 * into a PyObject* via PyUnicode_DecodeUTF8(); never actually invoked on this crash path
 * (Py_BuildValue's real "O&" handling is what calls it, and our Py_BuildValue stand-in
 * below never touches its varargs), kept only so its address is a valid, correctly-typed
 * function pointer for conv_content_model to thread through, matching the real call site.
 */
static PyObject *
conv_string_to_unicode(const XML_Char *str)
{
    if (str == NULL) {
        return NULL;
    }
    return PyTuple_New(0);
}

/* Real CPython C-API (Include/modsupport.h): builds a new object from a format string +
 * varargs (here "(iiO&N)"). Never fails in production unless a sub-conversion fails, and
 * our only sub-conversion (conv_string_to_unicode, above) never fails either -- so this
 * stand-in just needs to unconditionally return a fresh, non-NULL object without touching
 * the (fault-irrelevant) varargs' *values*. It never inspects `format` or calls va_start,
 * so there's no risk of a va_arg type-mismatch in scaffolding code masquerading as the
 * real bug. */
static PyObject *
Py_BuildValue(const char *format, ...)
{
    (void) format;
    return PyTuple_New(0);
}

/* ==== VERBATIM from data_cve/cve_2b784c12/target/original_function.c (byte-for-byte,
 * this is the CVE-2026-4224 target function) ==================================== */

static PyObject *
conv_content_model(XML_Content * const model,
                   PyObject *(*conv_string)(const XML_Char *))
{
    PyObject *result = NULL;
    PyObject *children = PyTuple_New(model->numchildren);
    int i;

    if (children != NULL) {
        assert(model->numchildren < INT_MAX);
        for (i = 0; i < (int)model->numchildren; ++i) {
            PyObject *child = conv_content_model(&model->children[i],
                                                 conv_string);
            if (child == NULL) {
                Py_XDECREF(children);
                return NULL;
            }
            PyTuple_SET_ITEM(children, i, child);
        }
        result = Py_BuildValue("(iiO&N)",
                               model->type, model->quant,
                               conv_string,model->name, children);
    }
    return result;
}
/* ==== end verbatim ==== */

/* ---- driver ----------------------------------------------------------------- */

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }
    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        return 0;
    }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 0; }
    long fsz = ftell(fp);
    if (fsz < 0) { fclose(fp); return 0; }
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 0; }

    /* HEAP-allocate the raw input so ASAN guards it. */
    unsigned char *ibuf = (unsigned char *) malloc((size_t) (fsz > 0 ? fsz : 1));
    if (!ibuf) { fclose(fp); return 0; }
    size_t irn = fsz > 0 ? fread(ibuf, 1, (size_t) fsz, fp) : 0;
    fclose(fp);

    /* FDP-style argument construction: the input's first 4 bytes (little-endian), or its
     * single byte if shorter, choose N -- the XML content-model NESTING DEPTH. This is
     * exactly the attacker-controlled quantity a real DTD element declaration
     *   <!ELEMENT root (a, (a, (a, ... )))>          (N levels of nested groups)
     * maps to: expat's DTD content()/build_model() parser emits ONE XML_Content cell per
     * nesting level and wires each cell's `children` to point one level deeper into the
     * SAME flat array -- precisely the pool[] chain built below (see the struct XML_cp
     * doc comment in expat.h: "CHOICE and SEQ ... children will point, recursively, to an
     * array of XML_Content cells"). */
    uint32_t n = 0;
    if (irn >= 4) {
        n = (uint32_t) ibuf[0] | ((uint32_t) ibuf[1] << 8) |
            ((uint32_t) ibuf[2] << 16) | ((uint32_t) ibuf[3] << 24);
    } else if (irn > 0) {
        n = ibuf[0];
    }
    free(ibuf);

    if (n < 1) {
        n = 1;
    }
    if (n > 2000000U) {
        n = 2000000U;   /* sanity clamp only -- keeps the pool allocation bounded; the real
                          * bug has no such limit (that IS the CVE), this just protects the
                          * test box from an absurd multi-gigabyte alloc on a fuzzed N. */
    }

    XML_Content *pool = (XML_Content *) malloc((size_t) n * sizeof(XML_Content));
    if (!pool) {
        return 0;
    }
    for (uint32_t i = 0; i < n; i++) {
        if (i + 1 < n) {
            /* an inner SEQ group with exactly one nested child, matching the doc comment:
             * "CHOICE and SEQ will have name NULL, the number of children in numchildren
             * and children will point, recursively, to an array of XML_Content cells." */
            pool[i].type = XML_CTYPE_SEQ;
            pool[i].quant = XML_CQUANT_NONE;
            pool[i].name = NULL;
            pool[i].numchildren = 1;
            pool[i].children = &pool[i + 1];
        } else {
            /* the innermost element-name particle, e.g. the `a` of `(a, (a, ... ))`. */
            pool[i].type = XML_CTYPE_NAME;
            pool[i].quant = XML_CQUANT_NONE;
            pool[i].name = (XML_Char *) "a";
            pool[i].numchildren = 0;
            pool[i].children = NULL;
        }
    }

    PyObject *result = conv_content_model(&pool[0], conv_string_to_unicode);
    (void) result;

    free(pool);
    return 0;
}

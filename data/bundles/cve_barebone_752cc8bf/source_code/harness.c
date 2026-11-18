/* cve_barebone harness — mruby prepare_singleton_class / CVE-2022-0240
 *
 * Crash: src/class.c:360:13  `if (o->c->tt == MRB_TT_SCLASS) return;`
 *   reached with o->c == NULL -> UBSAN "member access within null pointer of
 *   type 'struct RClass'" (functionally CWE-476 NULL deref). Under ASAN this is a
 *   SEGV on a near-null address inside prepare_singleton_class. The whole bug is
 *   the very first statement of the function, so no callee ever runs.
 *
 * Real mruby types copied verbatim (real names) from data_cve/cve_752cc8bf/source_code:
 *   include/mruby/value.h  (enum mrb_vtype, mrb_value)
 *   include/mruby/object.h (MRB_OBJECT_HEADER, struct RBasic, struct RObject)
 *   include/mruby/class.h  (struct RClass, MRB_FL_CLASS_IS_INHERITED)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- include/mruby/value.h : scalar typedefs ---- */
typedef uint32_t mrb_sym;      /* value.h:23 */
typedef int64_t  mrb_int;
typedef double   mrb_float;

/* ---- include/mruby/value.h : enum mrb_vtype (MRB_VTYPE_FOREACH order, verbatim values) ---- */
enum mrb_vtype {
  MRB_TT_FALSE, MRB_TT_TRUE, MRB_TT_SYMBOL, MRB_TT_UNDEF, MRB_TT_FREE,
  MRB_TT_FLOAT, MRB_TT_INTEGER, MRB_TT_CPTR, MRB_TT_OBJECT, MRB_TT_CLASS,
  MRB_TT_MODULE, MRB_TT_ICLASS, MRB_TT_SCLASS, MRB_TT_PROC, MRB_TT_ARRAY,
  MRB_TT_HASH, MRB_TT_STRING, MRB_TT_RANGE, MRB_TT_EXCEPTION, MRB_TT_ENV,
  MRB_TT_DATA, MRB_TT_FIBER, MRB_TT_STRUCT, MRB_TT_ISTRUCT, MRB_TT_BREAK,
  MRB_TT_COMPLEX, MRB_TT_RATIONAL,
  MRB_TT_MAXDEFINE
};

/* opaque tables referenced by the class/object structs */
struct iv_tbl;
struct mt_tbl;

/* ---- include/mruby/object.h ---- */
#define MRB_OBJECT_HEADER \
  struct RClass *c;       \
  struct RBasic *gcnext;  \
  enum mrb_vtype tt:8;    \
  uint32_t color:3;       \
  uint32_t flags:21

struct RBasic {
  MRB_OBJECT_HEADER;
};

#define MRB_FL_OBJ_IS_FROZEN (1 << 20)   /* object.h:24 */

struct RObject {
  MRB_OBJECT_HEADER;
  struct iv_tbl *iv;
};

/* ---- include/mruby/class.h ---- */
struct RClass {
  MRB_OBJECT_HEADER;
  struct iv_tbl *iv;
  struct mt_tbl *mt;
  struct RClass *super;
};

#define MRB_FL_CLASS_IS_INHERITED (1 << 17)  /* class.h:71 */

/* ---- include/mruby/boxing_no.h : mrb_value ---- */
union mrb_value_union {
  mrb_float f;
  void *p;
  mrb_int i;
  mrb_sym sym;
};
typedef struct mrb_value {
  union mrb_value_union value;
  enum mrb_vtype tt;
} mrb_value;

/* minimal faithful mrb_state — only ->class_class is touched, and only PAST the
 * crash site (line 361), so it is never actually read on the crash path. */
typedef struct mrb_state {
  struct RClass *object_class;
  struct RClass *class_class;
} mrb_state;

/* ================= incidental callees =================
 * The crash is at the first statement (`o->c->tt`) with o->c == NULL, so NONE of
 * these run on any triggering input, and on safe inputs the function early-returns
 * at that same statement. They exist only so prepare_singleton_class links; each is
 * a minimal faithful no-op with the real signature/return type. */
struct RBasic *mrb_obj_alloc(mrb_state *mrb, enum mrb_vtype tt, struct RClass *cls) {
  (void)mrb; (void)tt; (void)cls; return NULL;
}
/* mruby.h:1179 — real macro casts to the tt's C type; MRB_TT_SCLASS -> struct RClass */
#define MRB_OBJ_ALLOC(mrb, tt, klass) ((struct RClass*)mrb_obj_alloc((mrb), (tt), (klass)))

struct mt_tbl *mt_new(mrb_state *mrb) { (void)mrb; return NULL; }

static void make_metaclass(mrb_state *mrb, struct RClass *c) { (void)mrb; (void)c; }

void mrb_field_write_barrier(mrb_state *mrb, struct RBasic *a, struct RBasic *b) {
  (void)mrb; (void)a; (void)b;
}

mrb_value mrb_obj_value(void *p) {
  mrb_value v;
  memset(&v, 0, sizeof v);
  v.value.p = p;
  v.tt = MRB_TT_OBJECT;
  return v;
}

void mrb_obj_iv_set(mrb_state *mrb, struct RObject *obj, mrb_sym sym, mrb_value v) {
  (void)mrb; (void)obj; (void)sym; (void)v;
}

/* presym/disable.h resolves MRB_SYM to an intern call; unreachable here -> a constant. */
#define MRB_SYM(name) ((mrb_sym)0)

/* forward decl so main can take the address before the definition below */
static void prepare_singleton_class(mrb_state *mrb, struct RBasic *o);

/* ================= TARGET FUNCTION (verbatim) ================= */
static void
prepare_singleton_class(mrb_state *mrb, struct RBasic *o)
{
  struct RClass *sc, *c;

  if (o->c->tt == MRB_TT_SCLASS) return;
  sc = MRB_OBJ_ALLOC(mrb, MRB_TT_SCLASS, mrb->class_class);
  sc->flags |= MRB_FL_CLASS_IS_INHERITED;
  sc->mt = mt_new(mrb);
  sc->iv = 0;
  if (o->tt == MRB_TT_CLASS) {
    c = (struct RClass*)o;
    if (!c->super) {
      sc->super = mrb->class_class;
    }
    else {
      sc->super = c->super->c;
    }
  }
  else if (o->tt == MRB_TT_SCLASS) {
    c = (struct RClass*)o;
    while (c->super->tt == MRB_TT_ICLASS)
      c = c->super;
    make_metaclass(mrb, c->super);
    sc->super = c->super->c;
  }
  else {
    sc->super = o->c;
    prepare_singleton_class(mrb, (struct RBasic*)sc);
  }
  o->c = sc;
  mrb_field_write_barrier(mrb, (struct RBasic*)o, (struct RBasic*)sc);
  mrb_field_write_barrier(mrb, (struct RBasic*)sc, (struct RBasic*)o);
  mrb_obj_iv_set(mrb, (struct RObject*)sc, MRB_SYM(__attached__), mrb_obj_value(o));
  sc->flags |= o->flags & MRB_FL_OBJ_IS_FROZEN;
}
/* ================= isolation driver ================= */

/* call through a volatile function pointer so -O1 cannot inline the target away
 * (keeps prepare_singleton_class as a real frame in the crash stack). */
static void (*volatile g_call)(mrb_state *, struct RBasic *) = prepare_singleton_class;

int
main(int argc, char **argv)
{
  if (argc < 2) return 0;
  FILE *f = fopen(argv[1], "rb");
  if (!f) return 0;
  fseek(f, 0, SEEK_END);
  long sz = ftell(f);
  fseek(f, 0, SEEK_SET);
  if (sz < 0) sz = 0;
  /* HEAP buffer so any overread of the input itself is ASAN-visible */
  unsigned char *buf = (unsigned char *)malloc((size_t)(sz > 0 ? sz : 1));
  size_t n = fread(buf, 1, (size_t)sz, f);
  fclose(f);

  /* FDP: leading bytes drive the argument construction */
  unsigned char sel  = (n >= 1) ? buf[0] : 0;   /* bit7 selects trigger vs safe */
  unsigned char tsel = (n >= 2) ? buf[1] : 0;    /* varies o->tt for coverage    */
  unsigned char fsel = (n >= 3) ? buf[2] : 0;    /* varies o->flags for coverage */

  /* mrb_state (only ->class_class, used past the crash site) */
  mrb_state *mrb = (mrb_state *)malloc(sizeof(mrb_state));
  memset(mrb, 0, sizeof(*mrb));
  struct RClass *cc = (struct RClass *)malloc(sizeof(struct RClass));
  memset(cc, 0, sizeof(*cc));
  cc->tt = MRB_TT_CLASS;
  mrb->class_class = cc;
  mrb->object_class = cc;

  /* the receiver object o, heap-allocated so ASAN guards the class-pointer deref */
  struct RObject *obj = (struct RObject *)malloc(sizeof(struct RObject));
  memset(obj, 0, sizeof(*obj));
  struct RBasic *o = (struct RBasic *)obj;
  o->tt = (enum mrb_vtype)(tsel % (unsigned)MRB_TT_MAXDEFINE);
  o->flags = (uint32_t)fsel & 0x1fffffu;

  if (sel & 0x80u) {
    /* TRIGGER: uninitialised class pointer (the CVE-2022-0240 defect) ->
     * o->c->tt dereferences NULL at src/class.c:360:13 */
    o->c = NULL;
  } else {
    /* SAFE: a valid singleton class -> o->c->tt == MRB_TT_SCLASS -> early return */
    struct RClass *sc = (struct RClass *)malloc(sizeof(struct RClass));
    memset(sc, 0, sizeof(*sc));
    sc->tt = MRB_TT_SCLASS;
    o->c = sc;
  }

  g_call(mrb, o);

  free(buf);
  return 0;
}

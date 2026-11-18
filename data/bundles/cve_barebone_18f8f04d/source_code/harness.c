/* cve_barebone harness -- CVE-2024-25177 / openresty/luajit2 snap_unsink()
 *
 * Root cause + why -fsanitize=null is required: see scripts/gen_dc_cve_18f8f04d.py docstring.
 *
 * Isolated reproduction: fabricate a minimal IR array representing a SUNK IR_TNEW (a table
 * allocation the optimizer proved dead outside a snapshot) whose only pending store is the
 * field `t.metatable`, with the stored *value* itself an IR_KNULL constant (exactly what
 * recff_setmetatable() records for `setmetatable(t, nil)`), then call snap_unsink() directly
 * -- the same call lj_snap_restore() makes when unwinding a trace exit through that snapshot.
 *
 * Everything below is either (a) the real LuaJIT type/macro definitions snap_unsink's own
 * body needs (copied, real names, from lj_obj.h/lj_ir.h/lj_target.h/lj_jit.h/lj_def.h -- often
 * *partial* structs: only the fields this call path actually touches, e.g. jit_State keeps
 * only its real `L` field out of ~50), (b) real crash-path callees copied VERBATIM
 * (snap_restoreval, snap_sunk_store[2], lj_ir_kvalue, snap_renameref), or (c) minimal faithful
 * stubs for GC-allocator machinery that is irrelevant to the bug (lj_tab_new/lj_tab_dup/
 * lj_tab_set: real signatures, minimal bodies -- lj_tab_dup is never actually invoked by any
 * crafted input, TNEW is always used, but the symbol must exist because the ternary that
 * selects between them is compiled either way).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

/* ============================================================================================
 * Build-config knobs (real lj_arch.h values for x86-64; LJ_HASFFI=0 = LUAJIT_DISABLE_FFI, a
 * real supported knob that only removes the CNEW/CNEWI branch -- unreached by our input either
 * way, since the bug is in the TNEW/TDUP (table) branch). lua_assert/check_exp reproduce the
 * DEFAULT release build (upstream Makefile ships with LUA_USE_ASSERT commented out): no-ops,
 * exactly like real LuaJIT out of the box. The crash we reproduce is caught by UBSan's null
 * check (harness.flags), independent of lua_assert.
 * ============================================================================================ */
#define LJ_64 1
#define LJ_HASFFI 0
#define LJ_SOFTFP 0
#define LJ_DUALNUM 0
#define LJ_52 0

#define UNUSED(x)               ((void)(x))
#define LJ_LIKELY(x)            (x)
#define LJ_UNLIKELY(x)          (x)
#define LJ_ALIGN(n)             __attribute__((aligned(n)))
#define LJ_AINLINE              inline __attribute__((always_inline))
#define LJ_ENDIAN_LOHI(lo, hi)  lo hi          /* little-endian (x86-64) selection */

#define lua_assert(c)           ((void)0)
#define check_exp(c, e)         (e)

typedef double lua_Number;     /* LUA_NUMBER, luaconf.h */

/* ============================================================================================
 * lj_obj.h (real defs, verbatim where copied; a subset -- global_State/GCproto debug fields/
 * etc are never touched by this call path so are omitted or left partial)
 * ============================================================================================ */
typedef uint32_t MSize;

typedef struct MRef { uint32_t ptr32; } MRef;
#define mref(r, t)      ((t *)(void *)(uintptr_t)(r).ptr32)
#define setmref(r, p)   ((r).ptr32 = (uint32_t)(uintptr_t)(void *)(p))

typedef struct GCRef { uint32_t gcptr32; } GCRef;
#define GCHeader        GCRef nextgc; uint8_t marked; uint8_t gct

#define gcref(r)        ((GCobj *)(uintptr_t)(r).gcptr32)
#define gcrefp(r, t)    ((t *)(void *)(uintptr_t)(r).gcptr32)
#define setgcref(r, gc)     ((r).gcptr32 = (uint32_t)(uintptr_t)&(gc)->gch)
#define setgcrefi(r, i)     ((r).gcptr32 = (uint32_t)(i))
#define setgcrefp(r, p)     ((r).gcptr32 = (uint32_t)(uintptr_t)(p))
#define setgcrefnull(r)     ((r).gcptr32 = 0)

/* Forward-declare (incomplete tag is fine for pointer params/casts): completed once GCstr,
 * GCtab, etc are defined below (MID1), so setgcV/define_setV can reference GCobj and lua_State
 * pointers up here without reordering the (much larger) real object-struct definitions. */
typedef struct lua_State lua_State;
typedef union GCobj GCobj;

typedef uint32_t BCIns;
typedef uint32_t BCPos;
typedef uint32_t BCReg;
typedef int32_t BCLine;

typedef LJ_ALIGN(8) union TValue {
  uint64_t u64;
  lua_Number n;
  struct {
    LJ_ENDIAN_LOHI(
      union { GCRef gcr; int32_t i; };
    , uint32_t it;
    )
  };
  struct {
    LJ_ENDIAN_LOHI(
      uint32_t lo;
    , uint32_t hi;
    )
  } u32;
} TValue;
typedef const TValue cTValue;

#define LJ_TNIL         (~0u)
#define LJ_TFALSE       (~1u)
#define LJ_TTRUE        (~2u)
#define LJ_TLIGHTUD     (~3u)
#define LJ_TSTR         (~4u)
#define LJ_TUPVAL       (~5u)
#define LJ_TTHREAD      (~6u)
#define LJ_TPROTO       (~7u)
#define LJ_TFUNC        (~8u)
#define LJ_TTRACE       (~9u)
#define LJ_TCDATA       (~10u)
#define LJ_TTAB         (~11u)
#define LJ_TUDATA       (~12u)
#define LJ_TNUMX        (~13u)
#if LJ_64
#define LJ_TISNUM       0xfffeffffu
#else
#define LJ_TISNUM       LJ_TNUMX
#endif

#define itype(o)        ((o)->it)
#define tvisnil(o)      (itype(o) == LJ_TNIL)
#if LJ_64
#define tvislightud(o)  (((int32_t)itype(o) >> 15) == -2)
#else
#define tvislightud(o)  (itype(o) == LJ_TLIGHTUD)
#endif
#define tvistab(o)      (itype(o) == LJ_TTAB)
#define tvisint(o)      (LJ_DUALNUM && itype(o) == LJ_TISNUM)
#define tvispri(o)      (itype(o) >= LJ_TTRUE)

#define gcval(o)        (gcref((o)->gcr))
#if LJ_64
#define lightudV(o) \
  check_exp(tvislightud(o), (void *)((o)->u64 & ((uint64_t)0x00007fffffffffffULL)))
#else
#define lightudV(o)     check_exp(tvislightud(o), gcrefp((o)->gcr, void))
#endif
#define tabV(o)         check_exp(tvistab(o), &gcval(o)->tab)
#define intV(o)         check_exp(tvisint(o), (int32_t)(o)->i)

#define setitype(o, i)      ((o)->it = (i))
#define setnilV(o)          ((o)->it = LJ_TNIL)
#define setnumV(o, x)       ((o)->n = (x))

static LJ_AINLINE void setintV(TValue *o, int32_t i)
{
#if LJ_DUALNUM
  o->i = (uint32_t)i; setitype(o, LJ_TISNUM);
#else
  o->n = (lua_Number)i;
#endif
}

static LJ_AINLINE void setlightudV(TValue *o, void *p)
{
#if LJ_64
  o->u64 = (uint64_t)p | (((uint64_t)0xffff) << 48);
#else
  setgcrefp(o->gcr, p); setitype(o, LJ_TLIGHTUD);
#endif
}

/* obj2gco is forward-usable (just a cast macro); setgcV/define_setV need the COMPLETE GCobj
 * union (they dereference it), so they're defined in MID1 below, right before their use. */
#define obj2gco(v)      ((GCobj *)(v))

/* -- String / userdata / cdata / prototype / upvalue / function / table objects (real defs) - */
typedef struct GCstr {
  GCHeader;
  uint8_t reserved;
  uint8_t unused;
  MSize hash;
  MSize len;
} GCstr;

typedef struct GCudata {
  GCHeader;
  uint8_t udtype;
  uint8_t unused2;
  GCRef env;
  MSize len;
  GCRef metatable;
  uint32_t align1;
} GCudata;

typedef struct GCcdata {
  GCHeader;
  uint16_t ctypeid;
} GCcdata;

typedef struct GCproto {
  GCHeader;
  uint8_t numparams;
  uint8_t framesize;
  MSize sizebc;
  GCRef gclist;
  MRef k;
  MRef uv;
  MSize sizekgc;
  MSize sizekn;
  MSize sizept;
  uint8_t sizeuv;
  uint8_t flags;
  uint16_t trace;
  GCRef chunkname;
  BCLine firstline;
  BCLine numline;
  MRef lineinfo;
  MRef uvinfo;
  MRef varinfo;
} GCproto;

typedef struct GCupval {
  GCHeader;
  uint8_t closed;
  uint8_t immutable;
  union {
    TValue tv;
    struct { GCRef prev; GCRef next; };
  };
  MRef v;
  uint32_t dhash;
} GCupval;

typedef int (*lua_CFunction)(struct lua_State *L);

#define GCfuncHeader \
  GCHeader; uint8_t ffid; uint8_t nupvalues; \
  GCRef env; GCRef gclist; MRef pc

typedef struct GCfuncC {
  GCfuncHeader;
  lua_CFunction f;
  TValue upvalue[1];
} GCfuncC;

typedef struct GCfuncL {
  GCfuncHeader;
  GCRef uvptr[1];
} GCfuncL;

typedef union GCfunc {
  GCfuncC c;
  GCfuncL l;
} GCfunc;

typedef struct GCtab {
  GCHeader;
  uint8_t nomm;
  int8_t colo;
  MRef array;
  GCRef gclist;
  GCRef metatable;
  MRef node;
  uint32_t asize;
  uint32_t hmask;
} GCtab;

/* Per-thread state -- only the header + real field NAMES; nothing below touches its contents
 * (this call path never reads/writes any lua_State field -- lua_assert(c)=((void)0) means `c`
 * is never even evaluated, so tvchecklive()'s G(L) dereference in the real setgcV is dead too;
 * global_State is therefore never needed and is omitted entirely). */
struct lua_State {
  GCHeader;
  uint8_t dummy_ffid;
  uint8_t status;
  MRef glref;
  GCRef gclist;
  TValue *base;
  TValue *top;
  MRef maxstack;
  MRef stack;
  GCRef openupval;
  GCRef env;
  void *cframe;
  MSize stacksize;
};

typedef struct GChead {
  GCHeader;
  uint8_t unused1;
  uint8_t unused2;
  GCRef env;
  GCRef gclist;
  GCRef metatable;
} GChead;

union GCobj {
  GChead gch;
  GCstr str;
  GCupval uv;
  lua_State th;
  GCproto pt;
  GCfunc fn;
  GCcdata cd;
  GCtab tab;
  GCudata ud;
};

/* setgcV/define_setV: need the now-complete GCobj union (setgcref dereferences ->gch). */
static LJ_AINLINE void setgcV(lua_State *L, TValue *o, GCobj *v, uint32_t itypearg)
{
  setgcref(o->gcr, v); setitype(o, itypearg); UNUSED(L);
}
#define define_setV(name, type, tag) \
static LJ_AINLINE void name(lua_State *L, TValue *o, type *v) \
{ \
  setgcV(L, o, obj2gco(v), tag); \
}
define_setV(settabV, GCtab, LJ_TTAB)

/* ============================================================================================
 * lj_ir.h (real defs: IROp/IRFieldID/IRType enums copied wholesale -- values are internal-only
 * and only ever compared for equality within this TU, so omitted entries are harmless; the
 * IRFLDEF offsetof() arguments are syntactically required but their VALUES are discarded by
 * the FLENUM enumerator macro, same as upstream)
 * ============================================================================================ */
#define IRDEF(_) \
  _(LT, N, ref, ref) _(GE, N, ref, ref) _(LE, N, ref, ref) _(GT, N, ref, ref) \
  _(ULT, N, ref, ref) _(UGE, N, ref, ref) _(ULE, N, ref, ref) _(UGT, N, ref, ref) \
  _(EQ, C, ref, ref) _(NE, C, ref, ref) \
  _(ABC, N, ref, ref) _(RETF, S, ref, ref) \
  _(NOP, N, ___, ___) _(BASE, N, lit, lit) _(PVAL, N, lit, ___) _(GCSTEP, S, ___, ___) \
  _(HIOP, S, ref, ref) _(LOOP, S, ___, ___) _(USE, S, ref, ___) _(PHI, S, ref, ref) \
  _(RENAME, S, ref, lit) \
  _(KPRI, N, ___, ___) _(KINT, N, cst, ___) _(KGC, N, cst, ___) _(KPTR, N, cst, ___) \
  _(KKPTR, N, cst, ___) _(KNULL, N, cst, ___) _(KNUM, N, cst, ___) _(KINT64, N, cst, ___) \
  _(KSLOT, N, ref, lit) \
  _(BNOT, N, ref, ___) _(BSWAP, N, ref, ___) _(BAND, C, ref, ref) _(BOR, C, ref, ref) \
  _(BXOR, C, ref, ref) _(BSHL, N, ref, ref) _(BSHR, N, ref, ref) _(BSAR, N, ref, ref) \
  _(BROL, N, ref, ref) _(BROR, N, ref, ref) \
  _(ADD, C, ref, ref) _(SUB, N, ref, ref) _(MUL, C, ref, ref) _(DIV, N, ref, ref) \
  _(MOD, N, ref, ref) _(POW, N, ref, ref) _(NEG, N, ref, ref) \
  _(ABS, N, ref, ref) _(ATAN2, N, ref, ref) _(LDEXP, N, ref, ref) _(MIN, C, ref, ref) \
  _(MAX, C, ref, ref) _(FPMATH, N, ref, lit) \
  _(ADDOV, CW, ref, ref) _(SUBOV, NW, ref, ref) _(MULOV, CW, ref, ref) \
  _(AREF, R, ref, ref) _(HREFK, R, ref, ref) _(HREF, L, ref, ref) _(NEWREF, S, ref, ref) \
  _(UREFO, LW, ref, lit) _(UREFC, LW, ref, lit) _(FREF, R, ref, lit) _(STRREF, N, ref, ref) \
  _(ALOAD, L, ref, ___) _(HLOAD, L, ref, ___) _(ULOAD, L, ref, ___) _(FLOAD, L, ref, lit) \
  _(XLOAD, L, ref, lit) _(SLOAD, L, lit, lit) _(VLOAD, L, ref, ___) \
  _(ASTORE, S, ref, ref) _(HSTORE, S, ref, ref) _(USTORE, S, ref, ref) _(FSTORE, S, ref, ref) \
  _(XSTORE, S, ref, ref) \
  _(SNEW, N, ref, ref) _(XSNEW, A, ref, ref) _(TNEW, AW, lit, lit) _(TDUP, AW, ref, ___) \
  _(CNEW, AW, ref, ref) _(CNEWI, NW, ref, ref) \
  _(TBAR, S, ref, ___) _(OBAR, S, ref, ref) _(XBAR, S, ___, ___) \
  _(CONV, N, ref, lit) _(TOBIT, N, ref, ref) _(TOSTR, N, ref, ___) _(STRTO, N, ref, ___) \
  _(CALLN, N, ref, lit) _(CALLL, L, ref, lit) _(CALLS, S, ref, lit) _(CALLXS, S, ref, ref) \
  _(CARG, N, ref, ref)

typedef enum {
#define IRENUM(name, m, m1, m2) IR_##name,
IRDEF(IRENUM)
#undef IRENUM
  IR__MAX
} IROp;
typedef uint8_t IROp1;

#define IRFLDEF(_) \
  _(STR_LEN,      offsetof(GCstr, len)) \
  _(FUNC_ENV,     offsetof(GCfunc, l.env)) \
  _(FUNC_PC,      offsetof(GCfunc, l.pc)) \
  _(TAB_META,     offsetof(GCtab, metatable)) \
  _(TAB_ARRAY,    offsetof(GCtab, array)) \
  _(TAB_NODE,     offsetof(GCtab, node)) \
  _(TAB_ASIZE,    offsetof(GCtab, asize)) \
  _(TAB_HMASK,    offsetof(GCtab, hmask)) \
  _(TAB_NOMM,     offsetof(GCtab, nomm)) \
  _(UDATA_META,   offsetof(GCudata, metatable)) \
  _(UDATA_UDTYPE, offsetof(GCudata, udtype)) \
  _(UDATA_FILE,   sizeof(GCudata)) \
  _(CDATA_CTYPEID, offsetof(GCcdata, ctypeid)) \
  _(CDATA_PTR,    sizeof(GCcdata)) \
  _(CDATA_INT,    sizeof(GCcdata)) \
  _(CDATA_INT64,  sizeof(GCcdata)) \
  _(CDATA_INT64_4, sizeof(GCcdata) + 4)

typedef enum {
#define FLENUM(name, ofs) IRFL_##name,
IRFLDEF(FLENUM)
#undef FLENUM
  IRFL__MAX
} IRFieldID;

#define IRTDEF(_) \
  _(NIL, 4) _(FALSE, 4) _(TRUE, 4) _(LIGHTUD, 8) _(STR, 4) \
  _(P32, 4) _(THREAD, 4) _(PROTO, 4) _(FUNC, 4) _(P64, 8) _(CDATA, 4) \
  _(TAB, 4) _(UDATA, 4) \
  _(FLOAT, 4) _(NUM, 8) _(I8, 1) _(U8, 1) _(I16, 2) _(U16, 2) \
  _(INT, 4) _(U32, 4) _(I64, 8) _(U64, 8) \
  _(SOFTFP, 4)

typedef enum {
#define IRTENUM(name, size) IRT_##name,
IRTDEF(IRTENUM)
#undef IRTENUM
  IRT__MAX
} IRType;

typedef struct IRType1 { uint8_t irt; } IRType1;
#define irt_type(t)             ((IRType)((t).irt & 0x1f))
#define irt_isinteger(t) \
  ((uint32_t)((t).irt & 0x1f) - (uint32_t)(IRT_I8) <= (uint32_t)(IRT_INT - IRT_I8))
#define irt_isnum(t)            (irt_type(t) == IRT_NUM)
#define irt_islightud(t)        (irt_type(t) == IRT_LIGHTUD)
#define irt_ispri(t)            ((uint32_t)irt_type(t) <= IRT_TRUE)

#define IRCONV_DSH              5
#define IRCONV_NUM_INT          ((IRT_NUM << IRCONV_DSH) | IRT_INT)

static LJ_AINLINE uint32_t irt_toitype_(IRType t)
{
  lua_assert(!LJ_64 || t != IRT_LIGHTUD);
  if (LJ_DUALNUM && t > IRT_NUM) {
    return LJ_TISNUM;
  } else {
    lua_assert(t <= IRT_NUM);
    return ~(uint32_t)t;
  }
}
#define irt_toitype(t)          irt_toitype_(irt_type((t)))

typedef uint16_t IROpT;
typedef uint16_t IRRef1;
typedef uint32_t IRRef2;
typedef uint32_t IRRef;

enum { REF_BIAS = 0x8000 };
#define irref_isk(ref)          ((ref) < REF_BIAS)

typedef union IRIns {
  struct {
    LJ_ENDIAN_LOHI(
      IRRef1 op1;
    , IRRef1 op2;
    )
    IROpT ot;
    IRRef1 prev;
  };
  struct {
    IRRef2 op12;
    LJ_ENDIAN_LOHI(
      IRType1 t;
    , IROp1 o;
    )
    LJ_ENDIAN_LOHI(
      uint8_t r;
    , uint8_t s;
    )
  };
  int32_t i;
  GCRef gcr;
  MRef ptr;
} IRIns;

#define ir_kgc(ir)      check_exp((ir)->o == IR_KGC, gcref((ir)->gcr))
#define gco2tab(o)      check_exp((o)->gch.gct == ~LJ_TTAB, &(o)->tab)
#define ir_ktab(ir)     (gco2tab(ir_kgc((ir))))
#define ir_knum(ir)     check_exp((ir)->o == IR_KNUM, mref((ir)->ptr, cTValue))

/* ============================================================================================
 * lj_target.h (real x86-64 register IDs + RegSP encoding) + lj_jit.h (SnapShot/SnapNo/GCtrace/
 * jit_State -- the latter two kept PARTIAL: only the real fields this call path touches) +
 * lj_def.h (BloomFilter)
 * ============================================================================================ */
typedef uint32_t Reg;
#define GPRDEF(_) \
  _(EAX) _(ECX) _(EDX) _(EBX) _(ESP) _(EBP) _(ESI) _(EDI) \
  _(R8D) _(R9D) _(R10D) _(R11D) _(R12D) _(R13D) _(R14D) _(R15D)
#define FPRDEF(_) \
  _(XMM0) _(XMM1) _(XMM2) _(XMM3) _(XMM4) _(XMM5) _(XMM6) _(XMM7) \
  _(XMM8) _(XMM9) _(XMM10) _(XMM11) _(XMM12) _(XMM13) _(XMM14) _(XMM15)
#define RIDENUM(name)   RID_##name,
enum {
  GPRDEF(RIDENUM)
  FPRDEF(RIDENUM)
  RID_MAX,
  RID_MIN_GPR = RID_EAX,
  RID_MIN_FPR = RID_XMM0,
  RID_MAX_GPR = RID_MIN_FPR,
  RID_MAX_FPR = RID_MAX,
  RID_NUM_GPR = RID_MAX_GPR - RID_MIN_GPR,
  RID_NUM_FPR = RID_MAX_FPR - RID_MIN_FPR,
};

#define RID_NONE        0x80
#define RID_MASK        0x7f
#define RID_INIT        (RID_NONE|RID_MASK)
#define RID_SINK        (RID_INIT-1)
#define RID_SUNK        (RID_INIT-2)
#define ra_noreg(r)     ((r) & RID_NONE)
#define SPS_NONE        0
#define ra_hasspill(s)  ((s) != SPS_NONE)

typedef uint32_t RegSP;
#define REGSP(r, s)             ((r) + ((s) << 8))
#define regsp_reg(rs)           ((rs) & 255)
#define regsp_spill(rs)         ((rs) >> 8)

/* This definition must match with the *.dasc file(s) -- real def, lj_target_x86.h. */
typedef struct {
  lua_Number fpr[RID_NUM_FPR];
  intptr_t gpr[RID_NUM_GPR];
  int32_t spill[256];
} ExitState;

typedef struct SnapShot {
  uint32_t mapofs;
  IRRef1 ref;
  uint8_t nslots;
  uint8_t topslot;
  uint8_t nent;
  uint8_t count;
} SnapShot;

typedef uint32_t SnapNo;

/* GCtrace/jit_State: PARTIAL, real field names -- only what snap_unsink's call graph reads
 * (T->ir, T->snap, T->nins; J->L). The other ~10 GCtrace fields and ~45 jit_State fields
 * (mcode buffers, IR emission buffers, penalty caches, register-allocator scratch, ...) are
 * recorder/assembler-only state, never touched when snap_unsink is called directly. */
typedef struct GCtrace {
  IRRef nins;
  IRIns *ir;
  SnapShot *snap;
} GCtrace;

typedef struct jit_State {
  lua_State *L;
} jit_State;

typedef uintptr_t BloomFilter;
#define BLOOM_MASK      (8*sizeof(BloomFilter) - 1)
#define bloombit(x)     ((uintptr_t)1 << ((x) & BLOOM_MASK))
#define bloomtest(b, x) ((b) & bloombit((x)))

/* ============================================================================================
 * Real crash-path callees, copied VERBATIM from source_code/src/{lj_ir.c,lj_snap.c}.
 * ============================================================================================ */

/* -- lj_ir_kvalue (lj_ir.c) -- */
void lj_ir_kvalue(lua_State *L, TValue *tv, const IRIns *ir)
{
  UNUSED(L);
  lua_assert(ir->o != IR_KSLOT);  /* Common mistake. */
  switch (ir->o) {
  case IR_KPRI: setitype(tv, irt_toitype(ir->t)); break;
  case IR_KINT: setintV(tv, ir->i); break;
  case IR_KGC: setgcV(L, tv, ir_kgc(ir), irt_toitype(ir->t)); break;
  case IR_KPTR: case IR_KKPTR: case IR_KNULL:
    setlightudV(tv, mref(ir->ptr, void));
    break;
  case IR_KNUM: setnumV(tv, ir_knum(ir)->n); break;
#if LJ_HASFFI
  case IR_KINT64: {
    GCcdata *cd = lj_cdata_new_(L, CTID_INT64, 8);
    *(uint64_t *)cdataptr(cd) = ir_kint64(ir)->u64;
    setcdataV(L, tv, cd);
    break;
    }
#endif
  default: lua_assert(0); break;
  }
}

/* -- snap_renameref (lj_snap.c) -- */
static RegSP snap_renameref(GCtrace *T, SnapNo lim, IRRef ref, RegSP rs)
{
  IRIns *ir;
  for (ir = &T->ir[T->nins-1]; ir->o == IR_RENAME; ir--)
    if (ir->op1 == ref && ir->op2 <= lim)
      rs = ir->prev;
  return rs;
}

/* -- snap_sunk_store2 / snap_sunk_store (lj_snap.c) -- */
static int snap_sunk_store2(GCtrace *T, IRIns *ira, IRIns *irs)
{
  if (irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
      irs->o == IR_FSTORE || irs->o == IR_XSTORE) {
    IRIns *irk = &T->ir[irs->op1];
    if (irk->o == IR_AREF || irk->o == IR_HREFK)
      irk = &T->ir[irk->op1];
    return (&T->ir[irk->op1] == ira);
  }
  return 0;
}

static LJ_AINLINE int snap_sunk_store(GCtrace *T, IRIns *ira, IRIns *irs)
{
  if (irs->s != 255)
    return (ira + irs->s == irs);  /* Fast check. */
  return snap_sunk_store2(T, ira, irs);
}

/* -- snap_restoreval (lj_snap.c) -- */
static void snap_restoreval(jit_State *J, GCtrace *T, ExitState *ex,
			    SnapNo snapno, BloomFilter rfilt,
			    IRRef ref, TValue *o)
{
  IRIns *ir = &T->ir[ref];
  IRType1 t = ir->t;
  RegSP rs = ir->prev;
  if (irref_isk(ref)) {  /* Restore constant slot. */
    lj_ir_kvalue(J->L, o, ir);
    return;
  }
  if (LJ_UNLIKELY(bloomtest(rfilt, ref)))
    rs = snap_renameref(T, snapno, ref, rs);
  if (ra_hasspill(regsp_spill(rs))) {  /* Restore from spill slot. */
    int32_t *sps = &ex->spill[regsp_spill(rs)];
    if (irt_isinteger(t)) {
      setintV(o, *sps);
#if !LJ_SOFTFP
    } else if (irt_isnum(t)) {
      o->u64 = *(uint64_t *)sps;
#endif
    } else if (LJ_64 && irt_islightud(t)) {
      /* 64 bit lightuserdata which may escape already has the tag bits. */
      o->u64 = *(uint64_t *)sps;
    } else {
      lua_assert(!irt_ispri(t));  /* PRI refs never have a spill slot. */
      setgcrefi(o->gcr, *sps);
      setitype(o, irt_toitype(t));
    }
  } else {  /* Restore from register. */
    Reg r = regsp_reg(rs);
    if (ra_noreg(r)) {
      lua_assert(ir->o == IR_CONV && ir->op2 == IRCONV_NUM_INT);
      snap_restoreval(J, T, ex, snapno, rfilt, ir->op1, o);
      if (LJ_DUALNUM) setnumV(o, (lua_Number)intV(o));
      return;
    } else if (irt_isinteger(t)) {
      setintV(o, (int32_t)ex->gpr[r-RID_MIN_GPR]);
#if !LJ_SOFTFP
    } else if (irt_isnum(t)) {
      setnumV(o, ex->fpr[r-RID_MIN_FPR]);
#endif
    } else if (LJ_64 && irt_islightud(t)) {
      /* 64 bit lightuserdata which may escape already has the tag bits. */
      o->u64 = ex->gpr[r-RID_MIN_GPR];
    } else {
      if (!irt_ispri(t))
	setgcrefi(o->gcr, ex->gpr[r-RID_MIN_GPR]);
      setitype(o, irt_toitype(t));
    }
  }
}

/* ============================================================================================
 * Minimal faithful stubs: real signatures (lj_tab.h), GC-allocator/hash-table internals
 * (irrelevant to the bug) replaced by a plain heap allocation. lj_tab_dup/lj_tab_set are
 * never actually invoked by any crafted input (our sunk alloc is always IR_TNEW, and the
 * only sunk store we ever construct targets the metatable field, not an array/hash slot) --
 * but the symbols must exist because snap_unsink's `ir->o==IR_TNEW ? lj_tab_new(...) :
 * lj_tab_dup(...)` ternary and the array/hash "else" branch are compiled in either way.
 * ============================================================================================ */
static GCtab *lj_tab_new(lua_State *L, uint32_t asize, uint32_t hbits)
{
  UNUSED(L); UNUSED(asize); UNUSED(hbits);
  GCtab *t = (GCtab *)calloc(1, sizeof(GCtab));
  t->gct = (uint8_t)(~LJ_TTAB);
  setgcrefnull(t->metatable);
  return t;
}

static GCtab *lj_tab_dup(lua_State *L, const GCtab *kt)
{
  UNUSED(L); UNUSED(kt);
  return lj_tab_new(L, 0, 0);   /* never actually invoked; see comment above */
}

static TValue *lj_tab_set(lua_State *L, GCtab *t, cTValue *key)
{
  UNUSED(L); UNUSED(t); UNUSED(key);
  static TValue dummy;   /* never actually invoked; see comment above */
  return &dummy;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) ================= */
static void snap_unsink(jit_State *J, GCtrace *T, ExitState *ex,
			SnapNo snapno, BloomFilter rfilt,
			IRIns *ir, TValue *o)
{
  lua_assert(ir->o == IR_TNEW || ir->o == IR_TDUP ||
	     ir->o == IR_CNEW || ir->o == IR_CNEWI);
#if LJ_HASFFI
  if (ir->o == IR_CNEW || ir->o == IR_CNEWI) {
    CTState *cts = ctype_cts(J->L);
    CTypeID id = (CTypeID)T->ir[ir->op1].i;
    CTSize sz = lj_ctype_size(cts, id);
    GCcdata *cd = lj_cdata_new(cts, id, sz);
    setcdataV(J->L, o, cd);
    if (ir->o == IR_CNEWI) {
      uint8_t *p = (uint8_t *)cdataptr(cd);
      lua_assert(sz == 4 || sz == 8);
      if (LJ_32 && sz == 8 && ir+1 < T->ir + T->nins && (ir+1)->o == IR_HIOP) {
	snap_restoredata(T, ex, snapno, rfilt, (ir+1)->op2, LJ_LE?p+4:p, 4);
	if (LJ_BE) p += 4;
	sz = 4;
      }
      snap_restoredata(T, ex, snapno, rfilt, ir->op2, p, sz);
    } else {
      IRIns *irs, *irlast = &T->ir[T->snap[snapno].ref];
      for (irs = ir+1; irs < irlast; irs++)
	if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	  IRIns *iro = &T->ir[T->ir[irs->op1].op2];
	  uint8_t *p = (uint8_t *)cd;
	  CTSize szs;
	  lua_assert(irs->o == IR_XSTORE && T->ir[irs->op1].o == IR_ADD);
	  lua_assert(iro->o == IR_KINT || iro->o == IR_KINT64);
	  if (irt_is64(irs->t)) szs = 8;
	  else if (irt_isi8(irs->t) || irt_isu8(irs->t)) szs = 1;
	  else if (irt_isi16(irs->t) || irt_isu16(irs->t)) szs = 2;
	  else szs = 4;
	  if (LJ_64 && iro->o == IR_KINT64)
	    p += (int64_t)ir_k64(iro)->u64;
	  else
	    p += iro->i;
	  lua_assert(p >= (uint8_t *)cdataptr(cd) &&
		     p + szs <= (uint8_t *)cdataptr(cd) + sz);
	  if (LJ_32 && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    lua_assert(szs == 4);
	    snap_restoredata(T, ex, snapno, rfilt, (irs+1)->op2, LJ_LE?p+4:p,4);
	    if (LJ_BE) p += 4;
	  }
	  snap_restoredata(T, ex, snapno, rfilt, irs->op2, p, szs);
	}
    }
  } else
#endif
  {
    IRIns *irs, *irlast;
    GCtab *t = ir->o == IR_TNEW ? lj_tab_new(J->L, ir->op1, ir->op2) :
				  lj_tab_dup(J->L, ir_ktab(&T->ir[ir->op1]));
    settabV(J->L, o, t);
    irlast = &T->ir[T->snap[snapno].ref];
    for (irs = ir+1; irs < irlast; irs++) {
      if (irs->r == RID_SINK && snap_sunk_store(T, ir, irs)) {
	IRIns *irk = &T->ir[irs->op1];
	TValue tmp, *val;
	lua_assert(irs->o == IR_ASTORE || irs->o == IR_HSTORE ||
		   irs->o == IR_FSTORE);
	if (irk->o == IR_FREF) {
	  switch (irk->op2) {
	  case IRFL_TAB_META:
	    snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, &tmp);
	    /* NOBARRIER: The table is new (marked white). */
	    setgcref(t->metatable, obj2gco(tabV(&tmp)));
	    break;
	  case IRFL_TAB_NOMM:
	    /* Negative metamethod cache invalidated by lj_tab_set() below. */
	    break;
	  default:
	    lua_assert(0);
	    break;
	  }
	} else {
	  irk = &T->ir[irk->op2];
	  if (irk->o == IR_KSLOT) irk = &T->ir[irk->op1];
	  lj_ir_kvalue(J->L, &tmp, irk);
	  val = lj_tab_set(J->L, t, &tmp);
	  /* NOBARRIER: The table is new (marked white). */
	  snap_restoreval(J, T, ex, snapno, rfilt, irs->op2, val);
	  if (LJ_SOFTFP && irs+1 < T->ir + T->nins && (irs+1)->o == IR_HIOP) {
	    snap_restoreval(J, T, ex, snapno, rfilt, (irs+1)->op2, &tmp);
	    val->u32.hi = tmp.u32.lo;
	  }
	}
      }
    }
  }
}

/* ================================= driver ================================= */
/*
 * Fabricates the minimal fake IR array + GCtrace that reproduces the exact call
 * lj_snap_restore() makes when unwinding a trace exit through a sunk table allocation whose
 * only pending store sets the metatable field:
 *
 *   T_ir[0] = IR_TNEW                                     (the sunk allocation itself, `ir`)
 *   T_ir[1] = IR_FSTORE  op1=T_ir[2] op2=T_ir[3]  r=RID_SINK s=1     (the sunk store, `irs`)
 *   T_ir[2] = IR_FREF    op2=IRFL_TAB_META                            (`irk`: which field)
 *   T_ir[3] = IR_KNULL   i=0 t=IRT_TAB          <-- TRIGGER mode: setmetatable(t, nil)
 *          or IR_KGC  gcr=&dummy_mt t=IRT_TAB   <-- SAFE mode:    setmetatable(t, dummy_mt)
 *   T.snap[0].ref = 2   -> irlast = &T_ir[2], so the unsink loop visits exactly T_ir[1]
 *
 * mode = data[0] % 3 selects the scenario per input byte 0 (heap-read, ASAN-guarded):
 *   0 -> no store at all (bare `local t = {}`)                              SAFE
 *   1 -> metatable store, KNULL value (`setmetatable(t, nil)`)              TRIGGER (the bug)
 *   2 -> metatable store, real-table value (`setmetatable(t, dummy_mt)`)    SAFE (same shape,
 *        proves the crash is conditioned on the KNULL-ness of the stored value, not merely on
 *        the presence of a metatable store)
 */
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
  if (got < 1) { free(data); return 0; }                      /* empty -> nothing to do, clean */

  int mode = data[0] % 3;

  /* real lua_State / jit_State / GCtrace -- see the PARTIAL-struct comments above for why
   * only .L / .ir / .snap / .nins are ever populated. */
  lua_State *L = (lua_State *)calloc(1, sizeof(lua_State));
  jit_State J; memset(&J, 0, sizeof J); J.L = L;

  IRIns *T_ir = (IRIns *)calloc(4, sizeof(IRIns));
  SnapShot T_snap[1]; memset(T_snap, 0, sizeof T_snap);
  GCtrace T; memset(&T, 0, sizeof T);
  T.ir = T_ir; T.snap = T_snap; T.nins = 4;

  ExitState ex; memset(&ex, 0, sizeof ex);

  /* T_ir[0]: the sunk allocation itself -- IR_TNEW(asize, hbits); values unused by our stub. */
  T_ir[0].o = IR_TNEW;
  T_ir[0].op1 = (IRRef1)(data[1 % got] & 3);
  T_ir[0].op2 = (IRRef1)(data[2 % got] & 3);

  GCtab *dummy_mt = NULL;   /* mode 2's "real, valid metatable" object */

  if (mode == 0) {
    /* no pending store: irlast == ir+1 immediately, snap_unsink just allocates and returns */
    T_snap[0].ref = 1;
  } else {
    T_snap[0].ref = 2;      /* irlast = &T_ir[2]: unsink loop visits exactly T_ir[1] */

    /* T_ir[1]: the sunk field store, `t.metatable = <T_ir[3]>` */
    T_ir[1].o = IR_FSTORE;
    T_ir[1].op1 = 2;                 /* -> T_ir[2], the FREF */
    T_ir[1].op2 = 3;                 /* -> T_ir[3], the stored value */
    T_ir[1].r = RID_SINK;
    T_ir[1].s = (uint8_t)(&T_ir[1] - &T_ir[0]);   /* == 1: snap_sunk_store() fast path */

    /* T_ir[2]: IR_FREF selecting the metatable field */
    T_ir[2].o = IR_FREF;
    T_ir[2].op1 = 0;                 /* -> T_ir[0] (the table); unused on this path */
    T_ir[2].op2 = IRFL_TAB_META;

    if (mode == 1) {
      /* T_ir[3]: IR_KNULL, IRT_TAB -- exactly lj_ir_knull(J, IRT_TAB)'s output for
       * `setmetatable(t, nil)`. i=0 always (the real interner never produces anything else). */
      T_ir[3].o = IR_KNULL;
      T_ir[3].i = 0;
      T_ir[3].t.irt = (uint8_t)IRT_TAB;
    } else {
      /* T_ir[3]: IR_KGC referencing a real, valid GCtab -- `setmetatable(t, dummy_mt)`. */
      dummy_mt = (GCtab *)calloc(1, sizeof(GCtab));
      dummy_mt->gct = (uint8_t)(~LJ_TTAB);
      T_ir[3].o = IR_KGC;
      setgcref(T_ir[3].gcr, obj2gco(dummy_mt));
      T_ir[3].t.irt = (uint8_t)IRT_TAB;
    }
  }

  TValue out; memset(&out, 0, sizeof out);

  /* Call through a volatile function pointer: guarantees snap_unsink is NOT inlined into
   * main (so it stays a real, reported stack frame) without touching a single byte of its
   * own (verbatim, byte-for-byte) body. */
  void (*volatile fn)(jit_State *, GCtrace *, ExitState *, SnapNo, BloomFilter, IRIns *, TValue *)
      = snap_unsink;
  fn(&J, &T, &ex, 0, (BloomFilter)0, &T_ir[0], &out);

  free(T_ir);
  free(dummy_mt);
  free(L);
  free(data);
  return 0;
}

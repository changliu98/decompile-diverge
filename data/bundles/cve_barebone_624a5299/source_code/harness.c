/* cve_barebone harness -- jsish jsi_ArraySpliceCmd forged-.length OOB read (CWE-125)
 *
 * Isolated reproduction: jsi_ArraySpliceCmd() is called directly on a hand-built array
 * Jsi_Obj whose physical `arr[]` backing store is small (a handful of real elements,
 * arrCnt==arrMaxSize==phys_n) but whose ->tree forges a "length" property far larger than
 * phys_n. Jsi_ObjGetLength() (real, verbatim -- this IS the pre-fix buggy-usage contract)
 * trusts that forged length unconditionally, so jsi_ArraySpliceCmd's own copy loop walks
 * obj->arr[i] for i far past the real allocation -> heap-buffer-overflow READ, caught by ASAN
 * inside jsi_ArraySpliceCmd itself.
 *
 * TRIGGER: tree "length" == phys_n + 8..2007 (always > phys_n)  -> OOB read at i==phys_n.
 * SAFE:    no tree (real ->arrCnt used) or tree "length" <= phys_n -> every access in-bounds.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>

/* ---- real base typedefs (jsi.h, verbatim) ---- */
typedef int64_t  Jsi_Wide;
typedef uint64_t Jsi_UWide;
typedef double    Jsi_Number;           /* JSI_USE_LONG_DOUBLE not defined -- the default build */
typedef unsigned int   uint;
typedef unsigned char  uchar;

/* ---- opaque real names (jsi.h itself forward-declares Jsi_Interp this way; nothing this
 * harness calls ever dereferences interp or funcPtr -- jsi_ArraySpliceCmd's own body only
 * threads them through to callees, all of which are defined below without touching them). ---- */
typedef struct Jsi_Interp Jsi_Interp;
typedef struct Jsi_Func   Jsi_Func;
typedef struct Jsi_Regex   Jsi_Regex;
typedef struct Jsi_FuncObj Jsi_FuncObj;
typedef struct Jsi_IterObj Jsi_IterObj;
typedef struct Jsi_UserObj Jsi_UserObj;

typedef struct Jsi_Obj   Jsi_Obj;
typedef struct Jsi_Value Jsi_Value;
typedef struct Jsi_Tree  Jsi_Tree;

/* ---- Jsi_RC / Jsi_otype / Jsi_vtype (jsi.h, verbatim) ---- */
typedef enum {
    JSI_OK=0, JSI_ERROR=1, JSI_RETURN=2, JSI_BREAK=3,
    JSI_CONTINUE=4, JSI_SIGNAL=5, JSI_EXIT=6, JSI_EVAL=7,
} Jsi_RC;

typedef enum {
    JSI_OT_UNDEF, JSI_OT_BOOL, JSI_OT_NUMBER, JSI_OT_STRING, JSI_OT_OBJECT,
    JSI_OT_ARRAY, JSI_OT_FUNCTION, JSI_OT_REGEXP, JSI_OT_ITER, JSI_OT_USEROBJ,
    JSI_OT__MAX = JSI_OT_USEROBJ
} Jsi_otype;

typedef enum {
    JSI_VT_UNDEF, JSI_VT_BOOL, JSI_VT_NUMBER, JSI_VT_STRING, JSI_VT_OBJECT,
    JSI_VT_NULL, JSI_VT_VARIABLE, JSI_VT__MAX = JSI_VT_VARIABLE
} Jsi_vtype;

/* ---- Jsi_String (jsi.h, verbatim -- embedded by value in both d-unions below) ---- */
typedef struct {
    char *str;
    int32_t len;
    uint32_t flags;
} Jsi_String;

/* ---- Jsi_Tree -- MINIMAL FAITHFUL STUB. Upstream (jsiInt.h/jsiObj.c) is a full intrusive
 * red-black tree (Jsi_Tree wraps Jsi_Map, keyed through interp->strKeyTbl string interning)
 * used for EVERY object's non-array-index property storage -- pure incidental plumbing, not
 * part of this bug. jsi_ArraySpliceCmd's call graph (via the real, verbatim Jsi_ObjGetLength)
 * only ever probes ONE property out of it: "length". This stub keeps the real field name
 * (`numEntries`) that Jsi_ObjGetLength's own verbatim body branches on, plus a single
 * key/value slot -- exactly enough to plant a forged "length" the way real jsish does when an
 * array is object-shaped / had .length assigned directly (Jsi_ObjSetLength's non-isarrlist
 * branch literally Jsi_ObjInsert()s a tree entry named "length"). */
struct Jsi_Tree {
    int numEntries;
    const char *key;
    Jsi_Value *value;
};

/* ---- Jsi_Obj / Jsi_Value (jsiInt.h, verbatim field layout -- JSI_HAS_SIG / JSI_MEM_DEBUG
 * both undefined here, matching the plain non-debug build those #ifdef guard). These are the
 * ONLY two structs jsi_ArraySpliceCmd's own body dereferences directly
 * (_this->vt, _this->d.obj, obj->arr[i], nobj->arr[m]). ---- */
struct Jsi_Obj {
    int refcnt;
    Jsi_otype ot:8;
    uint isarrlist:1;
    uint isstrkey:1;
    uint isJSONstr:1;
    uint clearProto:1;
    uint isNoOp:1;
    uint isBlob:1;
    uint unused2:16;
    union {
        int val;
        Jsi_Number num;
        Jsi_String s;
        Jsi_Regex *robj;
        Jsi_FuncObj *fobj;
        Jsi_IterObj *iobj;
        Jsi_UserObj *uobj;
    } d;
    uint arrMaxSize;
    uint arrCnt;
    Jsi_Value **arr;
    Jsi_Tree *tree;
    Jsi_Value *__proto__;
    struct Jsi_Obj *constructor;
    struct Jsi_Obj *next, *prev;
    int gc_refs;
};

struct Jsi_Value {
    int32_t refCnt;
    Jsi_vtype vt:8;
    union {
        uint flag:8;
        struct vflagbit {
            uint readonly:1;
            uint dontenum:1;
            uint dontdel:1;
            uint innershared:1;
            uint isarrlist:1;
            uint isstrkey:1;
            uint local:1;
            uint lookupfailed:1;
        } bits;
    } f;
    union {
        int val;
        Jsi_Number num;
        Jsi_String s;
        Jsi_Obj *obj;
        struct Jsi_Value *lval;
        const char *lookupFail;
    } d;
    struct Jsi_Value *next, *prev;
};

/* ---- ALLOC_MOD_SIZE / MAX_ARRAY_LIST (jsiInt.h, verbatim) ---- */
#define ALLOC_MOD_SIZE 16
#define MAX_ARRAY_LIST 100000
#define Assert(n) assert(n)

/* ---- JSI_LOG_* + Jsi_LogError/Jsi_LogWarn macros (jsi.h, verbatim -- both expand to a call
 * on the caller's own local `interp`, which every real callee here has as a parameter). ---- */
#define JSI_LOG_BUG   0
#define JSI_LOG_ERROR 1
#define JSI_LOG_WARN  2
#define Jsi_LogError(fmt,...) Jsi_LogMsg(interp, JSI_LOG_ERROR, fmt, ##__VA_ARGS__)
#define Jsi_LogWarn(fmt,...)  Jsi_LogMsg(interp, JSI_LOG_WARN,  fmt, ##__VA_ARGS__)

/* Jsi_LogMsg -- minimal faithful stub (real: jsiUtils.c, formats+dispatches to interp's log
 * sink/stderr). None of this harness's inputs are designed to reach an error path, so this is
 * link-only scaffolding; kept real-signature + real printf-style behavior for honesty. */
Jsi_RC Jsi_LogMsg(Jsi_Interp *interp, uint code, const char *format, ...) {
    (void)interp; (void)code;
    va_list ap; va_start(ap, format); vfprintf(stderr, format, ap); va_end(ap);
    fputc('\n', stderr);
    return JSI_ERROR;
}

/* Jsi_Realloc -- real body verbatim (jsiUtils.c). */
void* Jsi_Realloc(void *m, unsigned int size) {
    void *v = realloc(m, size);
    Assert(v);
    return v;
}

/* Jsi_TreeObjGetValue -- MINIMAL FAITHFUL STUB (see the Jsi_Tree comment above): real key/value
 * lookup contract, backed by the single-slot stub tree instead of the real Jsi_Map. */
Jsi_Value *Jsi_TreeObjGetValue(Jsi_Obj *obj, const char *key, int isstrkey) {
    (void)isstrkey;
    Jsi_Tree *t = obj->tree;
    if (!t || t->numEntries <= 0) return NULL;
    if (t->key && strcmp(t->key, key) == 0) return t->value;
    return NULL;
}

/* Jsi_NumberIsInteger -- real body verbatim (jsiNumber.c). */
bool Jsi_NumberIsInteger(Jsi_Number n) { return (isnormal(n) ? (Jsi_Number)((Jsi_Wide)(n)) == (n) : n==0.0); }

/* Jsi_GetNumberFromValue -- real body verbatim (jsiUtils.c). Converts the "start"/"howmany"
 * splice args (and, via Jsi_ObjGetLength below, a forged tree "length") from a Jsi_Value to a
 * Jsi_Number. */
Jsi_RC Jsi_GetNumberFromValue(Jsi_Interp *interp, Jsi_Value *value, Jsi_Number *n) {
    if (!value)
        return JSI_ERROR;
    if (value->vt == JSI_VT_NUMBER) {
        *n = value->d.num;
        return JSI_OK;
    }
    if (value->vt == JSI_VT_OBJECT && value->d.obj->ot == JSI_OT_NUMBER) {
        *n = value->d.obj->d.num;
        return JSI_OK;
    }
    if (interp)
        Jsi_LogError("invalid number");
    return JSI_ERROR;
}

/* Jsi_ObjIsArray -- real body verbatim (jsiObj.c). */
bool Jsi_ObjIsArray(Jsi_Interp *interp, Jsi_Obj *o) {
    (void)interp;
    return (o->ot == JSI_OT_OBJECT && o->isarrlist);
}

/* Jsi_ValueIsArray -- real body verbatim (jsiValue.c); feeds Jsi_ValueGetLength below. */
bool Jsi_ValueIsArray(Jsi_Interp *interp, Jsi_Value *v) {
    (void)interp;
    return (v->vt == JSI_VT_OBJECT && v->d.obj->ot == JSI_OT_OBJECT && v->d.obj->isarrlist);
}

/* Jsi_ValueGetLength -- real body verbatim (jsiValue.c). Used for `argc` (the splice args
 * array's own arrCnt) -- always a real array in this harness, so the Jsi_LogWarn branch is
 * dead but kept for link/behavioral fidelity. */
int Jsi_ValueGetLength(Jsi_Interp *interp, Jsi_Value *v) {
    if (Jsi_ValueIsArray(interp, v))
        return v->d.obj->arrCnt;
    Jsi_LogWarn("expected array");
    return 0;
}

/* Jsi_NumberItoA10 -- real body verbatim (jsiNumber.c); only reached by Jsi_ValueArrayIndex's
 * non-isarrlist fallback below, which this harness's args/this arrays never take (both are
 * always isarrlist with ->arr set) but is kept verbatim rather than trimmed. */
void Jsi_NumberItoA10(Jsi_Wide value, char *buf, int bsiz) {
    snprintf(buf, bsiz, "%" PRId64, value);
}

/* Jsi_ValueArrayIndex -- real body verbatim (jsiValue.c). Fetches args[0]/args[1]
 * (start/howmany) in jsi_ArraySpliceCmd, and (dead in this corpus, ilen==0 always) args[i] for
 * extra insert values. */
Jsi_Value *Jsi_ValueArrayIndex(Jsi_Interp *interp, Jsi_Value *args, int index) {
    Jsi_Obj *obj = args->d.obj;
    Jsi_Value *v;
    assert(args->vt == JSI_VT_OBJECT);
    if (obj->isarrlist && obj->arr)
        return ((index < 0 || (uint)index >= obj->arrCnt) ? NULL : obj->arr[index]);
    char unibuf[100];
    Jsi_NumberItoA10(index, unibuf, sizeof(unibuf));
    v = Jsi_TreeObjGetValue(args->d.obj, unibuf, 0);
    return v;
}

/* Jsi_ObjGetLength -- *** THE pre-fix buggy-usage function, real body VERBATIM (jsiObj.c),
 * byte-for-byte unchanged by the fix (the fix instead stopped jsi_ArraySpliceCmd from calling
 * it). This is the exact contract that lets a forged ->tree "length" outrun the real ->arrCnt
 * physical array size. *** */
int Jsi_ObjGetLength(Jsi_Interp *interp, Jsi_Obj *obj) {
    if (obj->tree && obj->tree->numEntries) {
        Jsi_Value *r = Jsi_TreeObjGetValue(obj, "length", 0);
        Jsi_Number nr;
        if (r && Jsi_GetNumberFromValue(interp, r, &nr) == JSI_OK) {
            if (Jsi_NumberIsInteger(nr))
                return nr;
        }
    }
    if (obj->arr)
        return obj->arrCnt;
    return 0;
}

/* Jsi_ObjArraySizer -- real body verbatim (jsiObj.c). Grows/tracks a Jsi_Obj's real ->arr
 * backing store; used here on `nobj` (the splice's return array) BEFORE the OOB loop runs --
 * this is what makes the crash a genuine READ overflow on the SOURCE array rather than a WRITE
 * overflow on the destination. */
int Jsi_ObjArraySizer(Jsi_Interp *interp, Jsi_Obj *obj, uint len) {
    int nsiz = len + 1, mod = ALLOC_MOD_SIZE;
    assert(obj->isarrlist);
    if (mod > 1)
        nsiz = nsiz + ((mod - 1) - (nsiz + mod - 1) % mod);
    if (nsiz > MAX_ARRAY_LIST) {
        Jsi_LogError("array size too large");
        return 0;
    }
    if (len >= obj->arrMaxSize) {
        int oldsz = (nsiz - obj->arrMaxSize);
        obj->arr = (Jsi_Value**)Jsi_Realloc(obj->arr, nsiz * sizeof(Jsi_Value*));
        memset(obj->arr + obj->arrMaxSize, 0, oldsz * sizeof(Jsi_Value*));
        obj->arrMaxSize = nsiz;
    }
    if (len > obj->arrCnt)
        obj->arrCnt = len;
    return nsiz;
}

/* Jsi_ObjSetLength -- MINIMAL FAITHFUL STUB of the real function's isarrlist branch (real body:
 * jsiObj.c). Every Jsi_Obj this harness builds (both the source array and the freshly-made
 * return array) has isarrlist==1, so that branch --
 *     if (obj->isarrlist) { assert(len<=obj->arrMaxSize); obj->arrCnt = len; return; }
 * -- is copied verbatim; the non-isarrlist branch (Jsi_ObjInsert()ing a "length" tree entry --
 * real interpreters take this branch for object-shaped/non-listified arrays) is provably dead
 * here and omitted rather than dragged in for no behavioral effect. */
void Jsi_ObjSetLength(Jsi_Interp *interp, Jsi_Obj *obj, uint len) {
    (void)interp;
    assert(obj->isarrlist);
    assert(len <= obj->arrMaxSize);
    obj->arrCnt = len;
}

/* Jsi_ObjListifyArray -- MINIMAL FAITHFUL STUB. Real body's very first action (jsiObj.c) is
 *     if (!obj->arr) ... else return;
 * i.e. `if (obj->arr) return;` -- every Jsi_Obj this harness builds already has ->arr set, so
 * that is always the taken branch; the tree-walk-to-array conversion body (unreachable here)
 * is omitted. */
void Jsi_ObjListifyArray(Jsi_Interp *interp, Jsi_Obj *obj) {
    (void)interp;
    if (!obj->isarrlist) return;
    if (obj->arr) return;
}

/* Jsi_ObjNewType -- MINIMAL FAITHFUL STUB. Real body (jsiObj.c) additionally threads the new
 * object onto interp's GC list and assigns ->__proto__ from one of interp's prototype objects
 * -- pure JS-prototype-chain bookkeeping jsi_ArraySpliceCmd's call graph never reads. Kept: the
 * two fields that graph actually depends on, ->ot and ->isarrlist. */
Jsi_Obj *Jsi_ObjNewType(Jsi_Interp *interp, Jsi_otype otype) {
    (void)interp;
    Jsi_Obj *obj = (Jsi_Obj*)calloc(1, sizeof(Jsi_Obj));
    obj->refcnt = 1;
    obj->ot = (otype == JSI_OT_ARRAY ? JSI_OT_OBJECT : otype);
    if (otype == JSI_OT_ARRAY) obj->isarrlist = 1;
    return obj;
}

/* Jsi_ValueMakeArrayObject -- MINIMAL FAITHFUL STUB of the branch this harness always takes
 * (vPtr's target pre-allocated by main(), matching how the real interpreter's command
 * dispatcher always pre-supplies `ret` -- see jsiEval.c call sites). Real body additionally
 * sets ->__proto__=interp->Array_prototype and bumps a GC refcount, both incidental. The
 * Jsi_ObjArraySizer(o,0) call IS the real, verbatim function -- it is what actually gives
 * `nobj` its initial arr[] backing store. */
Jsi_Value *Jsi_ValueMakeArrayObject(Jsi_Interp *interp, Jsi_Value **vPtr, Jsi_Obj *o) {
    Jsi_Value *v = (vPtr ? *vPtr : NULL);
    if (!o) o = Jsi_ObjNewType(interp, JSI_OT_ARRAY);
    if (!v) v = (Jsi_Value*)calloc(1, sizeof(Jsi_Value));   /* fallback; unreached here */
    v->vt = JSI_VT_OBJECT;
    v->d.obj = o;
    o->ot = JSI_OT_OBJECT;
    o->isarrlist = 1;
    Jsi_ObjArraySizer(interp, o, 0);
    return v;
}

/* Jsi_ValueMakeNull / Jsi_ValueMakeUndef -- MINIMAL FAITHFUL STUBS (real bodies: jsiValue.c).
 * Only reached via bail2 (args[0]=="start" missing) or the "array too long" error path -- this
 * harness's inputs never take either branch; kept for link fidelity. */
Jsi_Value *Jsi_ValueMakeNull(Jsi_Interp *interp, Jsi_Value **vPtr) {
    (void)interp;
    Jsi_Value *v = (vPtr ? *vPtr : NULL);
    if (!v) v = (Jsi_Value*)calloc(1, sizeof(Jsi_Value));
    v->vt = JSI_VT_NULL;
    return v;
}
Jsi_Value *Jsi_ValueMakeUndef(Jsi_Interp *interp, Jsi_Value **vPtr) {
    (void)interp;
    Jsi_Value *v = (vPtr ? *vPtr : NULL);
    if (!v) v = (Jsi_Value*)calloc(1, sizeof(Jsi_Value));
    v->vt = JSI_VT_UNDEF;
    return v;
}

/* Jsi_ValueDup2 -- MINIMAL FAITHFUL STUB (real body: jsiValue.c, copies `from` into a
 * possibly-fresh `*to`). Never invoked in this harness's corpus: ilen==argc-2==0 always
 * (args always carries exactly 2 slots, start+howmany, no extra insert values), so the
 * `if (ilen>0)` block in jsi_ArraySpliceCmd that calls this is provably dead code here. Kept
 * only so the file links. */
void Jsi_ValueDup2(Jsi_Interp *interp, Jsi_Value **to, Jsi_Value *from) {
    (void)interp;
    if (!*to) *to = (Jsi_Value*)calloc(1, sizeof(Jsi_Value));
    if (from) **to = *from; else memset(*to, 0, sizeof(Jsi_Value));
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
static Jsi_RC jsi_ArraySpliceCmd(Jsi_Interp *interp, Jsi_Value *args, Jsi_Value *_this,Jsi_Value **ret, Jsi_Func *funcPtr)
{
    if (_this->vt != JSI_VT_OBJECT || !Jsi_ObjIsArray(interp, _this->d.obj))
        return Jsi_LogError("expected array object");
    int newlen, argc, istart, n, rhowmany, ilen, curlen;
    Jsi_Value *va, *start, *howmany;
    Jsi_Obj *nobj, *obj = _this->d.obj;
    
    start = Jsi_ValueArrayIndex(interp, args, 0);
    howmany = Jsi_ValueArrayIndex(interp, args, 1);
    argc = Jsi_ValueGetLength(interp, args);
    istart = 0;
    ilen = (argc>=2 ? argc - 2 : 0);
    n = Jsi_ObjGetLength(interp, obj);
    curlen = n;
    
    if (!start) {
        goto bail2;
    }

    nobj = Jsi_ObjNewType(interp, JSI_OT_ARRAY);
    Jsi_ValueMakeArrayObject(interp, ret, nobj);
    Jsi_ObjSetLength(interp, nobj, 0);
    
    /* Determine start index. */
    Jsi_Number nstart;
    if (Jsi_GetNumberFromValue(interp, start, &nstart) == JSI_OK) {
        istart = (int)nstart;
        if (istart > n)
            goto bail;
        if (istart < 0)
            istart = (n+istart);
        if (istart<0)
            istart=0;
    }
      
    Jsi_Number nhow;
    rhowmany = n-istart;
    if (howmany && Jsi_GetNumberFromValue(interp, howmany, &nhow) == JSI_OK) {
        rhowmany = (int)nhow;
        if (rhowmany >= (n-istart))
            rhowmany = n-istart;
        if (rhowmany < 0)
            rhowmany = (n-istart);
        if (rhowmany<0)
            goto bail;
    }
    
    if (curlen < 0) {
        Jsi_ObjSetLength(interp, obj, 0);
    }
    Jsi_ObjListifyArray(interp, obj);
   
    Jsi_ObjArraySizer(interp, nobj, rhowmany);

    /* Move elements to return object. */
    int i, j, m;
    for (m=0, j = 0, i = istart; m<rhowmany && m<curlen; m++, i++, j++)
    {
        if (!obj->arr[i]) continue;
        nobj->arr[m] = obj->arr[i];
        obj->arr[i] = NULL;
    }
    Jsi_ObjSetLength(interp, nobj, m);
    
    /* Shift remaining down. */
    for (; rhowmany && i<curlen; i++)
    {
        obj->arr[i-rhowmany] = obj->arr[i];
        obj->arr[i] = NULL;
    }
    curlen -= j;
    /* Add elements. */
    newlen = curlen + argc - (argc>=2?2:1);
    if (Jsi_ObjArraySizer(interp, obj, newlen+3) <= 0) {
        Jsi_LogError("too long");
        Jsi_ValueMakeUndef(interp, ret);
        return JSI_ERROR;
    }
    if (ilen>0) {
        for (i = curlen-1; i>=istart; i--) {
            obj->arr[i+ilen] = obj->arr[i];
            obj->arr[i] = NULL;
        }
        for (m=istart, i = 2; i<argc; m++,i++) {
            va = Jsi_ValueArrayIndex(interp, args, i);
            if (!va) continue;
            obj->arr[m] = NULL;
            Jsi_ValueDup2(interp, obj->arr+m, va);
        }
    }
    Jsi_ObjSetLength(interp, obj, newlen);
bail:    
    return JSI_OK;
     
            
bail2:
    Jsi_ValueMakeNull(interp, ret);
    return JSI_OK;
}

/* ================= driver ================= */

/* mk_num: build a heap Jsi_Value holding a JS number -- used for the splice "start"/"howmany"
 * args, this array's real elements, and the forged tree "length" value. Not a jsish API (no
 * such helper is needed at this granularity); a plain, obviously-correct constructor. */
static Jsi_Value *mk_num(double v) {
    Jsi_Value *p = (Jsi_Value*)calloc(1, sizeof(Jsi_Value));
    p->vt = JSI_VT_NUMBER;
    p->d.num = v;
    return p;
}

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

    unsigned char b0 = got > 0 ? data[0] : 0;
    unsigned char b1 = got > 1 ? data[1] : 0;
    unsigned char b2 = got > 2 ? data[2] : 0;
    unsigned char b3 = got > 3 ? data[3] : 0;
    unsigned char b4 = got > 4 ? data[4] : 0;
    unsigned char b5 = got > 5 ? data[5] : 0;
    free(data);

    int trigger = b0 & 1;                                  /* forged .length outruns arrCnt */
    int safe_small_tree = (!trigger) && (b0 & 2);           /* SAFE variant: tree present, but
                                                                 length <= phys_n (in-bounds) */
    uint32_t phys_n = 2u + (uint32_t)(b1 % 6);              /* real physical elements: 2..7 */
    uint32_t rand16 = (uint32_t)b2 | ((uint32_t)b3 << 8);
    uint32_t fake_len = phys_n + 8u + (rand16 % 2000u);     /* always phys_n+8 .. phys_n+2007 */
    uint32_t small_len = (phys_n > 0) ? (uint32_t)(b5 % (phys_n + 1)) : 0u;  /* 0..phys_n */
    uint32_t istart_arg = (uint32_t)(b4 % (phys_n + 1));    /* 0..phys_n, always in [0,n] */

    Jsi_Interp *interp = (Jsi_Interp*)calloc(1, 64);   /* opaque handle; never dereferenced */

    /* ---- build `_this`: the array Jsi_Obj jsi_ArraySpliceCmd operates on ---- */
    Jsi_Obj thisobj; memset(&thisobj, 0, sizeof(thisobj));
    thisobj.ot = JSI_OT_OBJECT;
    thisobj.isarrlist = 1;
    thisobj.refcnt = 1;
    thisobj.arrCnt = phys_n;
    thisobj.arrMaxSize = phys_n;                       /* EXACT physical size: index phys_n is
                                                            the very first byte past the real
                                                            heap allocation -> ASAN redzone. */
    thisobj.arr = (Jsi_Value**)malloc((phys_n ? phys_n : 1) * sizeof(Jsi_Value*));
    for (uint32_t k = 0; k < phys_n; k++)
        thisobj.arr[k] = mk_num((double)(k + 1));      /* real, valid, non-NULL elements */

    Jsi_Tree faketree; memset(&faketree, 0, sizeof(faketree));
    if (trigger) {
        faketree.numEntries = 1;
        faketree.key = "length";
        faketree.value = mk_num((double)fake_len);      /* <-- the forged, oversized length */
        thisobj.tree = &faketree;
    } else if (safe_small_tree) {
        faketree.numEntries = 1;
        faketree.key = "length";
        faketree.value = mk_num((double)small_len);      /* in-bounds length, still via ->tree */
        thisobj.tree = &faketree;
    } else {
        thisobj.tree = NULL;                             /* Jsi_ObjGetLength falls to ->arrCnt */
    }

    Jsi_Value thisval; memset(&thisval, 0, sizeof(thisval));
    thisval.vt = JSI_VT_OBJECT;
    thisval.d.obj = &thisobj;

    /* ---- build `args`: a real 2-slot array (start, howmany) -- argc==2, so
     * ilen==argc-2==0 always (the Jsi_ValueDup2 insert path never runs). howmany is left
     * absent (NULL slot) so rhowmany defaults to n-istart, i.e. "delete through the end". ---- */
    Jsi_Obj argsobj; memset(&argsobj, 0, sizeof(argsobj));
    argsobj.ot = JSI_OT_OBJECT;
    argsobj.isarrlist = 1;
    argsobj.refcnt = 1;
    argsobj.arrCnt = 2;
    argsobj.arrMaxSize = 2;
    argsobj.arr = (Jsi_Value**)malloc(2 * sizeof(Jsi_Value*));
    argsobj.arr[0] = mk_num((double)istart_arg);   /* start */
    argsobj.arr[1] = NULL;                          /* howmany absent */

    Jsi_Value argsval; memset(&argsval, 0, sizeof(argsval));
    argsval.vt = JSI_VT_OBJECT;
    argsval.d.obj = &argsobj;

    /* ---- pre-allocate the result slot, matching the real interpreter's calling convention
     * (jsiEval.c always supplies a live `*ret` Jsi_Value* before invoking a Jsi_CmdProc). ---- */
    Jsi_Value retstore; memset(&retstore, 0, sizeof(retstore));
    retstore.vt = JSI_VT_UNDEF;
    Jsi_Value *retval = &retstore;

    /* volatile function pointer: forbid the compiler from inlining/proving-away the call
     * despite __attribute__((noinline)). */
    Jsi_RC (* volatile fn)(Jsi_Interp*, Jsi_Value*, Jsi_Value*, Jsi_Value**, Jsi_Func*) = jsi_ArraySpliceCmd;
    Jsi_RC rc = fn(interp, &argsval, &thisval, &retval, NULL);
    (void)rc;

    return 0;
}

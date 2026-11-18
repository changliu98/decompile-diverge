/*
 * Direct-call ASAN harness for CVE-2025-55158 (vim, CWE-415 Double Free)
 * Target: eval_tuple()  (src/tuple.c, vim commit 9ff1e598e8ee373b5623219ed38ad49470ec7938)
 *
 * Upstream fix (commit 9772025d24e939fd84b85748ce35c26874c05775):
 *
 *     if (rettv->v_type != VAR_UNKNOWN)
 *     {
 *         // Add the first item to the tuple from "rettv"
 *         if (tuple_append_tv(tuple, rettv) == FAIL)
 *             return FAIL;
 *   +     // The first item in "rettv" is added to the tuple.  Set the rettv
 *   +     // type to unknown, so that the caller doesn't free it.
 *   +     rettv->v_type = VAR_UNKNOWN;
 *     }
 *
 * tuple_append_tv() -> tuple_set_item() does a SHALLOW struct copy
 * ("*TUPLE_ITEM(tuple, idx) = *tv;", src/tuple.c) -- it aliases rettv's
 * heap-allocated value (e.g. a VAR_STRING's vval.v_string) into the tuple's
 * item 0 without transferring ownership away from "rettv" itself.  If
 * eval_tuple() later fails (any of the several "goto failret;" sites reached
 * AFTER that alias is created), it does
 *
 *     failret:
 *         if (evaluate)
 *             tuple_free(tuple);      // frees item 0 -> frees rettv's own string
 *         return FAIL;
 *
 * without ever touching "rettv" itself.  rettv is left with its original
 * v_type/vval pointing at memory tuple_free() has ALREADY freed.  Every real
 * eval_tuple() caller (see src/eval.c:eval9_nested_expr(), and the CVE
 * advisory's own "handle_import / ex_import" callers) then does its
 * standard on-FAIL cleanup -- clear_tv(rettv) -- exactly the same idiom
 * eval_tuple() itself uses two lines above for the check_typval_is_value()
 * early-FAIL case.  That second clear_tv() frees the same pointer again:
 * CWE-415 double free, official CVE description: "the clear_tv() function
 * may attempt to free memory that has already been deallocated".
 *
 * This harness reproduces that exactly: it plays the role of eval_tuple()'s
 * caller.  It builds "rettv" holding a real heap string (as if eval1() had
 * just evaluated the tuple's first element), calls the REAL, byte-for-byte
 * eval_tuple() with a crafted "arg" that forces the early vim9script
 * syntax-error "goto failret;" (so eval1() -- the recursive expression
 * parser -- is never actually invoked; see below), and then performs the
 * single, universal cleanup call (clear_tv(&rettv)) that every real caller
 * performs.  ASAN's double-free report's "freed by thread T0 here" trace
 * shows the FIRST (legitimate) free, whose stack runs through tuple_free()
 * <- eval_tuple() <- main(), i.e. through the target function itself.
 *
 * Everything on this trigger path (check_typval_is_value, tuple_alloc,
 * tuple_append_tv, tuple_free[_contents/_list], rettv_tuple_set, clear_tv,
 * the vartype_T/typval_T/tuple_T/garray_T layouts) is copied verbatim from
 * the vulnerable tree (src/tuple.c, src/typval.c, src/structs.h, src/vim.h,
 * src/macros.h, src/ascii.h, src/alloc.c, src/vim9type.c).  Two functions
 * eval_tuple() references are NEVER actually called by either corpus branch
 * below and exist only so the program links: eval1() (the trigger branch
 * takes the vim9script-whitespace "goto failret;" BEFORE the while-loop that
 * would call it) and skipwhite_and_linebreak()/skipwhite() (same -- dead on
 * both the "goto done;" and "goto failret;" branches this harness uses).
 * semsg() IS called (it formats the syntax-error message) but is pure
 * message-plumbing with no heap effect, so a no-op stub is
 * behavior-preserving for the bug under test.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ===================== src/vim.h / src/ascii.h ===================== */

typedef unsigned char char_u;                  /* src/vim.h */
typedef long          varnumber_T;              /* src/structs.h (LP64 path) */
typedef double         float_T;                 /* src/structs.h */

#define NUL   '\000'                             /* src/ascii.h */
#define OK    1                                  /* src/vim.h */
#define FAIL  0                                  /* src/vim.h */
#define TRUE  1
#define FALSE 0

/* src/macros.h */
#define VIM_ISWHITE(x)          ((x) == ' ' || (x) == '\t')
#define IS_WHITE_NL_OR_NUL(x)   ((x) == ' ' || (x) == '\t' || (x) == '\n' || (x) == NUL)
#define VIM_CLEAR(p)  do { vim_free(p); (p) = NULL; } while (0)

/* src/vim.h: gettext -- no-op, message text carries no memory-safety signal */
#define _(x) (x)

/* ===================== src/structs.h: vartype_T (verbatim) ===================== */

typedef enum
{
    VAR_UNKNOWN = 0,	// not set, any type or "void" allowed
    VAR_ANY,		// used for "any" type
    VAR_VOID,		// no value (function not returning anything)
    VAR_BOOL,		// "v_number" is used: VVAL_TRUE or VVAL_FALSE
    VAR_SPECIAL,	// "v_number" is used: VVAL_NULL or VVAL_NONE
    VAR_NUMBER,		// "v_number" is used
    VAR_FLOAT,		// "v_float" is used
    VAR_STRING,		// "v_string" is used
    VAR_BLOB,		// "v_blob" is used
    VAR_FUNC,		// "v_string" is function name
    VAR_PARTIAL,	// "v_partial" is used
    VAR_LIST,		// "v_list" is used
    VAR_DICT,		// "v_dict" is used
    VAR_JOB,		// "v_job" is used
    VAR_CHANNEL,	// "v_channel" is used
    VAR_INSTR,		// "v_instr" is used
    VAR_CLASS,		// "v_class" is used (also used for interface)
    VAR_OBJECT,		// "v_object" is used
    VAR_TYPEALIAS,	// "v_typealias" is used
    VAR_TUPLE		// "v_tuple" is used
} vartype_T;

/* Opaque -- only ever used as a pointer inside typval_T's union / tuple_T;
 * this harness never instantiates or dereferences these variant kinds
 * (VAR_STRING and VAR_TUPLE are the only ones that are ever live here), so
 * matching the real field TYPES (for a faithful typval_T layout) doesn't
 * require pulling in their real bodies. */
typedef struct list_S       list_T;
typedef struct dict_S       dict_T;
typedef struct partial_S    partial_T;
typedef struct blob_S       blob_T;
typedef struct instr_S      instr_T;
typedef struct class_S      class_T;
typedef struct object_S     object_T;
typedef struct typealias_S  typealias_T;
typedef struct type_S       type_T;

typedef struct tuplevar_S tuple_T;

/* src/structs.h: garray_T (verbatim) */
typedef struct growarray
{
    int	    ga_len;
    int	    ga_maxlen;
    int	    ga_itemsize;
    int	    ga_growsize;
    void    *ga_data;
} garray_T;

/* src/structs.h: struct typval_S (verbatim; FEAT_JOB_CHANNEL's v_job/v_channel
 * members dropped, matching the real #ifdef since this harness doesn't build
 * with that feature) */
typedef struct typval_S typval_T;
struct typval_S
{
    vartype_T	v_type;
    char	v_lock;	    // see below: VAR_LOCKED, VAR_FIXED
    union
    {
	varnumber_T	v_number;	// number value
	float_T		v_float;	// floating point number value
	char_u		*v_string;	// string value (can be NULL)
	list_T		*v_list;	// list value (can be NULL)
	dict_T		*v_dict;	// dict value (can be NULL)
	partial_T	*v_partial;	// closure: function with args
	blob_T		*v_blob;	// blob value (can be NULL)
	instr_T		*v_instr;	// instructions to execute
	class_T		*v_class;	// class value (can be NULL)
	object_T	*v_object;	// object value (can be NULL)
	typealias_T	*v_typealias;	// user-defined type name
	tuple_T		*v_tuple;	// tuple
    }		vval;
};

/* src/structs.h: struct tuplevar_S (verbatim) */
struct tuplevar_S
{
    garray_T	tv_items;	// tuple items
    type_T	*tv_type;	// current type, allocated by alloc_type()
    tuple_T	*tv_copytuple;	// copied tuple used by deepcopy()
    tuple_T	*tv_used_next;	// next tuple in used tuples list
    tuple_T	*tv_used_prev;	// previous tuple in used tuples list
    int		tv_refcount;	// reference count
    int		tv_copyID;	// ID used by deepcopy()
    char	tv_lock;	// zero, VAR_LOCKED, VAR_FIXED
};

/* src/macros.h (verbatim) */
#define TUPLE_LEN(t)	    (t->tv_items.ga_len)
#define TUPLE_ITEM(t, i) \
	    (((typval_T *)t->tv_items.ga_data) + i)

/* src/vim.h (verbatim) */
#define ALLOC_CLEAR_ONE(type)  (type *)alloc_clear(sizeof(type))

/* src/structs.h evalarg_T -- MINIMAL harness stand-in for the real ~12-field
 * struct.  eval_tuple() itself reads only "eval_flags"; every other real
 * field feeds getline/line-continuation machinery that only
 * skipwhite_and_linebreak()/eval1() touch, and both are dead code on every
 * input this harness's corpus generator produces (see file header). */
typedef struct
{
    int eval_flags;
} evalarg_T;

#define EVAL_EVALUATE 1   /* src/structs.h */

/* ===================== forward declarations ===================== */

static void clear_tv(typval_T *varp);
static void tuple_free(tuple_T *tuple);
static void tuple_unref(tuple_T *tuple);
int eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error);

/* src/globals.h: EXTERN int in_free_unref_items INIT(= FALSE); (verbatim
 * value; declared up front since tuple_free() below reads it) */
int in_free_unref_items = FALSE;

/* ===================== src/alloc.c (minimal: drops lalloc()'s OOM-retry
 * loop, which never triggers at these allocation sizes) ===================== */

static void *alloc(size_t size) { return malloc(size); }
static void *alloc_clear(size_t size) { return calloc(1, size); }
static void *vim_realloc(void *ptr, size_t size) { return realloc(ptr, size); }
static void vim_free(void *x) { if (x != NULL) free(x); }

/* src/alloc.c: ga_init / ga_init2 / ga_grow_inner / ga_grow / ga_clear (verbatim) */
    static void
ga_init(garray_T *gap)
{
    gap->ga_data = NULL;
    gap->ga_maxlen = 0;
    gap->ga_len = 0;
}

    static void
ga_init2(garray_T *gap, size_t itemsize, int growsize)
{
    ga_init(gap);
    gap->ga_itemsize = (int)itemsize;
    gap->ga_growsize = growsize;
}

    static int
ga_grow_inner(garray_T *gap, int n)
{
    size_t	old_len;
    size_t	new_len;
    char_u	*pp;

    if (n < gap->ga_growsize)
	n = gap->ga_growsize;
    if (n < gap->ga_len / 2)
	n = gap->ga_len / 2;

    new_len = (size_t)gap->ga_itemsize * (gap->ga_len + n);
    pp = vim_realloc(gap->ga_data, new_len);
    if (pp == NULL)
	return FAIL;
    old_len = (size_t)gap->ga_itemsize * gap->ga_maxlen;
    memset(pp + old_len, 0, new_len - old_len);
    gap->ga_maxlen = gap->ga_len + n;
    gap->ga_data = pp;
    return OK;
}

    static int
ga_grow(garray_T *gap, int n)
{
    if (gap->ga_maxlen - gap->ga_len < n)
	return ga_grow_inner(gap, n);
    return OK;
}

    static void
ga_clear(garray_T *gap)
{
    vim_free(gap->ga_data);
    ga_init(gap);
}

/* src/vim9type.c: free_type() -- minimal.  On every path this harness
 * exercises, tuple->tv_type is NULL (tuple_alloc() zero-inits it via
 * ALLOC_CLEAR_ONE and nothing here ever calls alloc_type()) -- exactly the
 * case the real function no-ops on ("if (type == NULL ...) return;"). */
static void free_type(type_T *type) { (void)type; }

/* src/vim9type.c: check_typval_is_value() -- minimal.  The real function
 * additionally formats an error message for VAR_CLASS/VAR_TYPEALIAS using
 * class_T fields this harness doesn't model; every typval this harness ever
 * builds is VAR_STRING, VAR_UNKNOWN or VAR_TUPLE, for which both versions
 * return OK identically. */
    static int
check_typval_is_value(typval_T *tv)
{
    if (tv == NULL)
	return OK;
    if (tv->v_type == VAR_CLASS || tv->v_type == VAR_TYPEALIAS)
	return FAIL;
    return OK;
}

/* Link-satisfying no-op stubs for clear_tv()'s switch arms this harness never
 * actually exercises (v_type here is always VAR_STRING or VAR_TUPLE). */
static void func_unref(char_u *name) { (void)name; }
static void partial_unref(partial_T *pt) { (void)pt; }
static void blob_unref(blob_T *b) { (void)b; }
static void list_unref(list_T *l) { (void)l; }
static void dict_unref(dict_T *d) { (void)d; }
static void class_unref(class_T *cl) { (void)cl; }
static void object_unref(object_T *obj) { (void)obj; }
static void typealias_unref(typealias_T *ta) { (void)ta; }

/* src/typval.c: clear_tv() -- verbatim (the FEAT_JOB_CHANNEL VAR_JOB/
 * VAR_CHANNEL bodies are dropped, matching the real #ifdef since this
 * harness doesn't build with that feature -- the case labels stay so the
 * switch is exhaustive exactly as in the original).  This is the function
 * the CVE advisory names as the double-free site. */
    static void
clear_tv(typval_T *varp)
{
    if (varp == NULL)
	return;

    switch (varp->v_type)
    {
	case VAR_FUNC:
	    func_unref(varp->vval.v_string);
	    // FALLTHROUGH
	case VAR_STRING:
	    VIM_CLEAR(varp->vval.v_string);
	    break;
	case VAR_PARTIAL:
	    partial_unref(varp->vval.v_partial);
	    varp->vval.v_partial = NULL;
	    break;
	case VAR_BLOB:
	    blob_unref(varp->vval.v_blob);
	    varp->vval.v_blob = NULL;
	    break;
	case VAR_LIST:
	    list_unref(varp->vval.v_list);
	    varp->vval.v_list = NULL;
	    break;
	case VAR_TUPLE:
	    tuple_unref(varp->vval.v_tuple);
	    varp->vval.v_tuple = NULL;
	    break;
	case VAR_DICT:
	    dict_unref(varp->vval.v_dict);
	    varp->vval.v_dict = NULL;
	    break;
	case VAR_NUMBER:
	case VAR_BOOL:
	case VAR_SPECIAL:
	    varp->vval.v_number = 0;
	    break;
	case VAR_FLOAT:
	    varp->vval.v_float = 0.0;
	    break;
	case VAR_JOB:
	    break;
	case VAR_CHANNEL:
	    break;
	case VAR_INSTR:
	    VIM_CLEAR(varp->vval.v_instr);
	    break;
	case VAR_CLASS:
	    class_unref(varp->vval.v_class);
	    varp->vval.v_class = NULL;
	    break;
	case VAR_OBJECT:
	    object_unref(varp->vval.v_object);
	    varp->vval.v_object = NULL;
	    break;
	case VAR_TYPEALIAS:
	    typealias_unref(varp->vval.v_typealias);
	    varp->vval.v_typealias = NULL;
	    break;
	case VAR_UNKNOWN:
	case VAR_ANY:
	case VAR_VOID:
	    break;
    }
    varp->v_lock = 0;
}

/* ===================== src/tuple.c (verbatim subset) =====================
 * Only the functions eval_tuple()'s own body and its direct call chain use;
 * tuple_alloc_with_items/tuple_concat/tuple_slice/tuple_copy/... are not
 * reachable from eval_tuple() and are omitted. */

static tuple_T *first_tuple = NULL;	// list of all tuples, for GC bookkeeping

    static void
tuple_init(tuple_T *tuple)
{
    // Prepend the tuple to the list of tuples for garbage collection.
    if (first_tuple != NULL)
	first_tuple->tv_used_prev = tuple;
    tuple->tv_used_prev = NULL;
    tuple->tv_used_next = first_tuple;
    first_tuple = tuple;

    ga_init2(&tuple->tv_items, sizeof(typval_T), 20);
}

/*
 * Allocate an empty header for a tuple.
 * Caller should take care of the reference count.
 */
    tuple_T *
tuple_alloc(void)
{
    tuple_T  *tuple;

    tuple = ALLOC_CLEAR_ONE(tuple_T);
    if (tuple != NULL)
	tuple_init(tuple);
    return tuple;
}

/*
 * Set item "idx" for a tuple previously allocated with
 * tuple_alloc_with_items().
 * The contents of "tv" is copied into the tuple item.
 * Each item must be set exactly once.
 */
    void
tuple_set_item(tuple_T *tuple, int idx, typval_T *tv)
{
    *TUPLE_ITEM(tuple, idx) = *tv;
    tuple->tv_items.ga_len++;
}

    int
tuple_append_tv(tuple_T *tuple, typval_T *tv)
{
    if (ga_grow(&tuple->tv_items, 1) == FAIL)
	return FAIL;

    tuple_set_item(tuple, TUPLE_LEN(tuple), tv);

    return OK;
}

/*
 * Free a tuple, including all non-container items it points to.
 * Ignores the reference count.
 */
    static void
tuple_free_contents(tuple_T *tuple)
{
    for (int i = 0; i < TUPLE_LEN(tuple); i++)
	clear_tv(TUPLE_ITEM(tuple, i));

    ga_clear(&tuple->tv_items);
}

    static void
tuple_free_list(tuple_T  *tuple)
{
    // Remove the tuple from the list of tuples for garbage collection.
    if (tuple->tv_used_prev == NULL)
	first_tuple = tuple->tv_used_next;
    else
	tuple->tv_used_prev->tv_used_next = tuple->tv_used_next;
    if (tuple->tv_used_next != NULL)
	tuple->tv_used_next->tv_used_prev = tuple->tv_used_prev;

    free_type(tuple->tv_type);
    vim_free(tuple);
}

    void
tuple_free(tuple_T *tuple)
{
    if (in_free_unref_items)
	return;

    tuple_free_contents(tuple);
    tuple_free_list(tuple);
}

    void
tuple_unref(tuple_T *tuple)
{
    if (tuple != NULL && --tuple->tv_refcount <= 0)
	tuple_free(tuple);
}

/*
 * Set a tuple as the return value.  Increments the reference count.
 */
    void
rettv_tuple_set(typval_T *rettv, tuple_T *tuple)
{
    rettv->v_type = VAR_TUPLE;
    rettv->vval.v_tuple = tuple;
    if (tuple != NULL)
	++tuple->tv_refcount;
}

/* ===================== incidental plumbing (never touches heap state
 * shared with the bug under test) ===================== */

/* src/charset.c: skipwhite() -- verbatim (trivial, and technically dead code
 * on both corpus branches below, but harmless and cheap to keep faithful). */
    char_u *
skipwhite(char_u *q)
{
    char_u	*p = q;

    while (VIM_ISWHITE(*p))
	++p;
    return p;
}

/* src/eval.c: skipwhite_and_linebreak() -- minimal.  NEVER reached: both
 * corpus branches below take a "goto done;"/"goto failret;" inside
 * eval_tuple() strictly BEFORE the real function's one call site
 * ("*arg = skipwhite_and_linebreak(*arg + 1, evalarg);") is reached.  Body
 * kept faithful for the no-line-continuation case anyway (this harness's
 * crafted "arg" strings never contain '\n'), for which it is behaviorally
 * identical to the real multi-line-aware version. */
    char_u *
skipwhite_and_linebreak(char_u *arg, evalarg_T *evalarg)
{
    (void)evalarg;
    return skipwhite(arg);
}

/* src/eval.c: eval1() -- the recursive-descent expression evaluator.  NEVER
 * reached: eval_tuple()'s one call site for it is inside the while-loop that
 * parses tuple elements AFTER the first, and both corpus branches below
 * fail/succeed strictly before that loop is ever entered (see file header).
 * Present only so the program links; the body is unreachable dead code for
 * every input this harness's corpus generator produces. */
    int
eval1(char_u **arg, typval_T *rettv, evalarg_T *evalarg)
{
    (void)arg;
    (void)evalarg;
    rettv->v_type = VAR_UNKNOWN;
    return FAIL;
}

/* src/message.c-family: semsg() -- minimal.  The real implementation
 * formats and queues a translated error string for later display; it has no
 * effect on heap state shared with typval_T/tuple_T, so a no-op stub is
 * behavior-preserving for the double-free under test. */
    int
semsg(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    va_end(ap);
    return TRUE;
}

/* src/script.c-family: in_vim9script() -- minimal.  The real implementation
 * reads global script-context state (current_sctx) that tracks which script
 * is currently being sourced.  This harness calls eval_tuple() as if from a
 * vim9script context, matching the CVE's actual real-world trigger (a
 * vim9script ":import ... as (...)" -- see the upstream regression test
 * Test_import_invalid_tuple() added by the fix commit). */
    int
in_vim9script(void)
{
    return TRUE;
}

/* src/errors.h message text (verbatim strings; semsg() above ignores its
 * arguments entirely, so only the identifier needs to resolve). */
static const char e_white_space_required_after_str_str[] =
    "E1069: White space required after '%s': %s";
static const char e_missing_comma_in_tuple_str[] =
    "E1527: Missing comma in Tuple: %s";
static const char e_no_white_space_allowed_before_str_str[] =
    "E1068: No white space allowed before '%s': %s";
static const char e_missing_end_of_tuple_rsp_str[] =
    "E1526: Missing end of Tuple ')': %s";

/* ===================== src/tuple.c: eval_tuple() =====================
 * VERBATIM, byte-for-byte from data_cve/cve_1dee992a/target/original_function.c
 * (the UNPATCHED, vulnerable version -- vul_commit
 * 9ff1e598e8ee373b5623219ed38ad49470ec7938).  Not one character changed. */

/*
 * Allocate a variable for a tuple and fill it from "*arg".
 * "*arg" points to the "," after the first element.
 * "rettv" contains the first element.
 * Returns OK or FAIL.
 */
int
eval_tuple(char_u **arg, typval_T *rettv, evalarg_T *evalarg, int do_error)
{
    int		evaluate = evalarg == NULL ? FALSE
					 : evalarg->eval_flags & EVAL_EVALUATE;
    tuple_T	*tuple = NULL;
    typval_T	tv;
    int		vim9script = in_vim9script();
    int		had_comma;

    if (check_typval_is_value(rettv) == FAIL)
    {
	// the first item is not a valid value type
	clear_tv(rettv);
	return FAIL;
    }

    if (evaluate)
    {
	tuple = tuple_alloc();
	if (tuple == NULL)
	    return FAIL;

	if (rettv->v_type != VAR_UNKNOWN)
	{
	    // Add the first item to the tuple from "rettv"
	    if (tuple_append_tv(tuple, rettv) == FAIL)
		return FAIL;
	}
    }

    if (**arg == ')')
	// empty tuple
	goto done;

    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
    {
	semsg(_(e_white_space_required_after_str_str), ",", *arg);
	goto failret;
    }

    *arg = skipwhite_and_linebreak(*arg + 1, evalarg);
    while (**arg != ')' && **arg != NUL)
    {
	if (eval1(arg, &tv, evalarg) == FAIL)	// recursive!
	    goto failret;
	if (check_typval_is_value(&tv) == FAIL)
	{
	    if (evaluate)
		clear_tv(&tv);
	    goto failret;
	}

	if (evaluate)
	{
	    if (tuple_append_tv(tuple, &tv) == FAIL)
	    {
		clear_tv(&tv);
		goto failret;
	    }
	}

	if (!vim9script)
	    *arg = skipwhite(*arg);

	// the comma must come after the value
	had_comma = **arg == ',';
	if (had_comma)
	{
	    if (vim9script && !IS_WHITE_NL_OR_NUL((*arg)[1]) && (*arg)[1] != ')')
	    {
		semsg(_(e_white_space_required_after_str_str), ",", *arg);
		goto failret;
	    }
	    *arg = skipwhite(*arg + 1);
	}

	// The ")" can be on the next line.  But a double quoted string may
	// follow, not a comment.
	*arg = skipwhite_and_linebreak(*arg, evalarg);
	if (**arg == ')')
	    break;

	if (!had_comma)
	{
	    if (do_error)
	    {
		if (**arg == ',')
		    semsg(_(e_no_white_space_allowed_before_str_str),
								    ",", *arg);
		else
		    semsg(_(e_missing_comma_in_tuple_str), *arg);
	    }
	    goto failret;
	}
    }

    if (**arg != ')')
    {
	if (do_error)
	    semsg(_(e_missing_end_of_tuple_rsp_str), *arg);
failret:
	if (evaluate)
	    tuple_free(tuple);
	return FAIL;
    }

done:
    *arg += 1;
    if (evaluate)
	rettv_tuple_set(rettv, tuple);

    return OK;
}

/* ===================== harness driver ===================== */

int
main(int argc, char **argv)
{
    if (argc < 2)
    {
	fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
	return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL)
    {
	fprintf(stderr, "cannot open %s\n", argv[1]);
	return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    if (fsize < 0)
	fsize = 0;
    fseek(f, 0, SEEK_SET);

    /* Read the whole PoC/corpus file into a HEAP buffer (ASAN-guarded). */
    unsigned char *buf = (unsigned char *)malloc((size_t)fsize + 1);
    if (buf == NULL)
    {
	fclose(f);
	return 1;
    }
    size_t nread = (fsize > 0) ? fread(buf, 1, (size_t)fsize, f) : 0;
    fclose(f);
    buf[nread] = '\0';

    /* byte[0] (parity) selects the differential branch:
     *   odd  -> TRIGGER: force eval_tuple()'s vim9script "goto failret;",
     *           which frees the aliased first-item string via tuple_free();
     *           the subsequent clear_tv(&rettv) is then the fatal 2nd free.
     *   even (or empty file) -> SAFE: force eval_tuple()'s "empty tuple"
     *           "goto done;", where rettv_tuple_set() cleanly overwrites
     *           rettv to own the tuple -- clear_tv(&rettv) is then a single,
     *           ordinary, correct free.
     * The remaining bytes become the tuple's first-item string content --
     * the exact heap allocation eval_tuple() aliases into the tuple and
     * that, on the TRIGGER branch, gets freed twice. */
    int trigger = (nread > 0) && (buf[0] & 1);

    size_t slen = (nread > 0) ? nread - 1 : 0;
    char_u *first_item = (char_u *)malloc(slen + 1);
    if (first_item == NULL)
    {
	free(buf);
	return 1;
    }
    if (slen > 0)
	memcpy(first_item, buf + 1, slen);
    first_item[slen] = '\0';

    /* byte after the first-item content (if any usable one was supplied)
     * becomes the vim9script "character right after the comma" that must be
     * non-whitespace/non-NUL/non-')' to take the TRIGGER branch; fall back
     * to a fixed safe choice otherwise so the corpus author's intended
     * branch is always actually taken. */
    char_u xbyte = 'Z';
    if (slen > 0)
    {
	unsigned char c = first_item[0];
	if (c != ' ' && c != '\t' && c != '\n' && c != '\0' && c != ')')
	    xbyte = (char_u)c;
    }
    free(buf);

    /* Build "rettv" exactly as eval_tuple()'s real caller
     * (eval9_nested_expr(), src/eval.c) would have it immediately after
     * eval1() evaluated the tuple's first element into a VAR_STRING. */
    typval_T rettv;
    rettv.v_type = VAR_STRING;
    rettv.v_lock = 0;
    rettv.vval.v_string = first_item;

    evalarg_T evalarg;
    evalarg.eval_flags = EVAL_EVALUATE;

    /* "*arg" must point at the ',' after the first element (eval_tuple()'s
     * own documented precondition); heap-allocate it like every other
     * attacker-influenced buffer here. */
    char_u *arg_buf;
    if (trigger)
    {
	arg_buf = (char_u *)malloc(3);
	arg_buf[0] = ',';
	arg_buf[1] = xbyte;
	arg_buf[2] = NUL;
    }
    else
    {
	arg_buf = (char_u *)malloc(2);
	arg_buf[0] = ')';
	arg_buf[1] = NUL;
    }
    char_u *arg = arg_buf;

    /* ---- the call under test ---- */
    int ret = eval_tuple(&arg, &rettv, &evalarg, TRUE);

    /* Exactly what every real eval_tuple() caller does with its rettv once
     * the call returns: a one-shot cleanup of whatever eval_tuple() left
     * behind (see eval9_nested_expr()'s own clear_tv(rettv) calls on its
     * sibling failure branches, and eval_tuple()'s own clear_tv(rettv) two
     * lines into its body on the check_typval_is_value() early-FAIL path --
     * the exact same idiom).  On the TRIGGER branch this is the unpatched
     * bug's fatal second free (CVE-2025-55158, CWE-415); on the SAFE branch
     * rettv was cleanly overwritten by rettv_tuple_set() to solely own the
     * tuple, so this is a single ordinary free. */
    clear_tv(&rettv);

    free(arg_buf);

    printf("done trigger=%d ret=%d\n", trigger, ret);
    return 0;
}

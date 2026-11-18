/* Direct-call crash harness for njs njs_vmcode_array (CVE-2022-28049, CWE-476,
 * src/njs_vmcode.c).
 *
 * Root cause (fix commit f65981b0b8fcf02d69a40bc934803c25c9f607ab, "Fixed allocation
 * of large array literals."):
 *
 *   array = njs_array_alloc(vm, 0, code->length, NJS_ARRAY_SPARE);
 *   if (njs_fast_path(array != NULL)) {
 *       if (code->ctor) {
 *           value = array->start;         <-- may be NULL
 *           length = array->length;       <-- may be 0
 *           do {
 *               njs_set_invalid(value);   <-- CRASH: deref of NULL, do-while
 *               value++;                     runs unconditionally >=1 time
 *               length--;
 *           } while (length != 0);
 *       ...
 *
 * njs_array_alloc() (src/njs_array.c) allocates a *slow* (non-flat) array --
 * array->data == array->start == NULL, array->object.fast_array == 0,
 * array->length == 0 -- whenever `flat` is false (the njs_vmcode_array() call
 * site always passes flat=0) AND `length + NJS_ARRAY_SPARE(8) >
 * NJS_ARRAY_LARGE_OBJECT_LENGTH (32768)`. njs_vmcode_array()'s ctor branch
 * unconditionally assumes a *fast* array (array->start non-NULL, array->length
 * == the requested element count) and dereferences array->start in a do-while
 * that always executes at least once -- so a `[,]`-style elision array literal
 * (code->ctor == 1, e.g. `[,,,...]`) with code->length > 32760 makes
 * njs_array_alloc() return a slow array (start == NULL) and njs_vmcode_array()
 * immediately null-derefs it. The fix (not present in this vulnerable
 * revision) wraps the do-while in `if (array->object.fast_array) { ... }`.
 *
 * njs_vmcode_array() itself (target/original_function.c) is embedded
 * VERBATIM below, byte-for-byte, unchanged.
 *
 * njs_array_alloc() is NOT the fault site (njs_vmcode_array's own do-while
 * is), but its return value's shape (object.fast_array / start / length) is
 * exactly what attacker-controlled `code->length` drives through the real
 * bug condition, so a no-op stub would not exercise the real vulnerability.
 * The stand-in below reproduces njs_array_alloc()'s control flow and every
 * field assignment that njs_vmcode_array() (or our corpus) can observe
 * VERBATIM -- same overflow check, same `size = length + spare`, same
 * `flat || size <= NJS_ARRAY_LARGE_OBJECT_LENGTH` branch condition (the
 * exact real constant, src/njs_array.h), same fast_array/size/length/start
 * assignments -- and only replaces the VM-internal allocator plumbing that
 * this standalone harness cannot pull in and that does not affect whether
 * the bug fires: njs_mp_alloc/njs_mp_align (memory-pool allocator) -> plain
 * malloc(); njs_lvlhsh_init(&object.hash) -> zero-init (the real function is
 * itself just `lp->slot = NULL`, so this is not even a simplification);
 * vm->shared->array_instance_hash / vm->prototypes[...] linkage -> zeroed
 * (never read before the crash, and never read by our corpus at all); the
 * slow-array path's njs_array_length_redefine(vm, &value, length) call
 * (property-hash bookkeeping for the object's exotic "length" property,
 * unrelated to array->start/array->length) -> omitted, its only failure mode
 * is OOM which we do not simulate, so it is treated as always succeeding
 * (matching the real function's non-OOM behaviour of returning the array).
 *
 * All type/struct/macro/constant definitions below are the REAL names and
 * layouts from src/njs_vmcode.h, src/njs_value.h, src/njs_array.h,
 * src/njs_lvlhsh.h, src/njs_clang.h, src/njs_types.h, src/njs.h,
 * src/njs_vm.h. njs_vm_t is trimmed to just the one field njs_vmcode_array()
 * touches (`retval`, kept as the REAL first member per the real struct's own
 * "njs_vm_t must be aligned to njs_value_t due to scratch value" comment);
 * every other real njs_vm_s field (mem pool, hashes, frames, prototypes,
 * ...) is VM-internal state this direct-call harness has no use for and
 * njs_vmcode_array() never touches.
 *
 * main() reads argv[1] into a HEAP buffer sized to EXACTLY
 * sizeof(njs_vmcode_array_t) (malloc'd, zero-initialised, then fread() fills
 * in up to that many attacker bytes -- short files leave the tail
 * zero-filled instead of over-reading) and passes it directly as `pc`, i.e.
 * the raw bytes of the input file ARE the njs_vmcode_array_t bytecode
 * record, exactly mirroring how the real interpreter reads a heap-allocated
 * bytecode array through `pc`. Only two fields of that record actually
 * matter pre-crash (code->length, code->ctor); the corpus generator (see
 * gen_corpus.py) writes them at their real, compiler-computed
 * offsetof()s so the file format is exact regardless of struct padding.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* ---- njs_types.h / njs.h / njs_vmcode.h base typedefs (verbatim) ---- */
typedef unsigned char        u_char;
typedef intptr_t             njs_int_t;
typedef uintptr_t            njs_uint_t;
typedef njs_uint_t           njs_bool_t;
typedef uintptr_t            njs_index_t;
typedef intptr_t             njs_jump_off_t;
typedef uint8_t              njs_vmcode_operation_t;

#define NJS_ERROR   (-1)
#define NJS_OK       0

/* njs_clang.h (verbatim, NJS_HAVE_BUILTIN_EXPECT branch -- true for gcc/clang) */
#define njs_expect(c, x)   __builtin_expect((long) (x), (c))
#define njs_fast_path(x)   njs_expect(1, x)
#define njs_slow_path(x)   njs_expect(0, x)

/* njs_vmcode.h (verbatim) */
typedef struct {
    njs_vmcode_operation_t     operation;
    uint8_t                    operands;   /* 2 bits */
} njs_vmcode_t;

typedef struct {
    njs_vmcode_t               code;
    njs_index_t                retval;
    uintptr_t                  length;
    uint8_t                    ctor;       /* 1 bit  */
} njs_vmcode_array_t;

/* ---- njs_value.h (verbatim types njs_vmcode_array() needs) ---- */
typedef enum {
    NJS_NULL,
    NJS_UNDEFINED,
    NJS_BOOLEAN,
    NJS_NUMBER,
    NJS_SYMBOL,
    NJS_STRING,
    NJS_DATA,
    NJS_INVALID,

    NJS_OBJECT                = 0x10,
    NJS_ARRAY,
    NJS_FUNCTION,
    NJS_REGEXP,
    NJS_DATE,
    NJS_TYPED_ARRAY,
    NJS_PROMISE,
    NJS_OBJECT_VALUE,
    NJS_ARRAY_BUFFER,
    NJS_DATA_VIEW,
    NJS_VALUE_TYPE_MAX
} njs_value_type_t;

typedef struct njs_string_s           njs_string_t;
typedef struct njs_object_s           njs_object_t;
typedef struct njs_object_value_s     njs_object_value_t;
typedef struct njs_function_lambda_s  njs_function_lambda_t;
typedef struct njs_array_s            njs_array_t;
typedef struct njs_array_buffer_s     njs_array_buffer_t;
typedef struct njs_typed_array_s      njs_typed_array_t;
typedef struct njs_typed_array_s      njs_data_view_t;
typedef struct njs_regexp_s           njs_regexp_t;
typedef struct njs_date_s             njs_date_t;
typedef struct njs_object_value_s     njs_promise_t;
typedef struct njs_property_next_s    njs_property_next_t;
typedef struct njs_function_s         njs_function_t;
typedef struct njs_exotic_slots_s     njs_exotic_slots_t;
typedef union  njs_value_s            njs_value_t;
typedef njs_int_t                     (*njs_prop_handler_t)(void);

/* njs_lvlhsh.h (verbatim) */
typedef struct {
    void                      *slot;
} njs_lvlhsh_t;

/* njs_value.h: struct njs_object_s (verbatim, full) */
struct njs_object_s {
    /* A private hash of njs_object_prop_t. */
    njs_lvlhsh_t                      hash;

    /* A shared hash of njs_object_prop_t. */
    njs_lvlhsh_t                      shared_hash;

    njs_object_t                      *__proto__;
    njs_exotic_slots_t                *slots;

    /* The type is used in constructor prototypes. */
    njs_value_type_t                  type:8;
    uint8_t                           shared;     /* 1 bit */

    uint8_t                           extensible:1;
    uint8_t                           error_data:1;
    uint8_t                           fast_array:1;
};

/* njs_value.h: union njs_value_s (verbatim, full -- NJS_STRING_SHORT from
 * the same header) */
#define NJS_STRING_SHORT              14
#define NJS_STRING_LONG                15

union njs_value_s {
    struct {
        njs_value_type_t              type:8;  /* 6 bits */
        uint8_t                       truth;

        uint16_t                      magic16;
        uint32_t                      magic32;

        union {
            double                    number;
            njs_object_t              *object;
            njs_array_t               *array;
            njs_array_buffer_t        *array_buffer;
            njs_typed_array_t         *typed_array;
            njs_data_view_t           *data_view;
            njs_object_value_t        *object_value;
            njs_function_t            *function;
            njs_function_lambda_t     *lambda;
            njs_regexp_t              *regexp;
            njs_date_t                *date;
            njs_promise_t             *promise;
            njs_prop_handler_t        prop_handler;
            njs_value_t               *value;
            njs_property_next_t       *next;
            void                      *data;
        } u;
    } data;

    struct {
        njs_value_type_t              type:8;  /* 6 bits */

        uint8_t                       size:4;
        uint8_t                       length:4;

        u_char                        start[NJS_STRING_SHORT];
    } short_string;

    struct {
        njs_value_type_t              type:8;  /* 6 bits */
        uint8_t                       truth;

        uint8_t                       external;
        uint8_t                       _spare;

        uint32_t                      size;
        njs_string_t                  *data;
    } long_string;

    njs_value_type_t                  type:8;  /* 6 bits */
};

/* njs_value.h: struct njs_array_s (verbatim, full) */
struct njs_array_s {
    njs_object_t                      object;
    uint32_t                          size;
    uint32_t                          length;
    njs_value_t                       *start;
    njs_value_t                       *data;
};

/* njs_value.h: njs_set_invalid() / njs_set_array() (verbatim) */
#define njs_set_invalid(value)                                                \
    (value)->type = NJS_INVALID

static inline void
njs_set_array(njs_value_t *value, njs_array_t *array)
{
    value->data.u.array = array;
    value->type = NJS_ARRAY;
    value->data.truth = 1;
}

/* njs_array.h (verbatim constants) */
#define NJS_ARRAY_SPARE                8
#define NJS_ARRAY_LARGE_OBJECT_LENGTH  (32768)

/* njs_vm.h: njs_vm_t, trimmed to the one field njs_vmcode_array() touches
 * (see file header). `retval` kept as the REAL first member, REAL name,
 * REAL type -- matches the real struct's own layout requirement. */
typedef struct njs_vm_s njs_vm_t;

struct njs_vm_s {
    /* njs_vm_t must be aligned to njs_value_t due to scratch value. */
    njs_value_t               retval;
};

/* ---- njs_array.c: njs_array_alloc(), control-flow-verbatim stand-in for
 * the VM-internal allocator plumbing this standalone harness cannot pull
 * in (see file header for exactly what is preserved vs. replaced). ---- */
static njs_array_t *
njs_array_alloc(njs_vm_t *vm, njs_bool_t flat, uint64_t length, uint32_t spare)
{
    uint64_t     size;
    njs_array_t  *array;

    (void) vm;

    if (njs_slow_path(length > UINT32_MAX)) {
        /* overflow: real code calls njs_range_error(vm, ...) then returns NULL */
        return NULL;
    }

    array = malloc(sizeof(njs_array_t));
    if (njs_slow_path(array == NULL)) {
        /* memory_error: real code calls njs_memory_error(vm) then returns NULL */
        return NULL;
    }

    size = length + spare;

    if (flat || size <= NJS_ARRAY_LARGE_OBJECT_LENGTH) {
        array->data = malloc(size * sizeof(njs_value_t));
        if (njs_slow_path(array->data == NULL)) {
            free(array);
            return NULL;
        }

    } else {
        array->data = NULL;
    }

    array->start = array->data;
    array->object.hash.slot = NULL;          /* njs_lvlhsh_init(), verbatim effect */
    array->object.shared_hash.slot = NULL;   /* vm->shared->array_instance_hash: n/a here */
    array->object.__proto__ = NULL;          /* &vm->prototypes[NJS_OBJ_TYPE_ARRAY].object: n/a here */
    array->object.slots = NULL;
    array->object.type = NJS_ARRAY;
    array->object.shared = 0;
    array->object.extensible = 1;
    array->object.error_data = 0;
    array->object.fast_array = (array->data != NULL);

    if (njs_fast_path(array->object.fast_array)) {
        array->size = size;
        array->length = length;

    } else {
        array->size = 0;
        array->length = 0;

        /* real code: njs_set_array(&value, array);
         *            ret = njs_array_length_redefine(vm, &value, length);
         *            if (njs_slow_path(ret != NJS_OK)) return NULL;
         * omitted -- see file header; only failure mode is OOM, not modeled. */
    }

    return array;
}

/* ---- verbatim target function (target/original_function.c, byte-for-byte) ---- */
static njs_jump_off_t
njs_vmcode_array(njs_vm_t *vm, u_char *pc)
{
    uint32_t            length;
    njs_array_t         *array;
    njs_value_t         *value;
    njs_vmcode_array_t  *code;

    code = (njs_vmcode_array_t *) pc;

    array = njs_array_alloc(vm, 0, code->length, NJS_ARRAY_SPARE);

    if (njs_fast_path(array != NULL)) {

        if (code->ctor) {
            /* Array of the form [,,,], [1,,]. */
            value = array->start;
            length = array->length;

            do {
                njs_set_invalid(value);
                value++;
                length--;
            } while (length != 0);

        } else {
            /* Array of the form [], [,,1], [1,2,3]. */
            array->length = 0;
        }

        njs_set_array(&vm->retval, array);

        return sizeof(njs_vmcode_array_t);
    }

    return NJS_ERROR;
}
/* ---- end verbatim target function ---- */

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    /* Heap buffer, malloc'd to EXACTLY sizeof(njs_vmcode_array_t) -- the
     * attacker-controlled bytecode record `pc` points to. Zero-initialised
     * first so a short input file leaves the tail (whichever fields the
     * generator didn't reach) at a deterministic, in-bounds zero rather than
     * reading past the heap allocation. */
    njs_vmcode_array_t *code = malloc(sizeof(njs_vmcode_array_t));
    if (!code) {
        perror("malloc");
        fclose(fp);
        return 1;
    }
    memset(code, 0, sizeof(*code));

    size_t got = fread(code, 1, sizeof(*code), fp);
    (void) got;   /* short reads intentionally leave the zero-filled tail */
    fclose(fp);

    njs_vm_t vm;
    memset(&vm, 0, sizeof(vm));

    njs_vmcode_array((njs_vm_t *) &vm, (u_char *) code);

    free(code);
    return 0;
}

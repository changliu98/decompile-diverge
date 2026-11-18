/*
 * cve_barebone harness for CVE-2021-46461 (njs) — njs_vmcode_typeof
 *
 * Isolation reproduction of the exact bug: njs_vmcode_typeof implements JS
 * `typeof` via a static lookup table
 *     static const njs_value_t *types[NJS_VALUE_TYPE_MAX];
 * indexed by value->type.  In the vulnerable tree the table has only 25
 * initializers (indices 0..24) but NJS_VALUE_TYPE_MAX == 26, so index 25
 * (NJS_DATA_VIEW) is implicitly NULL.  `typeof` on a DataView reaches
 *     vm->retval = *types[value->type];   // value->type == 25
 * which dereferences the NULL table slot via a 16-byte struct copy (memcpy)
 * -> SEGV in memcpy called directly from njs_vmcode_typeof  (CWE-476).
 *
 * All type/field/callee names below are REAL, copied verbatim from
 * data_cve/cve_68cd05b8/source_code/ (src/njs.h, njs_types.h, njs_value.h,
 * njs_value.c, njs_vmcode.h).  Nothing invented or renamed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* --- scalar typedefs (src/njs_types.h, njs.h, njs_vmcode.h, njs_str.h) --- */
typedef unsigned char        u_char;
typedef intptr_t             njs_int_t;               /* njs_types.h (64-bit) */
typedef uintptr_t            njs_uint_t;               /* njs_types.h (64-bit) */
typedef njs_uint_t           njs_bool_t;               /* njs_types.h */
typedef uintptr_t            njs_index_t;              /* njs.h */
typedef intptr_t             njs_jump_off_t;           /* njs_vmcode.h */
typedef uint8_t              njs_vmcode_operation_t;   /* njs_vmcode.h */

#define njs_length(s)        (sizeof(s) - 1)           /* njs_str.h */

/* --- forward typedefs for union member pointer types (njs.h, njs_value.h) --- */
typedef union  njs_value_s            njs_value_t;
typedef struct njs_vm_s               njs_vm_t;
typedef struct njs_function_s         njs_function_t;
typedef struct njs_object_prop_s      njs_object_prop_t;
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

/* njs_prop_handler_t (src/njs.h) */
typedef njs_int_t (*njs_prop_handler_t) (njs_vm_t *vm, njs_object_prop_t *prop,
    njs_value_t *value, njs_value_t *setval, njs_value_t *retval);

/*
 * njs_value_type_t (src/njs_value.h) — verbatim.  The order is what
 * njs_vmcode_typeof relies on; NJS_DATA_VIEW == 25, NJS_VALUE_TYPE_MAX == 26.
 */
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
#define NJS_OBJECT_SPECIAL_MIN  (NJS_FUNCTION)
    NJS_FUNCTION,
    NJS_REGEXP,
    NJS_DATE,
    NJS_TYPED_ARRAY,
#define NJS_OBJECT_SPECIAL_MAX  (NJS_TYPED_ARRAY + 1)
    NJS_PROMISE,
    NJS_OBJECT_VALUE,
    NJS_ARRAY_BUFFER,
    NJS_DATA_VIEW,
    NJS_VALUE_TYPE_MAX
} njs_value_type_t;

/*
 * union njs_value_s (src/njs_value.h) — verbatim.  16-byte value cell; the
 * struct copy of one of these is what njs_vmcode_typeof performs.
 */
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

#define NJS_STRING_SHORT              14
#define NJS_STRING_LONG               15

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

/* njs_string() initializer macro (src/njs_value.h) — verbatim */
#define njs_string(s) {                                                       \
    .short_string = {                                                         \
        .type = NJS_STRING,                                                   \
        .size = njs_length(s),                                                \
        .length = njs_length(s),                                              \
        .start = s,                                                           \
    }                                                                         \
}

/*
 * The lookup-table target globals (src/njs_value.c) — real definitions.
 * These are the exact constants njs_vmcode_typeof's `types[]` points at, so
 * indices 0..24 resolve to real non-NULL cells (safe inputs copy from them);
 * index 25 has no initializer -> NULL -> the crash.
 */
const njs_value_t  njs_string_undefined =   njs_string("undefined");
const njs_value_t  njs_string_boolean =     njs_string("boolean");
const njs_value_t  njs_string_number =      njs_string("number");
const njs_value_t  njs_string_symbol =      njs_string("symbol");
const njs_value_t  njs_string_string =      njs_string("string");
const njs_value_t  njs_string_data =        njs_string("data");
const njs_value_t  njs_string_external =    njs_string("external");
const njs_value_t  njs_string_invalid =     njs_string("invalid");
const njs_value_t  njs_string_object =      njs_string("object");
const njs_value_t  njs_string_function =    njs_string("function");

/* njs_vmcode_t / njs_vmcode_2addr_t (src/njs_vmcode.h) — for the sizeof() */
typedef struct {
    njs_vmcode_operation_t     operation;
    uint8_t                    operands;   /* 2 bits */
} njs_vmcode_t;

typedef struct {
    njs_vmcode_t               code;
    njs_index_t                dst;
    njs_index_t                src;
} njs_vmcode_2addr_t;

/*
 * njs_vm_s (src/njs_vm.h) — minimal faithful slice: njs_vmcode_typeof only
 * touches vm->retval (real field name/type); the full VM struct is irrelevant
 * to the isolated call.
 */
struct njs_vm_s {
    njs_value_t              retval;
};

/* ===================== TARGET FUNCTION (verbatim) ===================== */

static njs_jump_off_t
njs_vmcode_typeof(njs_vm_t *vm, njs_value_t *value, njs_value_t *invld)
{
    /* ECMAScript 5.1: null, array and regexp are objects. */

    static const njs_value_t  *types[NJS_VALUE_TYPE_MAX] = {
        &njs_string_object,
        &njs_string_undefined,
        &njs_string_boolean,
        &njs_string_number,
        &njs_string_symbol,
        &njs_string_string,
        &njs_string_data,
        &njs_string_external,
        &njs_string_invalid,
        &njs_string_undefined,
        &njs_string_undefined,
        &njs_string_undefined,
        &njs_string_undefined,
        &njs_string_undefined,
        &njs_string_undefined,
        &njs_string_undefined,

        &njs_string_object,
        &njs_string_object,
        &njs_string_function,
        &njs_string_object,
        &njs_string_object,
        &njs_string_object,
        &njs_string_object,
        &njs_string_object,
        &njs_string_object,
    };

    vm->retval = *types[value->type];

    return sizeof(njs_vmcode_2addr_t);
}
/* =================== end verbatim target function =================== */

/*
 * Driver: read argv[1] into a HEAP buffer (ASAN-guarded), consume its first
 * byte FDP-style as value->type, then call njs_vmcode_typeof in isolation.
 *
 *   value->type == 25 (NJS_DATA_VIEW)  -> types[25] is NULL -> memcpy(NULL)
 *                                          -> SEGV in memcpy from
 *                                          njs_vmcode_typeof  (CWE-476, the PoC)
 *   value->type in 0..24               -> valid non-NULL table slot -> clean
 */
int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input>\n", argv[0]);
        return 2;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        return 2;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) {
        fclose(f);
        return 2;
    }

    size_t n = (size_t) sz;
    /* HEAP-allocate the input so ASAN guards it (never a stack/static array). */
    unsigned char *buf = (unsigned char *) malloc(n ? n : 1);
    if (buf == NULL) {
        fclose(f);
        return 2;
    }
    size_t got = fread(buf, 1, n, f);
    fclose(f);

    /* FDP-style: first byte selects the value type driving the table lookup. */
    uint8_t sel = (got >= 1) ? buf[0] : 0;

    /* Heap-allocate the njs objects the target dereferences (calloc -> zeroed). */
    njs_vm_t    *vm    = (njs_vm_t *)    calloc(1, sizeof(njs_vm_t));
    njs_value_t *value = (njs_value_t *) calloc(1, sizeof(njs_value_t));
    if (vm == NULL || value == NULL) {
        free(buf);
        return 2;
    }

    value->type = (njs_value_type_t) sel;

    /*
     * Call through a volatile function pointer so -O1 cannot inline the static
     * target into main() — this keeps njs_vmcode_typeof on the crash stack,
     * exactly as the real VM's dispatch table calls it indirectly.
     */
    njs_jump_off_t (* volatile fn)(njs_vm_t *, njs_value_t *, njs_value_t *)
        = njs_vmcode_typeof;

    njs_jump_off_t r = fn(vm, value, NULL);

    /* Keep the result live so nothing is optimized away. */
    printf("ret=%ld type=%u\n", (long) r, (unsigned) value->type);

    free(value);
    free(vm);
    free(buf);
    return 0;
}

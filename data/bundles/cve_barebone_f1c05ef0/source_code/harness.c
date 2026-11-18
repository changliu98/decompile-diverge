/*
 * cve_barebone direct-call harness for CVE-2021-46463 (njs)
 * target: njs_promise_perform_then  (src/njs_promise.c)  CWE-476 NULL deref
 *
 * The real bug: Promise.prototype.then() accepts any object whose prototype
 * chain contains Promise (loose njs_object_proto_lookup check in the caller),
 * so a NON-promise object reaches njs_promise_perform_then.  The function then
 * does  data = njs_data(&promise->value)  and dereferences `data` (data->state)
 * WITHOUT validating that `value` is a real promise -> the internal promise
 * data pointer is NULL/garbage -> NULL pointer dereference (SEGV / CWE-476).
 *
 * This harness embeds the REAL njs type vocabulary (names / fields / macros
 * copied verbatim from src/) and the target function BYTE-FOR-BYTE, then drives
 * it in isolation: FDP-style bytes from a HEAP input buffer decide whether the
 * spliced-in promise object carries a NULL internal data pointer (TRIGGER) or a
 * real, PENDING njs_promise_data_t with initialised queues (SAFE).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* ---- base scalar types (src/njs.h, src/njs_types.h) ---- */
typedef int             njs_int_t;
typedef unsigned int    njs_uint_t;
typedef njs_uint_t      njs_bool_t;
typedef uintptr_t       njs_index_t;

#define NJS_OK             0
#define NJS_ERROR          (-1)

/* src/njs_clang.h (no-builtin variant) */
#define njs_slow_path(x)   (x)
#define njs_fast_path(x)   (x)
#define njs_inline         static inline

/* ---- enums (src/njs_value.h, src/njs_promise.h, src/njs_promise.c) ---- */
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

typedef enum {
    NJS_DATA_TAG_ANY = 0,
    NJS_DATA_TAG_MAX
} njs_data_tag_t;

/* src/njs_promise.h */
typedef enum {
    NJS_PROMISE_PENDING = 0,
    NJS_PROMISE_FULFILL,
    NJS_PROMISE_REJECTED
} njs_promise_type_t;

/* src/njs_promise.c */
typedef enum {
    NJS_PROMISE_HANDLE = 0,
    NJS_PROMISE_REJECT
} njs_promise_rejection_type_t;

/* ---- forward struct typedefs (src/njs_value.h) ---- */
typedef union  njs_value_s            njs_value_t;
typedef struct njs_vm_s               njs_vm_t;
typedef struct njs_mp_s               njs_mp_t;
typedef struct njs_string_s           njs_string_t;
typedef struct njs_object_s           njs_object_t;
typedef struct njs_object_value_s     njs_object_value_t;
typedef struct njs_function_s         njs_function_t;
typedef struct njs_function_lambda_s  njs_function_lambda_t;
typedef struct njs_regexp_pattern_s   njs_regexp_pattern_t;
typedef struct njs_array_s            njs_array_t;
typedef struct njs_array_buffer_s     njs_array_buffer_t;
typedef struct njs_typed_array_s      njs_typed_array_t;
typedef struct njs_typed_array_s      njs_data_view_t;
typedef struct njs_regexp_s           njs_regexp_t;
typedef struct njs_date_s             njs_date_t;
typedef struct njs_object_value_s     njs_promise_t;
typedef struct njs_property_next_s    njs_property_next_t;
typedef struct njs_object_prop_s      njs_object_prop_t;
typedef struct njs_exotic_slots_s     njs_exotic_slots_t;

/* src/njs_lvlhsh.h */
typedef struct {
    void                      *slot;
} njs_lvlhsh_t;

/* function-pointer typedefs (src/njs.h) */
typedef njs_int_t (*njs_prop_handler_t) (njs_vm_t *vm, njs_object_prop_t *prop,
    njs_value_t *value, njs_value_t *setval, njs_value_t *retval);
typedef njs_int_t (*njs_exotic_keys_t)(njs_vm_t *vm, njs_value_t *value,
    njs_array_t *keys);
typedef njs_int_t (*njs_function_native_t) (njs_vm_t *vm, njs_value_t *args,
    njs_uint_t nargs, njs_index_t retval);

/* ---- union njs_value_s (verbatim, src/njs_value.h) ---- */
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

/* ---- njs_object_s (verbatim, src/njs_value.h) ---- */
struct njs_object_s {
    njs_lvlhsh_t                      hash;
    njs_lvlhsh_t                      shared_hash;

    njs_object_t                      *__proto__;
    njs_exotic_slots_t                *slots;

    njs_value_type_t                  type:8;
    uint8_t                           shared;

    uint8_t                           extensible:1;
    uint8_t                           error_data:1;
    uint8_t                           fast_array:1;
};

/* ---- njs_object_value_s / njs_promise_t (verbatim, src/njs_value.h) ---- */
struct njs_object_value_s {
    njs_object_t                      object;
    njs_value_t                       value;
};

/* ---- njs_function_s (verbatim, src/njs_value.h) ---- */
struct njs_function_s {
    njs_object_t                      object;

    uint8_t                           args_offset;

    uint8_t                           args_count:4;

    uint8_t                           closure_copied:1;
    uint8_t                           native:1;
    uint8_t                           ctor:1;
    uint8_t                           global_this:1;
    uint8_t                           global:1;

    uint8_t                           magic8;

    union {
        njs_function_lambda_t         *lambda;
        njs_function_native_t         native;
        njs_function_t                *bound_target;
    } u;

    void                              *context;
    void                              *await;

    njs_value_t                       *bound;
};

/* ---- njs_queue.h (verbatim) ---- */
typedef struct njs_queue_link_s  njs_queue_link_t;

struct njs_queue_link_s {
    njs_queue_link_t  *prev;
    njs_queue_link_t  *next;
};

typedef struct {
    njs_queue_link_t  head;
} njs_queue_t;

#define njs_queue_init(queue)                                                 \
    do {                                                                      \
        (queue)->head.prev = &(queue)->head;                                  \
        (queue)->head.next = &(queue)->head;                                  \
    } while (0)

#define njs_queue_insert_tail(queue, link)                                    \
    do {                                                                      \
        (link)->prev = (queue)->head.prev;                                    \
        (link)->prev->next = (link);                                          \
        (link)->next = &(queue)->head;                                        \
        (queue)->head.prev = (link);                                          \
    } while (0)

/* ---- src/njs_promise.h ---- */
typedef struct {
    njs_value_t               promise;
    njs_value_t               resolve;
    njs_value_t               reject;
} njs_promise_capability_t;

typedef struct {
    njs_promise_type_t        state;
    njs_value_t               result;
    njs_queue_t               fulfill_queue;
    njs_queue_t               reject_queue;
    njs_bool_t                is_handled;
} njs_promise_data_t;

/* ---- src/njs_promise.c ---- */
typedef struct {
    njs_promise_capability_t  *capability;
    njs_promise_type_t        type;
    njs_queue_link_t          link;
    njs_value_t               handler;
} njs_promise_reaction_t;

/*
 * njs_promise_context_t is referenced only by sizeof() inside the (never
 * executed) else branch of the target; the real struct is needed so the
 * verbatim body compiles.  (src/njs_promise.c)
 */
typedef struct {
    njs_value_t               promise;
    njs_value_t               finally;
    njs_value_t               constructor;
    njs_bool_t                resolved;
    njs_bool_t                *resolved_ref;
    njs_promise_capability_t  *capability;
    njs_function_native_t     handler;
} njs_promise_context_t;

/* ---- minimal-but-real njs_vm_t (only mem_pool + retval are used) ---- */
struct njs_vm_s {
    njs_mp_t                  *mem_pool;
    njs_value_t               retval;
};

/* ================= value macros (verbatim, src/njs*.h) ================= */
#define njs_value_arg(val) ((njs_value_t *) val)

#define njs_is_function(value)                                                \
    ((value)->type == NJS_FUNCTION)

#define njs_data(value)                                                       \
    ((value)->data.u.data)

#define njs_promise(value)                                                    \
    ((value)->data.u.promise)

/* ================= incidental machinery (faithful stubs) ================= */
extern const njs_value_t njs_value_undefined;
const njs_value_t njs_value_undefined = { .data = { .type = NJS_UNDEFINED } };

/* memory pool: the bug is unrelated to allocation; return real, ASAN-guarded
 * heap so the two reaction allocations succeed and execution reaches the
 * unchecked data->state dereference. */
void *
njs_mp_alloc(njs_mp_t *mp, size_t size)
{
    (void) mp;
    return malloc(size);
}

void
njs_memory_error(njs_vm_t *vm)
{
    (void) vm;
}

void
njs_vm_retval_set(njs_vm_t *vm, const njs_value_t *value)
{
    if (vm != NULL) {
        vm->retval = *value;
    }
}

/* njs_set_data (verbatim, src/njs_value.h) */
njs_inline void
njs_set_data(njs_value_t *value, void *data, njs_data_tag_t tag)
{
    value->data.magic32 = tag;
    value->data.u.data = data;
    value->type = NJS_DATA;
    value->data.truth = 1;
}

/* callees only reachable on the state!=PENDING branch (neither of our two
 * differential paths executes them: TRIGGER faults at data->state, SAFE takes
 * the PENDING queue path).  Faithful minimal stubs so the TU links. */
njs_function_t *
njs_promise_create_function(njs_vm_t *vm, size_t context_size)
{
    (void) vm; (void) context_size;
    return (njs_function_t *) calloc(1, sizeof(njs_function_t));
}

njs_int_t
njs_promise_reaction_job(njs_vm_t *vm, njs_value_t *args, njs_uint_t nargs,
    njs_index_t unused)
{
    (void) vm; (void) args; (void) nargs; (void) unused;
    return NJS_OK;
}

njs_int_t
njs_promise_add_event(njs_vm_t *vm, njs_function_t *function, njs_value_t *args,
    njs_uint_t nargs)
{
    (void) vm; (void) function; (void) args; (void) nargs;
    return NJS_OK;
}

static njs_int_t
njs_promise_host_rejection_tracker(njs_vm_t *vm, njs_promise_t *promise,
    njs_promise_rejection_type_t operation)
{
    (void) vm; (void) promise; (void) operation;
    return NJS_OK;
}

/* ===================================================================== */
/* ==== TARGET FUNCTION: njs_promise_perform_then (VERBATIM) ==== */
/* ===================================================================== */
njs_int_t
njs_promise_perform_then(njs_vm_t *vm, njs_value_t *value,
    njs_value_t *fulfilled, njs_value_t *rejected,
    njs_promise_capability_t *capability)
{
    njs_int_t               ret;
    njs_value_t             arguments[2];
    njs_promise_t           *promise;
    njs_function_t          *function;
    njs_promise_data_t      *data;
    njs_promise_reaction_t  *fulfilled_reaction, *rejected_reaction;

    if (!njs_is_function(fulfilled)) {
        fulfilled = njs_value_arg(&njs_value_undefined);
    }

    if (!njs_is_function(rejected)) {
        rejected = njs_value_arg(&njs_value_undefined);
    }

    promise = njs_promise(value);
    data = njs_data(&promise->value);

    fulfilled_reaction = njs_mp_alloc(vm->mem_pool,
                                      sizeof(njs_promise_reaction_t));
    if (njs_slow_path(fulfilled_reaction == NULL)) {
        njs_memory_error(vm);
        return NJS_ERROR;
    }

    fulfilled_reaction->capability = capability;
    fulfilled_reaction->handler = *fulfilled;
    fulfilled_reaction->type = NJS_PROMISE_FULFILL;

    rejected_reaction = njs_mp_alloc(vm->mem_pool,
                                     sizeof(njs_promise_reaction_t));
    if (njs_slow_path(rejected_reaction == NULL)) {
        njs_memory_error(vm);
        return NJS_ERROR;
    }

    rejected_reaction->capability = capability;
    rejected_reaction->handler = *rejected;
    rejected_reaction->type = NJS_PROMISE_REJECTED;

    if (data->state == NJS_PROMISE_PENDING) {
        njs_queue_insert_tail(&data->fulfill_queue, &fulfilled_reaction->link);
        njs_queue_insert_tail(&data->reject_queue, &rejected_reaction->link);

    } else {
        function = njs_promise_create_function(vm,
                                               sizeof(njs_promise_context_t));
        function->u.native = njs_promise_reaction_job;

        if (data->state == NJS_PROMISE_REJECTED) {
            njs_set_data(&arguments[0], rejected_reaction, 0);

            ret = njs_promise_host_rejection_tracker(vm, promise,
                                                     NJS_PROMISE_HANDLE);
            if (njs_slow_path(ret != NJS_OK)) {
                return ret;
            }

        } else {
            njs_set_data(&arguments[0], fulfilled_reaction, 0);
        }

        arguments[1] = data->result;

        ret = njs_promise_add_event(vm, function, arguments, 2);
        if (njs_slow_path(ret != NJS_OK)) {
            return ret;
        }
    }

    data->is_handled = 1;

    if (capability == NULL) {
        njs_vm_retval_set(vm, &njs_value_undefined);

    } else {
        njs_vm_retval_set(vm, &capability->promise);
    }

    return NJS_OK;
}
/* ===================================================================== */
/* ==== END TARGET FUNCTION ==== */
/* ===================================================================== */

/* -------------------------- driver -------------------------- */
int
main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }

    FILE *f = fopen(argv[1], "rb");
    if (f == NULL) {
        return 0;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (sz < 0) {
        sz = 0;
    }

    /* HEAP-allocated input buffer so any over-read is ASAN-visible */
    unsigned char *buf = (unsigned char *) malloc(sz ? (size_t) sz : 1);
    size_t n = fread(buf, 1, (size_t) sz, f);
    fclose(f);

    /* FDP-style byte consumption */
    unsigned char mode = (n > 0) ? buf[0] : 0;   /* bit0: trigger vs safe   */
    unsigned char ff   = (n > 1) ? buf[1] : 0;   /* fulfilled is a function? */
    unsigned char rf   = (n > 2) ? buf[2] : 0;   /* rejected is a function?  */
    unsigned char capf = (n > 3) ? buf[3] : 0;   /* capability present?      */
    unsigned char tail = (n > 4) ? buf[4] : 0;   /* extra entropy            */

    njs_vm_t *vm = (njs_vm_t *) calloc(1, sizeof(njs_vm_t));
    static njs_mp_t *pool_slot;
    vm->mem_pool = (njs_mp_t *) &pool_slot;      /* non-NULL dummy pool */

    njs_value_t *fulfilled = (njs_value_t *) calloc(1, sizeof(njs_value_t));
    njs_value_t *rejected  = (njs_value_t *) calloc(1, sizeof(njs_value_t));
    fulfilled->data.type = (ff & 1) ? NJS_FUNCTION : NJS_UNDEFINED;
    rejected->data.type  = (rf & 1) ? NJS_FUNCTION : NJS_UNDEFINED;
    if (ff & 1) {
        fulfilled->data.u.function =
            (njs_function_t *) calloc(1, sizeof(njs_function_t));
    }
    if (rf & 1) {
        rejected->data.u.function =
            (njs_function_t *) calloc(1, sizeof(njs_function_t));
    }

    /* the object reaching perform_then as `value` */
    njs_promise_t *ov = (njs_promise_t *) calloc(1, sizeof(njs_promise_t));
    njs_value_t *value = (njs_value_t *) calloc(1, sizeof(njs_value_t));
    value->data.type = NJS_PROMISE;
    value->data.u.promise = ov;

    njs_promise_capability_t *cap = NULL;
    if (capf & 1) {
        cap = (njs_promise_capability_t *) calloc(1, sizeof(*cap));
    }

    if (mode & 1) {
        /*
         * TRIGGER: object is not a real promise -> its internal promise-data
         * pointer is NULL.  perform_then reads data->state without checking
         * -> NULL pointer dereference (CWE-476).
         */
        ov->value.data.type = NJS_INVALID;
        ov->value.data.u.data = NULL;
    } else {
        /*
         * SAFE: a real, initialised, PENDING njs_promise_data_t.  perform_then
         * enqueues both reactions and returns NJS_OK cleanly.
         */
        njs_promise_data_t *data =
            (njs_promise_data_t *) calloc(1, sizeof(njs_promise_data_t));
        data->state = NJS_PROMISE_PENDING;
        njs_queue_init(&data->fulfill_queue);
        njs_queue_init(&data->reject_queue);
        data->is_handled = 0;
        ov->value.data.type = NJS_DATA;
        ov->value.data.u.data = data;
    }

    /* indirect call through a volatile pointer keeps the target a real,
     * non-inlined frame so it appears by name in the ASAN crash stack. */
    njs_int_t (*volatile fn)(njs_vm_t *, njs_value_t *, njs_value_t *,
                             njs_value_t *, njs_promise_capability_t *) =
        njs_promise_perform_then;

    njs_int_t r = fn(vm, value, fulfilled, rejected, cap);

    fprintf(stderr, "ret=%d mode=%u tail=%u\n", (int) r, (unsigned) mode,
            (unsigned) tail);

    free(buf);
    return 0;
}

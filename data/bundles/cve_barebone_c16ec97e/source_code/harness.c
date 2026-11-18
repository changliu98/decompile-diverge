/*
 * Direct-call crash harness for cve_c16ec97e (CVE-2022-31306, njs
 * src/njs_array.c, njs_array_convert_to_slow_array()). Embeds the vulnerable
 * function VERBATIM and calls it directly with a heap-allocated
 * `njs_array_t *` built from argv[1], so ASan catches the exact NULL-pointer
 * dereference this CVE describes, with no dependency on the rest of njs
 * (the JS parser/VM/Object.defineProperty machinery that produces this state
 * in the real product).
 *
 * Bug recap (matches baseline dedup_token
 * "njs_array_convert_to_slow_array--njs_object_prop_define--
 * njs_object_define_property" / summary "AddressSanitizer: SEGV
 * /work/src/njs_array.c:151:13 in njs_array_convert_to_slow_array", see
 * io/crafting_report.md for the full re-entrancy story): the fix commit
 * (81af26364c21) adds `if (!array->object.fast_array) return NJS_OK;` on
 * entry because, prior to it, a getter side effect during
 * Object.defineProperty() could call njs_array_convert_to_slow_array() a
 * SECOND time on an array a first (re-entrant) call already converted:
 * ->start was njs_mp_free()'d and set NULL, but ->length was left
 * unchanged (still whatever count it had). The unguarded second call then
 * does
 *     for (i = 0; i < length; i++) {
 *         if (njs_is_valid(&array->start[i])) {   <- array->start == NULL
 *     ...
 * njs_is_valid() reads `(value)->type`, i.e. dereferences address
 * `0 + i*sizeof(njs_value_t)` -> SIGSEGV at njs_array.c:151 (== line 14 of
 * target/original_function.c) whenever length > 0. The fault is entirely
 * local to njs_array_convert_to_slow_array(): it needs no JS
 * parser/VM/property-hash machinery, only an njs_array_t whose ->start is
 * NULL and ->length is nonzero.
 *
 * `original_function.c` is embedded byte-for-byte below (see the VERBATIM
 * markers) -- logic, names, and signature untouched.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal, faithful subset of njs's own headers (source_code/src/
 * njs_types.h, njs_value.h, njs_object.h, njs_array.h, njs_vm.h, njs_mp.h,
 * njs_clang.h): only the types/macros njs_array_convert_to_slow_array()
 * itself touches, real names and (where it matters for correctness) real
 * layout -- nothing else pulled in. ---- */

/* njs_types.h, amd64 branch (`#if (__amd64__)` -> NJS_INT_T_SIZE 4): the
 * exact typedefs njs actually gets on this architecture. */
typedef int             njs_int_t;
typedef unsigned int    njs_uint_t;
typedef njs_uint_t      njs_bool_t;
#define NJS_OK           0
#define NJS_ERROR        (-1)

/* njs_value.h: njs_value_type_t, the full real enum (verbatim). */
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

typedef struct njs_object_s  njs_object_t;
typedef struct njs_array_s   njs_array_t;

/* njs_value.h `union njs_value_s`, reduced to the arms njs_set_array() /
 * njs_is_valid() (both used verbatim below) actually touch: the `data`
 * struct's type/truth/u.array, plus the sibling top-level `type` bitfield
 * the real union also declares (njs_is_valid() reads THAT one directly --
 * this is exactly how the real njs code punches through the union, not an
 * invention of this harness). short_string/long_string arms and the other
 * `data.u` pointer members (number/object/function/regexp/date/.../) are
 * dropped: real field names/types for everything kept, nothing else
 * referenced anywhere in the target function or its (stubbed) callees. */
typedef union njs_value_u {
    struct {
        njs_value_type_t    type:8;
        uint8_t              truth;
        uint16_t             magic16;
        uint32_t             magic32;
        union {
            njs_object_t     *object;
            njs_array_t      *array;
            void             *data;
        } u;
    } data;
    njs_value_type_t         type:8;
} njs_value_t;

/* njs_value.h macros, verbatim. */
#define njs_is_valid(value)                                                  \
    ((value)->type != NJS_INVALID)

static inline void
njs_set_array(njs_value_t *value, njs_array_t *array)
{
    value->data.u.array = array;
    value->type = NJS_ARRAY;
    value->data.truth = 1;
}

/* njs_clang.h (the `#else` / no-__builtin_expect branch -- functionally
 * identical to the njs_expect() branch used when the compiler supports it,
 * just without the branch-prediction hint). */
#define njs_slow_path(x)   (x)

/* njs_value.h `struct njs_object_s`: minimal subset -- the target function
 * touches only `object.fast_array` (`array->object.fast_array = 0;`). The
 * real struct also carries hash/shared_hash/__proto__/slots/type/shared/
 * extensible/error_data; none of those are referenced anywhere in this
 * harness. */
struct njs_object_s {
    uint8_t   fast_array:1;
};

/* njs_value.h `struct njs_array_s`, verbatim -- complete, all 5 real
 * fields. */
struct njs_array_s {
    njs_object_t    object;
    uint32_t        size;
    uint32_t        length;
    njs_value_t     *start;
    njs_value_t     *data;
};

/* njs_value.h `struct njs_object_prop_s` + its two real enum field types,
 * verbatim -- complete. */
typedef enum {
    NJS_PROPERTY = 0,
    NJS_PROPERTY_REF,
    NJS_PROPERTY_TYPED_ARRAY_REF,
    NJS_PROPERTY_HANDLER,
    NJS_WHITEOUT,
} njs_object_prop_type_t;

typedef enum {
    NJS_ATTRIBUTE_FALSE = 0,
    NJS_ATTRIBUTE_TRUE = 1,
    NJS_ATTRIBUTE_UNSET,
} njs_object_attribute_t;

typedef struct njs_object_prop_s njs_object_prop_t;
struct njs_object_prop_s {
    njs_value_t               value;
    njs_value_t               name;
    njs_value_t               getter;
    njs_value_t               setter;
    njs_object_prop_type_t    type:8;
    njs_object_attribute_t    writable:8;
    njs_object_attribute_t    enumerable:8;
    njs_object_attribute_t    configurable:8;
};

/* njs_mp.h + njs_vm.h: an opaque allocator handle, and the ONE field of the
 * real (~30-field) `struct njs_vm_s` the target function touches --
 * `vm->mem_pool`, forwarded straight into njs_mp_free(). Nothing else in
 * njs_vm_s (paths/protos/frames/hashes/prototypes/constructors/...) is
 * referenced. */
typedef struct njs_mp_s   njs_mp_t;
typedef struct njs_vm_s   njs_vm_t;
struct njs_vm_s {
    njs_mp_t   *mem_pool;
};

/*
 * ---- callee stubs ----
 * njs_uint32_to_string() and njs_object_property_add() are reachable ONLY
 * through the loop body, and ONLY when njs_is_valid(&array->start[i]) is
 * true. Neither the 25 triggering inputs (array->start == NULL: the fault
 * fires at i==0, before either of these can run) nor most of the 25 safe
 * inputs (array->start valid but every element NJS_INVALID -- "all holes")
 * ever call them. A few safe inputs DO give one element a valid type to
 * exercise this call site for corpus diversity, so both stubs must be
 * linkable and must behave sanely (non-crashing, and truthful to their real
 * contract's error path) if actually invoked. Real signatures; the bodies
 * are minimal stand-ins for njs's lvlhsh-backed property table and short-
 * string formatter, which are irrelevant to the CWE-476 NULL-deref this
 * harness targets.
 */
static void
njs_uint32_to_string(njs_value_t *value, uint32_t u32)
{
    (void) value;
    (void) u32;
}

static njs_object_prop_t *
njs_object_property_add(njs_vm_t *vm, njs_value_t *object, njs_value_t *key,
    njs_bool_t replace)
{
    (void) vm;
    (void) object;
    (void) key;
    (void) replace;
    /* real njs_object_property_add() returns NULL on allocation/lvlhsh
     * failure; njs_array_convert_to_slow_array() already handles that via
     * njs_slow_path(prop == NULL) -> NJS_ERROR, so this is a faithful,
     * non-crashing stub result. */
    return NULL;
}

static void
njs_mp_free(njs_mp_t *mp, void *p)
{
    (void) mp;
    /* Our own vm->mem_pool is an opaque sentinel (never a real njs_mp_t),
     * and array->start is always a plain malloc()'d heap buffer (or NULL)
     * in this harness, so a plain free() is a faithful stand-in for njs's
     * real cluster-pool allocator here. */
    free(p);
}

/* ---- target function, embedded VERBATIM from target/original_function.c
 * (src/njs_array.c:138-168) -- logic, names, and signature untouched. ---- */
njs_int_t
njs_array_convert_to_slow_array(njs_vm_t *vm, njs_array_t *array)
{
    uint32_t           i, length;
    njs_value_t        index, value;
    njs_object_prop_t  *prop;

    njs_set_array(&value, array);
    array->object.fast_array = 0;

    length = array->length;

    for (i = 0; i < length; i++) {
        if (njs_is_valid(&array->start[i])) {
            njs_uint32_to_string(&index, i);
            prop = njs_object_property_add(vm, &value, &index, 0);
            if (njs_slow_path(prop == NULL)) {
                return NJS_ERROR;
            }

            prop->value = array->start[i];
        }
    }

    /* GC: release value. */

    njs_mp_free(vm->mem_pool, array->start);
    array->start = NULL;

    return NJS_OK;
}
/* ---- end verbatim ---- */

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    long len = ftell(f);
    if (len < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    /* REQUIRED: heap buffer for the attacker-controlled bytes, so any
     * later use of them is via a heap allocation ASan tracks. */
    unsigned char *buf = NULL;
    if (len > 0) {
        buf = malloc((size_t) len);
        if (!buf) { fclose(f); return 1; }
        size_t rd = fread(buf, 1, (size_t) len, f);
        fclose(f);
        if (rd != (size_t) len) { free(buf); return 1; }
    } else {
        fclose(f);
    }

    /*
     * Harness-only input convention (documented here; there's no wire
     * format at this call site in the real project -- a direct-call
     * harness necessarily invents SOME mapping from "a corpus file" to
     * "the njs_array_t the target function is handed"):
     *
     *   byte[0] == 0x01  -> TRIGGERING: array->start = NULL, array->length
     *                       = the little-endian uint32 at byte[1..4]
     *                       (clamped to 1..4096, so it's always > 0).
     *                       Reproduces the CVE exactly: a second
     *                       njs_array_convert_to_slow_array() call on an
     *                       array a prior (re-entrant) call already
     *                       converted -- ->start is NULL but ->length is
     *                       still whatever it was (script/attacker
     *                       controlled) -> njs_is_valid(&array->start[0])
     *                       reads `type` at address 0 -> SIGSEGV, exactly
     *                       njs_array.c:151 / original_function.c:14.
     *   byte[0] == 0x02  -> SAFE (one valid element): array->start is a
     *                       real heap buffer of `length` njs_value_t
     *                       (length = byte[1..4] LE, clamped 1..64);
     *                       element 0 is marked NJS_NUMBER (a real, valid
     *                       value), so the loop body runs once and hits
     *                       the stubbed njs_object_property_add() -> NULL
     *                       -> the function's own NJS_ERROR early-return.
     *                       No crash.
     *   anything else    -> SAFE (all holes): array->start is a real heap
     *                       buffer of `length` njs_value_t (length =
     *                       byte[1..4] LE if the file has >= 5 bytes,
     *                       else file-length mod 64), every element
     *                       NJS_INVALID -- mirrors a sparse/empty array
     *                       being converted for the first time (the
     *                       ordinary, non-buggy call). The loop runs to
     *                       completion touching no property, then
     *                       njs_mp_free() releases ->start cleanly.
     *
     * Bytes beyond the 5-byte header are never read by the target function
     * or this harness; they exist purely to vary corpus file length/
     * content, exactly mirroring how in the real bug the crash is
     * independent of the rest of the JS source once the vulnerable array
     * shape (fast_array already converted once, ->start NULL, ->length
     * nonzero) is present -- see io/crafting_report.md's "35 structural
     * triggering variants".
     */
    uint32_t hlen = 0;
    if (len >= 5) {
        hlen = (uint32_t) buf[1] | ((uint32_t) buf[2] << 8) |
               ((uint32_t) buf[3] << 16) | ((uint32_t) buf[4] << 24);
    }
    unsigned char mode = (len >= 1) ? buf[0] : 0xFF;

    njs_vm_t vm_storage;
    njs_vm_t *vm = &vm_storage;
    /* Opaque sentinel: never dereferenced by anything in this harness --
     * only ever forwarded to njs_mp_free(), whose stub ignores it. */
    vm->mem_pool = (njs_mp_t *) (uintptr_t) 0x1;

    njs_array_t array_storage;
    njs_array_t *array = &array_storage;
    memset(array, 0, sizeof(*array));
    array->object.fast_array = 1;   /* mirrors the real precondition: a
                                      * still-"fast" array on entry (the
                                      * function itself sets this to 0
                                      * unconditionally, so the value here
                                      * is cosmetic, not load-bearing). */

    njs_value_t *heap_start = NULL;
    uint32_t length = 0;

    if (mode == 0x01) {
        /* TRIGGERING */
        length = (hlen % 4096) + 1;   /* always >= 1 */
        array->start = NULL;
        array->length = length;
    } else if (mode == 0x02) {
        /* SAFE: one valid element */
        length = (hlen % 64) + 1;     /* always >= 1 */
        heap_start = malloc((size_t) length * sizeof(njs_value_t));
        if (!heap_start) { free(buf); return 1; }
        memset(heap_start, 0, (size_t) length * sizeof(njs_value_t));
        for (uint32_t i = 0; i < length; i++) {
            heap_start[i].type = NJS_INVALID;
        }
        heap_start[0].type = NJS_NUMBER;
        array->start = heap_start;
        array->length = length;
    } else {
        /* SAFE: all holes */
        length = (len >= 5) ? (hlen % 64) : ((uint32_t) len % 64);
        heap_start = (length > 0)
            ? malloc((size_t) length * sizeof(njs_value_t)) : NULL;
        if (length > 0 && !heap_start) { free(buf); return 1; }
        for (uint32_t i = 0; i < length; i++) {
            heap_start[i].type = NJS_INVALID;
        }
        array->start = heap_start;
        array->length = length;
    }

    njs_int_t rc = njs_array_convert_to_slow_array(vm, array);

    /* njs_mp_free() (our stub) already freed array->start on the NJS_OK
     * path, and the target function set it NULL itself; on the NJS_ERROR
     * early-return path (mode 0x02) it's still ours to free. */
    if (array->start != NULL) {
        free(array->start);
    }

    printf("njs_array_convert_to_slow_array returned %ld "
           "(mode=0x%02x, length=%u)\n", (long) rc, mode, array->length);

    free(buf);
    return 0;
}

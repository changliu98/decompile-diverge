/*
 * Direct-call crash harness for CVE-2022-31031 (pjproject, CWE-787).
 *
 * Target function: pjstun_parse_msg()
 *   pjlib-util/src/pjlib-util/stun_simple.c
 *
 * The bug: pjstun_msg declares a fixed-size pointer array
 *   pjstun_attr_hdr *attr[PJSTUN_MAX_ATTR];   // PJSTUN_MAX_ATTR == 16
 * (pjlib-util/include/pjlib-util/stun_simple.h, pjlib-util/include/
 * pjlib-util/config.h). pjstun_parse_msg()'s attribute-parsing loop walks
 * the STUN message's attribute list purely from the ATTACKER-CONTROLLED
 * `msg_len` field and each attribute's own (also attacker-controlled)
 * length, and increments `msg->attr_count` on every iteration WITHOUT ever
 * checking it against PJSTUN_MAX_ATTR:
 *
 *     msg->attr_count = 0;
 *     ...
 *     while (msg_len > 0) {
 *         pjstun_attr_hdr **attr = &msg->attr[msg->attr_count];
 *         ...
 *         *attr = (pjstun_attr_hdr*)p_attr;      <-- OOB WRITE once
 *                                                     attr_count >= 16
 *         ...
 *         ++msg->attr_count;
 *     }
 *
 * The upstream fix (450baca94f475345542c6953832650c390889202) adds exactly
 * one guard, `msg->attr_count < attr_max_cnt` (attr_max_cnt =
 * PJ_ARRAY_SIZE(msg->attr) == 16), to the while condition. So a STUN
 * message that declares 17 or more minimal (4-byte) attributes drives
 * `msg->attr_count` to 16 and the write `*attr = ...` on the 17th
 * iteration stores a pointer into `msg->attr[16]` -- one past the end of
 * the 16-element array -- a heap out-of-bounds WRITE (CWE-787).
 *
 * This harness calls pjstun_parse_msg() directly and in isolation: it
 * reads the attacker-controlled STUN message bytes from argv[1] into a
 * HEAP buffer (malloc, ASAN-guarded) and passes it as `buf`/`buf_len`
 * exactly as pjstun_parse_msg()'s real callers (pjstun_create_bind_req()'s
 * peers in stun_simple_client.c) do; `msg` (the struct containing the
 * overflowable `attr[16]` array) is ALSO heap-allocated so the array
 * overrun lands cleanly in ASAN's heap-buffer-overflow detector.
 *
 * pjstun_parse_msg() itself depends only on:
 *   - the real pj_uint8_t/pj_uint16_t/pj_uint32_t/pj_size_t/pj_status_t/
 *     pj_bool_t primitive typedefs (pjlib/include/pj/types.h),
 *   - the real pjstun_msg_hdr / pjstun_attr_hdr / pjstun_msg structs and
 *     PJSTUN_MAX_ATTR=16 / pjstun_msg_type / pjstun_attr_type constants
 *     (pjlib-util/include/pjlib-util/stun_simple.h,
 *      pjlib-util/include/pjlib-util/config.h),
 *   - pj_ntohs(), whose real implementation (pjlib/src/pj/sock_bsd.c) is
 *     a one-line wrapper `return ntohs(netshort);` -- reproduced verbatim
 *     using the standard <arpa/inet.h> ntohs(),
 *   - PJ_CHECK_STACK(), which by default (PJ_OS_HAS_CHECK_STACK undefined,
 *     pjlib/include/pj/os.h) expands to nothing -- a genuine no-op stub,
 *   - PJ_LOG(), which for any level above PJ_LOG_MAX_LEVEL already expands
 *     to an empty statement in the real header (pjlib/include/pj/log.h)
 *     -- reproduced as the same no-op; it only ever fires on error/warning
 *     paths that are incidental to the overflow mechanism,
 *   - the three real PJLIB_UTIL_ESTUNIN* error codes (their exact resolved
 *     values are given in pjlib-util/include/pjlib-util/errno.h's own
 *     comments), and
 *   - THIS_FILE, defined identically to stun_simple.c's own
 *     `#define THIS_FILE "stun_simple.c"`.
 * None of these affect the overflow: they are the real names/values, not
 * invented ones.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

/* ---- pjlib/include/pj/types.h (verbatim primitive typedefs) ---- */
typedef unsigned int   pj_uint32_t;
typedef unsigned short pj_uint16_t;
typedef unsigned char  pj_uint8_t;
typedef size_t         pj_size_t;
typedef int            pj_status_t;
typedef int            pj_bool_t;

/* pjlib/include/pj/types.h: enum pj_constants_ { PJ_SUCCESS=0, ... } */
#define PJ_SUCCESS  0

/* pjlib/include/pj/config.h: #define PJ_DEF(type) type  (non-DLL build) */
#define PJ_DEF(type)  type

/* pjlib/include/pj/os.h: default (PJ_OS_HAS_CHECK_STACK unset) is a no-op. */
#define PJ_CHECK_STACK()

/* pjlib/include/pj/log.h: PJ_LOG(level,arg) already expands to an empty
 * statement for any level above PJ_LOG_MAX_LEVEL in the real header;
 * reproduced as that same no-op (incidental to the overflow mechanism). */
#define PJ_LOG(level, arg)  do {} while (0)

/* pjlib/src/pj/sock_bsd.c: PJ_DEF(pj_uint16_t) pj_ntohs(pj_uint16_t netshort)
 * { return ntohs(netshort); }  -- verbatim one-line body. */
static pj_uint16_t pj_ntohs(pj_uint16_t netshort)
{
    return ntohs(netshort);
}

/* pjlib-util/src/pjlib-util/stun_simple.c */
#define THIS_FILE   "stun_simple.c"

/* pjlib-util/include/pjlib-util/errno.h (resolved values from the header's
 * own comments: PJLIB_UTIL_ERRNO_START+2/+3/+4). */
#define PJLIB_UTIL_ESTUNINMSGTYPE   320002
#define PJLIB_UTIL_ESTUNINMSGLEN    320003
#define PJLIB_UTIL_ESTUNINATTRLEN   320004

/* ---- pjlib-util/include/pjlib-util/config.h ---- */
#define PJSTUN_MAX_ATTR   16

/* ---- pjlib-util/include/pjlib-util/stun_simple.h (verbatim) ---- */
typedef enum pjstun_msg_type
{
    PJSTUN_BINDING_REQUEST                 = 0x0001,
    PJSTUN_BINDING_RESPONSE                = 0x0101,
    PJSTUN_BINDING_ERROR_RESPONSE          = 0x0111,
    PJSTUN_SHARED_SECRET_REQUEST           = 0x0002,
    PJSTUN_SHARED_SECRET_RESPONSE          = 0x0102,
    PJSTUN_SHARED_SECRET_ERROR_RESPONSE    = 0x0112
} pjstun_msg_type;

typedef enum pjstun_attr_type
{
    PJSTUN_ATTR_MAPPED_ADDR = 1,
    PJSTUN_ATTR_RESPONSE_ADDR,
    PJSTUN_ATTR_CHANGE_REQUEST,
    PJSTUN_ATTR_SOURCE_ADDR,
    PJSTUN_ATTR_CHANGED_ADDR,
    PJSTUN_ATTR_USERNAME,
    PJSTUN_ATTR_PASSWORD,
    PJSTUN_ATTR_MESSAGE_INTEGRITY,
    PJSTUN_ATTR_ERROR_CODE,
    PJSTUN_ATTR_UNKNOWN_ATTRIBUTES,
    PJSTUN_ATTR_REFLECTED_FROM,
    PJSTUN_ATTR_XOR_MAPPED_ADDR = 0x0020
} pjstun_attr_type;

typedef struct pjstun_msg_hdr
{
    pj_uint16_t     type;
    pj_uint16_t     length;
    pj_uint32_t     tsx[4];
} pjstun_msg_hdr;

typedef struct pjstun_attr_hdr
{
    pj_uint16_t     type;
    pj_uint16_t     length;
} pjstun_attr_hdr;

typedef struct pjstun_msg
{
    pjstun_msg_hdr    *hdr;
    int                 attr_count;
    pjstun_attr_hdr   *attr[PJSTUN_MAX_ATTR];
} pjstun_msg;

/* ==== VERBATIM from data_cve/cve_60a7d1a8/target/original_function.c ==== */
PJ_DEF(pj_status_t) pjstun_parse_msg( void *buf, pj_size_t buf_len, 
				      pjstun_msg *msg)
{
    pj_uint16_t msg_type, msg_len;
    char *p_attr;

    PJ_CHECK_STACK();

    msg->hdr = (pjstun_msg_hdr*)buf;
    msg_type = pj_ntohs(msg->hdr->type);

    switch (msg_type) {
    case PJSTUN_BINDING_REQUEST:
    case PJSTUN_BINDING_RESPONSE:
    case PJSTUN_BINDING_ERROR_RESPONSE:
    case PJSTUN_SHARED_SECRET_REQUEST:
    case PJSTUN_SHARED_SECRET_RESPONSE:
    case PJSTUN_SHARED_SECRET_ERROR_RESPONSE:
	break;
    default:
	PJ_LOG(4,(THIS_FILE, "Error: unknown msg type %d", msg_type));
	return PJLIB_UTIL_ESTUNINMSGTYPE;
    }

    msg_len = pj_ntohs(msg->hdr->length);
    if (msg_len != buf_len - sizeof(pjstun_msg_hdr)) {
	PJ_LOG(4,(THIS_FILE, "Error: invalid msg_len %d (expecting %d)", 
			     msg_len, buf_len - sizeof(pjstun_msg_hdr)));
	return PJLIB_UTIL_ESTUNINMSGLEN;
    }

    msg->attr_count = 0;
    p_attr = (char*)buf + sizeof(pjstun_msg_hdr);

    while (msg_len > 0) {
	pjstun_attr_hdr **attr = &msg->attr[msg->attr_count];
	pj_uint32_t len;
	pj_uint16_t attr_type;

	*attr = (pjstun_attr_hdr*)p_attr;
	len = pj_ntohs((pj_uint16_t) ((*attr)->length)) + sizeof(pjstun_attr_hdr);
	len = (len + 3) & ~3;

	if (msg_len < len) {
	    PJ_LOG(4,(THIS_FILE, "Error: length mismatch in attr %d", 
				 msg->attr_count));
	    return PJLIB_UTIL_ESTUNINATTRLEN;
	}

	attr_type = pj_ntohs((*attr)->type);
	if (attr_type > PJSTUN_ATTR_REFLECTED_FROM &&
	    attr_type != PJSTUN_ATTR_XOR_MAPPED_ADDR)
	{
	    PJ_LOG(5,(THIS_FILE, "Warning: unknown attr type %x in attr %d. "
				 "Attribute was ignored.",
				 attr_type, msg->attr_count));
	}

	msg_len = (pj_uint16_t)(msg_len - len);
	p_attr += len;
	++msg->attr_count;
    }

    return PJ_SUCCESS;
}
/* ==== end verbatim ==== */

int main(int argc, char **argv)
{
    FILE *f;
    long sz;
    size_t rd;
    unsigned char *buf;   /* heap buffer holding the attacker-controlled
                            * raw STUN message bytes */
    pjstun_msg *msg;      /* heap-allocated so the attr[16] overrun lands
                            * in ASAN's heap-buffer-overflow detector */
    pj_status_t rc;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    f = fopen(argv[1], "rb");
    if (f == NULL) {
        perror("fopen");
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
    sz = ftell(f);
    if (sz < 0) { fclose(f); return 1; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

    /* Attacker-controlled raw STUN message, HEAP-allocated so ASAN guards
     * exactly the bytes pjstun_parse_msg() is entitled to read as `buf`. */
    buf = (unsigned char *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (buf == NULL) { fclose(f); return 1; }
    rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    /* msg->attr[PJSTUN_MAX_ATTR] is the object the bug overruns -- heap
     * allocate it (not zero-padded/oversized) so the 17th-attribute write
     * lands exactly one slot past the allocation. */
    msg = (pjstun_msg *)malloc(sizeof(pjstun_msg));
    if (msg == NULL) { free(buf); return 1; }
    memset(msg, 0, sizeof(*msg));

    /* Exactly the real call site: pjstun_parse_msg(buf, buf_len, msg) as
     * used throughout stun_simple_client.c on a just-received UDP
     * datagram. */
    rc = pjstun_parse_msg(buf, (pj_size_t)rd, msg);
    fprintf(stderr, "rc=%d attr_count=%d\n", rc, msg->attr_count);

    free(msg);
    free(buf);
    return 0;
}

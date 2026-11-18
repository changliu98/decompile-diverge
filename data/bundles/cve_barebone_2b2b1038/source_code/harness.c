/* cve_barebone direct-call harness for cve_2b2b1038 (tcpdump)
 * Target: vqp_print  (print-vqp.c -- Cisco VLAN Query Protocol printer)
 * Bug class: missing bounds check before reading the VQP object TLV header
 * -> heap-buffer-overflow READ (CWE-125).
 *
 * See the top-of-file comment in gen_dc_cve_2b2b1038.py for the full root-
 * cause analysis (fix commit 3b36ec4e713dea9266db11975066c425aa669b6c).
 * Summary: the object loop
 *     while (nitems > 0 && tlen > 0) {
 *         vqp_obj_tlv = (const struct vqp_obj_tlv_t *)tptr;
 *         vqp_obj_type = EXTRACT_32BITS(vqp_obj_tlv->obj_type);
 *         vqp_obj_len  = EXTRACT_16BITS(vqp_obj_tlv->obj_length);
 * reads a full 6-byte TLV header (4-byte obj_type + 2-byte obj_length)
 * completely unchecked -- only the LATER object *payload* gets an
 * ND_TCHECK2. A packet whose captured length ends 1..5 bytes past the
 * 8-byte common header (tlen in {1..5}, nitems>=1) makes EXTRACT_32BITS (or
 * EXTRACT_16BITS, if tlen==4) read straight off the end of the heap buffer.
 *
 * Everything above vqp_print's verbatim body is the minimal-but-real subset
 * of tcpdump's netdissect.h / extract.h / print-vqp.c that its body (and its
 * real, self-contained callees tok2str/tok2strbuf, safeputs/safeputchar --
 * copied byte-for-byte from source_code/util-print.c) actually reference --
 * real field/macro/struct/function names throughout, no invented
 * placeholders. ipaddr_string/etheraddr_string/print_unknown_data are
 * INCIDENTAL callees (only reached AFTER the object's declared length has
 * already passed ND_TCHECK2, never on the crash path itself) and are
 * minimal faithful stand-ins, same pattern as the existing pimv2_print
 * (cve_0a9f0f17) harness in this corpus.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* ---------------------------------------------------------------------
 * Minimal-but-real base types (BSD-style aliases tcpdump's headers use
 * throughout; real names, from sys/types.h in the real build).
 * --------------------------------------------------------------------- */
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

/* ---------------------------------------------------------------------
 * extract.h (verbatim): UNALIGNED_OK attribute + EXTRACT_16BITS /
 * EXTRACT_32BITS, native-unaligned-load path (LBL_ALIGN is NOT defined on
 * the real x86_64 build -- matches the same branch the sibling pimv2_print
 * (cve_0a9f0f17) harness in this corpus confirmed via its own crash line).
 * --------------------------------------------------------------------- */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif defined(__has_attribute)
# if __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
# else
#define UNALIGNED_OK
# endif
#else
#define UNALIGNED_OK
#endif

static inline uint16_t UNALIGNED_OK
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* ---------------------------------------------------------------------
 * netdissect.h (verbatim subset): struct tok, struct netdissect_options
 * (trimmed to the fields vqp_print's call graph actually touches:
 * ndo_vflag, ndo_snapend, ndo_printf -- real field names, real types), and
 * the ND_TCHECK / ND_TCHECK2 / ND_PRINT / ND_ISPRINT bounds macros (copied
 * verbatim from netdissect.h).
 * --------------------------------------------------------------------- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;			/* verbosity level */
	const u_char *ndo_snapend;	/* one past the last captured byte */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF
#define ND_ISPRINT(c)	((c) >= 0x20 && (c) <= 0x7E)

/* ---------------------------------------------------------------------
 * print-vqp.c (verbatim): VQP_* constants, struct vqp_common_header_t /
 * struct vqp_obj_tlv_t, and the three `struct tok` tables vqp_print
 * references by name -- all copied byte-for-byte from source_code/
 * print-vqp.c so the verbatim target function compiles against the exact
 * real names/layout.
 * --------------------------------------------------------------------- */
#define VQP_VERSION            		1
#define VQP_EXTRACT_VERSION(x) ((x)&0xFF)

struct vqp_common_header_t {
    uint8_t version;
    uint8_t msg_type;
    uint8_t error_code;
    uint8_t nitems;
    uint8_t sequence[4];
};

struct vqp_obj_tlv_t {
    uint8_t obj_type[4];
    uint8_t obj_length[2];
};

#define VQP_OBJ_REQ_JOIN_PORT  0x01
#define VQP_OBJ_RESP_VLAN      0x02
#define VQP_OBJ_REQ_RECONFIRM  0x03
#define VQP_OBJ_RESP_RECONFIRM 0x04

static const struct tok vqp_msg_type_values[] = {
    { VQP_OBJ_REQ_JOIN_PORT, "Request, Join Port"},
    { VQP_OBJ_RESP_VLAN, "Response, VLAN"},
    { VQP_OBJ_REQ_RECONFIRM, "Request, Reconfirm"},
    { VQP_OBJ_RESP_RECONFIRM, "Response, Reconfirm"},
    { 0, NULL}
};

static const struct tok vqp_error_code_values[] = {
    { 0x00, "No error"},
    { 0x03, "Access denied"},
    { 0x04, "Shutdown port"},
    { 0x05, "Wrong VTP domain"},
    { 0, NULL}
};

#define VQP_OBJ_IP_ADDRESS    0x0c01
#define VQP_OBJ_PORT_NAME     0x0c02
#define VQP_OBJ_VLAN_NAME     0x0c03
#define VQP_OBJ_VTP_DOMAIN    0x0c04
#define VQP_OBJ_ETHERNET_PKT  0x0c05
#define VQP_OBJ_MAC_NULL      0x0c06
#define VQP_OBJ_MAC_ADDRESS   0x0c08

static const struct tok vqp_obj_values[] = {
    { VQP_OBJ_IP_ADDRESS, "Client IP Address" },
    { VQP_OBJ_PORT_NAME, "Port Name" },
    { VQP_OBJ_VLAN_NAME, "VLAN Name" },
    { VQP_OBJ_VTP_DOMAIN, "VTP Domain" },
    { VQP_OBJ_ETHERNET_PKT, "Ethernet Packet" },
    { VQP_OBJ_MAC_NULL, "MAC Null" },
    { VQP_OBJ_MAC_ADDRESS, "MAC Address" },
    { 0, NULL}
};

/* ---------------------------------------------------------------------
 * util-print.c (VERBATIM): tok2strbuf/tok2str and safeputs/safeputchar,
 * copied byte-for-byte -- both are fully self-contained (only need
 * struct tok / TOKBUFSIZE / ND_PRINT / ND_ISPRINT, all defined above) and
 * ARE reachable from vqp_print's own body, so they are real callees, not
 * stand-ins.
 * --------------------------------------------------------------------- */
#define TOKBUFSIZE 128

const char *
tok2strbuf(register const struct tok *lp, register const char *fmt,
	   register u_int v, char *buf, size_t bufsize)
{
	if (lp != NULL) {
		while (lp->s != NULL) {
			if (lp->v == v)
				return (lp->s);
			++lp;
		}
	}
	if (fmt == NULL)
		fmt = "#%d";

	(void)snprintf(buf, bufsize, fmt, v);
	return (const char *)buf;
}

const char *
tok2str(register const struct tok *lp, register const char *fmt,
	register u_int v)
{
	static char buf[4][TOKBUFSIZE];
	static int idx = 0;
	char *ret;

	ret = buf[idx];
	idx = (idx+1) & 3;
	return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

void
safeputchar(netdissect_options *ndo,
            const u_char c)
{
	ND_PRINT((ndo, (c < 0x80 && ND_ISPRINT(c)) ? "%c" : "\\0x%02x", c));
}

void
safeputs(netdissect_options *ndo,
         const u_char *s, const u_int maxlen)
{
	u_int idx = 0;

	while (idx < maxlen && *s) {
		safeputchar(ndo, *s);
		idx++;
		s++;
	}
}

/* ---------------------------------------------------------------------
 * Simplified-but-safe stand-ins for vqp_print's INCIDENTAL callees --
 * every call site is reached only AFTER `ND_TCHECK2(*tptr, vqp_obj_len)`
 * has already validated the bytes these would read, so a stub that never
 * dereferences its pointer argument is a strictly-safe (never a wrong-
 * CWE/false-positive source) faithful stand-in, same pattern as the
 * sibling pimv2_print (cve_0a9f0f17) harness in this corpus. Real
 * signatures, from addrtoname.h / util-print.c.
 * --------------------------------------------------------------------- */
static const char *
ipaddr_string(netdissect_options *ndo, const void *p)
{
	(void)ndo; (void)p;
	return "0.0.0.0";
}

static const char *
etheraddr_string(netdissect_options *ndo, const u_char *ep)
{
	(void)ndo; (void)ep;
	return "00:00:00:00:00:00";
}

static int
print_unknown_data(netdissect_options *ndo, const u_char *cp, const char *ident, int len)
{
	(void)ndo; (void)cp; (void)ident; (void)len;
	return 1;
}

/* ---------------------------------------------------------------------
 * TARGET FUNCTION -- VERBATIM copy of target/original_function.c
 * (the VULNERABLE, pre-fix body). Do not modify logic, names, or
 * signature.
 * --------------------------------------------------------------------- */

void
vqp_print(netdissect_options *ndo, register const u_char *pptr, register u_int len)
{
    const struct vqp_common_header_t *vqp_common_header;
    const struct vqp_obj_tlv_t *vqp_obj_tlv;

    const u_char *tptr;
    uint16_t vqp_obj_len;
    uint32_t vqp_obj_type;
    int tlen;
    uint8_t nitems;

    tptr=pptr;
    tlen = len;
    vqp_common_header = (const struct vqp_common_header_t *)pptr;
    ND_TCHECK(*vqp_common_header);

    /*
     * Sanity checking of the header.
     */
    if (VQP_EXTRACT_VERSION(vqp_common_header->version) != VQP_VERSION) {
	ND_PRINT((ndo, "VQP version %u packet not supported",
               VQP_EXTRACT_VERSION(vqp_common_header->version)));
	return;
    }

    /* in non-verbose mode just lets print the basic Message Type */
    if (ndo->ndo_vflag < 1) {
        ND_PRINT((ndo, "VQPv%u %s Message, error-code %s (%u), length %u",
               VQP_EXTRACT_VERSION(vqp_common_header->version),
               tok2str(vqp_msg_type_values, "unknown (%u)",vqp_common_header->msg_type),
               tok2str(vqp_error_code_values, "unknown (%u)",vqp_common_header->error_code),
	       vqp_common_header->error_code,
               len));
        return;
    }

    /* ok they seem to want to know everything - lets fully decode it */
    nitems = vqp_common_header->nitems;
    ND_PRINT((ndo, "\n\tVQPv%u, %s Message, error-code %s (%u), seq 0x%08x, items %u, length %u",
           VQP_EXTRACT_VERSION(vqp_common_header->version),
	   tok2str(vqp_msg_type_values, "unknown (%u)",vqp_common_header->msg_type),
	   tok2str(vqp_error_code_values, "unknown (%u)",vqp_common_header->error_code),
	   vqp_common_header->error_code,
           EXTRACT_32BITS(&vqp_common_header->sequence),
           nitems,
           len));

    /* skip VQP Common header */
    tptr+=sizeof(const struct vqp_common_header_t);
    tlen-=sizeof(const struct vqp_common_header_t);

    while (nitems > 0 && tlen > 0) {

        vqp_obj_tlv = (const struct vqp_obj_tlv_t *)tptr;
        vqp_obj_type = EXTRACT_32BITS(vqp_obj_tlv->obj_type);
        vqp_obj_len = EXTRACT_16BITS(vqp_obj_tlv->obj_length);
        tptr+=sizeof(struct vqp_obj_tlv_t);
        tlen-=sizeof(struct vqp_obj_tlv_t);

        ND_PRINT((ndo, "\n\t  %s Object (0x%08x), length %u, value: ",
               tok2str(vqp_obj_values, "Unknown", vqp_obj_type),
               vqp_obj_type, vqp_obj_len));

        /* basic sanity check */
        if (vqp_obj_type == 0 || vqp_obj_len ==0) {
            return;
        }

        /* did we capture enough for fully decoding the object ? */
        ND_TCHECK2(*tptr, vqp_obj_len);

        switch(vqp_obj_type) {
	case VQP_OBJ_IP_ADDRESS:
            ND_PRINT((ndo, "%s (0x%08x)", ipaddr_string(ndo, tptr), EXTRACT_32BITS(tptr)));
            break;
            /* those objects have similar semantics - fall through */
        case VQP_OBJ_PORT_NAME:
	case VQP_OBJ_VLAN_NAME:
	case VQP_OBJ_VTP_DOMAIN:
	case VQP_OBJ_ETHERNET_PKT:
            safeputs(ndo, tptr, vqp_obj_len);
            break;
            /* those objects have similar semantics - fall through */
	case VQP_OBJ_MAC_ADDRESS:
	case VQP_OBJ_MAC_NULL:
	      ND_PRINT((ndo, "%s", etheraddr_string(ndo, tptr)));
              break;
        default:
            if (ndo->ndo_vflag <= 1)
                print_unknown_data(ndo,tptr, "\n\t    ", vqp_obj_len);
            break;
        }
	tptr += vqp_obj_len;
	tlen -= vqp_obj_len;
	nitems--;
    }
    return;
trunc:
    ND_PRINT((ndo, "\n\t[|VQP]"));
}
/* ---------------------------------------------------------------------
 * ndo_printf implementation: matches the real signature
 * `int (*ndo_printf)(netdissect_options *, const char *fmt, ...)`.
 * --------------------------------------------------------------------- */
static int
harness_ndo_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
}

/* ---------------------------------------------------------------------
 * Direct-call driver: read argv[1] into a HEAP buffer (the attacker-
 * controlled captured packet bytes, starting at the VQP common header),
 * mirror the real caller setting ndo_snapend = one-past-the-end of what
 * was actually captured, force ndo_vflag=1 (the "-v" flag: the upstream
 * regression test for this exact bug, tests/vqp-oobr, is itself invoked
 * with "-v -c1" -- verbose mode is required to reach the vulnerable
 * object loop at all), and call vqp_print() ONCE, directly. ndo_snapend
 * is bound to EXACTLY the malloc'd+read region so an out-of-bounds parse
 * lands in the ASAN redzone right after the heap allocation.
 * --------------------------------------------------------------------- */
int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	fseek(f, 0, SEEK_END);
	long sz = ftell(f);
	if (sz < 0)
		sz = 0;
	fseek(f, 0, SEEK_SET);

	size_t alloc_sz = (size_t)sz > 0 ? (size_t)sz : 1;
	u_char *data = (u_char *)malloc(alloc_sz);
	if (!data) {
		fclose(f);
		return 1;
	}
	size_t got = sz > 0 ? fread(data, 1, (size_t)sz, f) : 0;
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_vflag = 1;
	ndo.ndo_printf = harness_ndo_printf;
	ndo.ndo_snapend = data + got;   /* exactly the captured/heap region */

	vqp_print(&ndo, data, (u_int)got);

	free(data);
	return 0;
}

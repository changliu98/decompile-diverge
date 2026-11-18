/*
 * Direct-call crash harness -- CVE-2017-13027 (tcpdump, print-lldp.c)
 * Bundle: cve_99d4ef74 | Target: lldp_mgmt_addr_tlv_print | CWE-125 heap-buffer-overflow READ
 *
 * lldp_mgmt_addr_tlv_print() parses an LLDP "Management Address" TLV: 1-byte
 * mgmt_addr_len + address bytes, 5-byte interface-numbering field, then an
 * OPTIONAL trailing OID (1-byte oid_len + oid_len data bytes). The OID guard is:
 *
 *     if (tlen) {
 *         oid_len = *tptr;
 *         if (tlen < oid_len) {          <-- BUG: should be `tlen < 1U + oid_len`
 *             return 0;
 *         }
 *         if (oid_len) {
 *             ND_PRINT((ndo, "\n\t  OID length %u", oid_len));
 *             safeputs(ndo, tptr + 1, oid_len);   <-- reads oid_len bytes starting
 *         }                                            at tptr+1, i.e. needs
 *     }                                                1+oid_len bytes from tptr,
 *                                                       but only tlen>=oid_len is
 *                                                       checked.
 *
 * `tlen` counts the bytes available FROM tptr (the oid_len byte itself)
 * inclusive, so reading `oid_len` bytes starting at tptr+1 needs
 * `tlen >= oid_len + 1`. The pre-fix check only requires `tlen >= oid_len`,
 * so whenever tlen == oid_len exactly, safeputs() walks 1 byte past the end
 * of the buffer while scanning for the NUL terminator it will never find
 * (the byte at tptr[oid_len] is the first byte beyond the TLV/allocation).
 * The upstream fix (a77ff09c46560bc895dea11dc9fe643486b056ac) changes the
 * check to `tlen < 1U + oid_len`. This is the real CVE-2017-13027 bug and
 * matches the upstream regression test tests/lldp_mgmt_addr_tlv_asan.{pcap,out}.
 *
 * This harness reproduces the SAME site/class fault -- inside
 * lldp_mgmt_addr_tlv_print, via its real (verbatim) crash-path callee
 * safeputs() -- by calling lldp_mgmt_addr_tlv_print() directly on a HEAP
 * buffer malloc'd to the exact size of the attacker-controlled input, with
 * no dependency on lldp_print / the rest of tcpdump's protocol stack.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>   /* u_char, u_int: real BSD types tcpdump relies on */

/* ------------------------------------------------------------------ */
/* Minimal but FAITHFUL type/macro defs, real names, copied verbatim  */
/* from the bundle's source_code/ headers where noted.                */
/* ------------------------------------------------------------------ */

/* netdissect.h: struct tok, verbatim */
struct tok {
    u_int v;		/* value */
    const char *s;	/* string */
};

/* netdissect.h: netdissect_options, trimmed to the single field
 * lldp_mgmt_addr_tlv_print actually touches (through ND_PRINT ->
 * ndo->ndo_printf); real field name + real function-pointer signature. */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h, verbatim */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* netdissect.h, verbatim -- used by safeputchar() (a real crash-path-adjacent
 * callee of safeputs(), copied verbatim below). */
#define ND_ISPRINT(c)	((c) >= 0x20 && (c) <= 0x7E)

/* extract.h, EXTRACT_32BITS copied VERBATIM (byte-at-a-time portable form).
 * Used directly inside lldp_mgmt_addr_tlv_print's own body for the interface
 * numbering field; that read is correctly bounds-checked (LLDP_INTF_NUM_LEN)
 * and is NOT the fault site, but the macro is real and copied verbatim. */
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* print-lldp.c, verbatim */
#define LLDP_INTF_NUM_LEN                  5

#define LLDP_INTF_NUMB_IFX_SUBTYPE         2
#define LLDP_INTF_NUMB_SYSPORT_SUBTYPE     3

static const struct tok lldp_intf_numb_subtype_values[] = {
    { LLDP_INTF_NUMB_IFX_SUBTYPE, "Interface Index" },
    { LLDP_INTF_NUMB_SYSPORT_SUBTYPE, "System Port Number" },
    { 0, NULL}
};

/* util-print.c, verbatim -- lldp_mgmt_addr_tlv_print calls tok2str() directly. */
#define TOKBUFSIZE 128

const char *
tok2strbuf(const struct tok *lp, const char *fmt, u_int v, char *buf, size_t bufsize)
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
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	static char buf[4][TOKBUFSIZE];
	static int idx = 0;
	char *ret;

	ret = buf[idx];
	idx = (idx + 1) & 3;
	return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

/* util-print.c, verbatim -- safeputs() IS the real crash-path callee: the
 * unchecked `*s` dereference inside its while-condition is the fault site
 * that the off-by-one in lldp_mgmt_addr_tlv_print's guard walks 1 byte past
 * the end of the caller-supplied buffer. safeputchar() is copied verbatim
 * too (it is called for every in-bounds byte before the OOB one is hit; it
 * never dereferences attacker memory itself, only a value already read by
 * safeputs()). */
void
safeputchar(netdissect_options *ndo, const u_char c)
{
	ND_PRINT((ndo, (c < 0x80 && ND_ISPRINT(c)) ? "%c" : "\\0x%02x", c));
}

void
safeputs(netdissect_options *ndo, const u_char *s, const u_int maxlen)
{
	u_int idx = 0;

	while (idx < maxlen && *s) {
		safeputchar(ndo, *s);
		idx++;
		s++;
	}
}

/* print-lldp.c: lldp_network_addr_print() is a real, but INCIDENTAL, callee
 * -- lldp_mgmt_addr_tlv_print only needs it to return non-NULL (mgmt_addr_len
 * >= 1) to proceed past it; it is never on the OOB-read fault path (that is
 * entirely in the OID branch, reached only after this call returns). The
 * real implementation additionally pulls in getname()/getname6()/
 * etheraddr_string()/af_values[]/BUFSIZE (hostname-resolution machinery
 * from addrtoname.c) that are orthogonal to the bug, so it gets a minimal
 * faithful stand-in matching the real prototype and the real NULL/non-NULL
 * contract (`if (len < 1) return NULL;` is copied verbatim from the real
 * function; the body is otherwise a stub that never touches attacker memory
 * beyond that single bounds-checked byte, so it can never introduce a false
 * crash of its own). */
static char *
lldp_network_addr_print(netdissect_options *ndo, const u_char *tptr, u_int len)
{
    static char buf[128];
    (void)ndo;

    if (len < 1)
        return NULL;
    snprintf(buf, sizeof(buf), "AFI stub (%u)", (unsigned)*tptr);
    return buf;
}

/* ------------------------------------------------------------------ */
/* TARGET FUNCTION -- verbatim from target/original_function.c        */
/* ------------------------------------------------------------------ */

static int
lldp_mgmt_addr_tlv_print(netdissect_options *ndo,
                         const u_char *pptr, u_int len)
{
    uint8_t mgmt_addr_len, intf_num_subtype, oid_len;
    const u_char *tptr;
    u_int tlen;
    char *mgmt_addr;

    tlen = len;
    tptr = pptr;

    if (tlen < 1) {
        return 0;
    }
    mgmt_addr_len = *tptr++;
    tlen--;

    if (tlen < mgmt_addr_len) {
        return 0;
    }

    mgmt_addr = lldp_network_addr_print(ndo, tptr, mgmt_addr_len);
    if (mgmt_addr == NULL) {
        return 0;
    }
    ND_PRINT((ndo, "\n\t  Management Address length %u, %s",
           mgmt_addr_len, mgmt_addr));
    tptr += mgmt_addr_len;
    tlen -= mgmt_addr_len;

    if (tlen < LLDP_INTF_NUM_LEN) {
        return 0;
    }

    intf_num_subtype = *tptr;
    ND_PRINT((ndo, "\n\t  %s Interface Numbering (%u): %u",
           tok2str(lldp_intf_numb_subtype_values, "Unknown", intf_num_subtype),
           intf_num_subtype,
           EXTRACT_32BITS(tptr + 1)));

    tptr += LLDP_INTF_NUM_LEN;
    tlen -= LLDP_INTF_NUM_LEN;

    /*
     * The OID is optional.
     */
    if (tlen) {
        oid_len = *tptr;

        if (tlen < oid_len) {
            return 0;
        }
        if (oid_len) {
            ND_PRINT((ndo, "\n\t  OID length %u", oid_len));
            safeputs(ndo, tptr + 1, oid_len);
        }
    }

    return 1;
}

/* ------------------------------------------------------------------ */
/* Harness main()                                                     */
/* ------------------------------------------------------------------ */

static int
fake_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0;
}

int
main(int argc, char **argv)
{
	FILE *f;
	long sz;
	u_char *buf;
	netdissect_options ndo;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}
	f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 1;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	sz = ftell(f);
	if (sz < 0) sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	buf = NULL;
	if (sz > 0) {
		/* HEAP buffer, sized EXACTLY to the attacker-controlled input,
		 * so an ASAN redzone sits immediately past the last real byte. */
		buf = (u_char *)malloc((size_t)sz);
		if (!buf) { fclose(f); return 1; }
		if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) {
			free(buf);
			fclose(f);
			return 1;
		}
	}
	fclose(f);

	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = fake_printf;

	lldp_mgmt_addr_tlv_print(&ndo, buf, (u_int)sz);

	free(buf);
	return 0;
}

/*
 * Direct-call crash harness -- CVE-2017-13042 (tcpdump, print-hncp.c)
 * Bundle: cve_281cb7f7 | Target: dhcpv6_print | CWE-125 heap-buffer-overflow READ
 *
 * dhcpv6_print() walks a caller-supplied `length`-byte TLV stream at `cp`.
 * Its loop condition is only `while (i < length)`: before reading the 4-byte
 * TLV header (type+optlen) via EXTRACT_16BITS() it never checks that at
 * least 4 bytes remain before `cp + length`. So whenever fewer than 4 bytes
 * are left, EXTRACT_16BITS() still unconditionally dereferences 2 bytes at
 * `cp+i` and 2 more at `cp+i+2`, walking past the end of the buffer if the
 * allocation backing `cp` is exactly `length` bytes long (as the real
 * tcpdump capture buffer is once ASAN owns it). That is the original
 * ARVO/OSS-Fuzz crash: dedup_token "EXTRACT_16BITS--dhcpv6_print--
 * hncp_print_rec" (heap-buffer-overflow READ inside the EXTRACT_16BITS
 * inline helper, called from dhcpv6_print).
 *
 * This harness reproduces the SAME class/site fault -- inside dhcpv6_print,
 * via EXTRACT_16BITS -- by calling dhcpv6_print() directly on a HEAP buffer
 * malloc'd to the exact size of the attacker-controlled input, with no
 * dependency on hncp_print_rec / the rest of tcpdump.
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

/* netdissect.h: struct tok */
struct tok {
    u_int v;
    const char *s;
};

/* netdissect.h: netdissect_options, trimmed to the single field
 * dhcpv6_print actually touches (through ND_PRINT -> ndo->ndo_printf);
 * real field name + real function-pointer signature. */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h, verbatim */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* extract.h, EXTRACT_16BITS copied VERBATIM (byte-at-a-time form) -- this
 * is the exact macro whose unchecked 2-byte read is the fault site. */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))

/* util-print.c, verbatim (not on the fault path, but real: dhcpv6_print
 * calls tok2str(dh6opt_str, ...) directly and references istr[]). */
#define TOKBUFSIZE 128
const char istr[] = " (invalid)";

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

/* addrtoname.h: real macro name + real extern prototypes. dhcpv6_print
 * only reaches these from the DNS_SERVERS/SNTP_SERVERS/DOMAIN_LIST cases,
 * which are never the crash site here (the fault fires on the TLV-header
 * read at loop top, before/independent of the switch). Stub bodies match
 * the real prototypes; they deliberately touch no attacker memory so they
 * can never introduce a false crash of their own. */
#define ip6addr_string(ndo, p) getname6(ndo, (const u_char *)(p))
const char *
getname6(netdissect_options *ndo, const u_char *p)
{
	(void)ndo; (void)p;
	return "::";
}

const u_char *
ns_nprint(netdissect_options *ndo, const u_char *cp, const u_char *bp)
{
	(void)ndo; (void)bp;
	return cp + 1;   /* always advances -> DOMAIN_LIST loop always terminates */
}

/* print-hncp.c, verbatim (the dh6opt_* bits dhcpv6_print references) */
#define DH6OPT_DNS_SERVERS 23   /* RFC3646 */
#define DH6OPT_DOMAIN_LIST 24   /* RFC3646 */
#define DH6OPT_SNTP_SERVERS 31  /* RFC4075 */

static const struct tok dh6opt_str[] = {
    { DH6OPT_DNS_SERVERS,  "DNS-server" },
    { DH6OPT_DOMAIN_LIST,  "DNS-search-list" },
    { DH6OPT_SNTP_SERVERS, "SNTP-servers" },
    { 0, NULL }
};

/* ------------------------------------------------------------------ */
/* TARGET FUNCTION -- verbatim from target/original_function.c        */
/* ------------------------------------------------------------------ */

static int
dhcpv6_print(netdissect_options *ndo,
             const u_char *cp, u_int length, int indent)
{
    u_int i, t;
    const u_char *tlv, *value;
    uint16_t type, optlen;

    i = 0;
    while (i < length) {
        tlv = cp + i;
        type = EXTRACT_16BITS(tlv);
        optlen = EXTRACT_16BITS(tlv + 2);
        value = tlv + 4;

        ND_PRINT((ndo, "\n"));
        for (t = indent; t > 0; t--)
            ND_PRINT((ndo, "\t"));

        ND_PRINT((ndo, "%s", tok2str(dh6opt_str, "Unknown", type)));
        ND_PRINT((ndo," (%u)", optlen + 4 ));

        switch (type) {
            case DH6OPT_DNS_SERVERS:
            case DH6OPT_SNTP_SERVERS: {
                if (optlen % 16 != 0) {
                    ND_PRINT((ndo, " %s", istr));
                    return -1;
                }
                for (t = 0; t < optlen; t += 16)
                    ND_PRINT((ndo, " %s", ip6addr_string(ndo, value + t)));
            }
                break;
            case DH6OPT_DOMAIN_LIST: {
                const u_char *tp = value;
                while (tp < value + optlen) {
                    ND_PRINT((ndo, " "));
                    if ((tp = ns_nprint(ndo, tp, value + optlen)) == NULL)
                        return -1;
                }
            }
                break;
        }

        i += 4 + optlen;
    }
    return 0;
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

	dhcpv6_print(&ndo, buf, (u_int)sz, 1);

	free(buf);
	return 0;
}

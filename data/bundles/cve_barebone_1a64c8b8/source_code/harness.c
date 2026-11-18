/*
 * Direct-call crash harness for cve_1a64c8b8 (CVE-2017-13044, tcpdump).
 *
 * TARGET FUNCTION: dhcpv4_print (print-hncp.c) -- embedded VERBATIM below,
 * byte-for-byte from dataset/cve_1a64c8b8/target/original_function.c.
 *
 * The frozen baseline dedup_token is
 *   "getname--dhcpv4_print--hncp_print_rec"
 * i.e. the actual fault is a heap-buffer-overflow READ inside getname()
 * (addrtoname.c:245, `memcpy(&addr, ap, sizeof(addr))`), reached from
 * dhcpv4_print() via the `ipaddr_string(ndo, value + t)` calls in the
 * DH4OPT_DNS_SERVERS / DH4OPT_NTP_SERVERS case. dhcpv4_print() trusts the
 * attacker-controlled `optlen` byte without checking it against the bounds
 * of the captured buffer -- if optlen claims more 4-byte IP addresses than
 * are actually present, getname() reads 4 bytes past the end of the heap
 * buffer.  getname() (its real callee, where the fault physically occurs),
 * plus its own small real callees (newhnamemem/intoa) and dhcpv4_print's
 * other direct callees (tok2str/tok2strbuf), are embedded verbatim too so
 * the target function executes with NO stubbed-out logic on its crash path.
 * ns_nprint() (the DH4OPT_DOMAIN_SEARCH helper) is NOT on the crash path
 * used by this harness's corpus; a link-only stub is provided purely to
 * satisfy the reference in the verbatim switch statement.
 *
 * main() reads the whole input file into a HEAP buffer (malloc) and calls
 * dhcpv4_print(ndo, buf, filesize, 0) directly -- ONE call, no pcap/UDP/IP
 * parsing, no dependency on the rest of the tcpdump source tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---------------- netdissect.h (minimal, real field/macro names) ---------------- */

typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_nflag;		/* leave addresses as numbers */
	int ndo_Nflag;		/* remove domains from printed host names */

	/* pointer to function to do regular output */
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
	/* pointer to function to output errors */
	void (*ndo_error)(netdissect_options *, const char *fmt, ...);
};

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

#define NTOHL(x)	(x) = ntohl(x)

/* ---------------- addrtoname.h / addrtoname.c (verbatim real callees) ---------------- */

#define HASHNAMESIZE 4096

struct hnamemem {
	uint32_t addr;
	const char *name;
	struct hnamemem *nxt;
};

static struct hnamemem hnametable[HASHNAMESIZE];

static uint32_t f_netmask;
static uint32_t f_localnet;

struct hnamemem *newhnamemem(netdissect_options *);
const char *intoa(uint32_t);
const char *getname(netdissect_options *, const u_char *);

#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))

/* verbatim from addrtoname.c */
const char *
intoa(uint32_t addr)
{
	register char *cp;
	register u_int byte;
	register int n;
	static char buf[sizeof(".xxx.xxx.xxx.xxx")];

	NTOHL(addr);
	cp = buf + sizeof(buf);
	*--cp = '\0';

	n = 4;
	do {
		byte = addr & 0xff;
		*--cp = byte % 10 + '0';
		byte /= 10;
		if (byte > 0) {
			*--cp = byte % 10 + '0';
			byte /= 10;
			if (byte > 0)
				*--cp = byte + '0';
		}
		*--cp = '.';
		addr >>= 8;
	} while (--n > 0);

	return cp + 1;
}

/* verbatim from addrtoname.c */
struct hnamemem *
newhnamemem(netdissect_options *ndo)
{
	register struct hnamemem *p;
	static struct hnamemem *ptr = NULL;
	static u_int num = 0;

	if (num  <= 0) {
		num = 64;
		ptr = (struct hnamemem *)calloc(num, sizeof (*ptr));
		if (ptr == NULL)
			(*ndo->ndo_error)(ndo, "newhnamemem: calloc");
	}
	--num;
	p = ptr++;
	return (p);
}

/*
 * verbatim from addrtoname.c (the real crash site: line 245's memcpy).
 * HAVE_CASPER is not defined in this build (matches upstream default), so
 * the #ifdef HAVE_CASPER branch that the original file guards is omitted
 * here exactly as the preprocessor would omit it; the gethostbyaddr() path
 * is the real fallback used on a non-Casper build.
 */
const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	register struct hostent *hp;
	uint32_t addr;
	struct hnamemem *p;

	memcpy(&addr, ap, sizeof(addr));
	p = &hnametable[addr & (HASHNAMESIZE-1)];
	for (; p->nxt; p = p->nxt) {
		if (p->addr == addr)
			return (p->name);
	}
	p->addr = addr;
	p->nxt = newhnamemem(ndo);

	/*
	 * Print names unless:
	 *	(1) -n was given.
	 *      (2) Address is foreign and -f was given. (If -f was not
	 *	    given, f_netmask and f_localnet are 0 and the test
	 *	    evaluates to true)
	 */
	if (!ndo->ndo_nflag &&
	    (addr & f_netmask) == f_localnet) {
		hp = gethostbyaddr((char *)&addr, 4, AF_INET);
		if (hp) {
			char *dotp;

			p->name = strdup(hp->h_name);
			if (p->name == NULL)
				(*ndo->ndo_error)(ndo,
						  "getname: strdup(hp->h_name)");
			if (ndo->ndo_Nflag) {
				/* Remove domain qualifications */
				dotp = strchr(p->name, '.');
				if (dotp)
					*dotp = '\0';
			}
			return (p->name);
		}
	}
	p->name = strdup(intoa(addr));
	if (p->name == NULL)
		(*ndo->ndo_error)(ndo, "getname: strdup(intoa(addr))");
	return (p->name);
}

/* ---------------- util-print.c (verbatim real callees of dhcpv4_print) ---------------- */

#define TOKBUFSIZE 128

/* verbatim from util-print.c */
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

/* verbatim from util-print.c */
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

/*
 * ns_nprint (print-domain.c) is referenced by dhcpv4_print's
 * DH4OPT_DOMAIN_SEARCH case but is NOT on this harness's crash path (no
 * corpus input takes that branch). Real signature (from netdissect.h),
 * link-only stub -- never exercised.
 */
const u_char *
ns_nprint(netdissect_options *ndo, register const u_char *cp, register const u_char *bp)
{
	(void)ndo; (void)bp;
	return cp;
}

/* ---------------- print-hncp.c (target function's own local decls) ---------------- */

#define DH4OPT_DNS_SERVERS 6     /* RFC2132 */
#define DH4OPT_NTP_SERVERS 42    /* RFC2132 */
#define DH4OPT_DOMAIN_SEARCH 119 /* RFC3397 */

static const struct tok dh4opt_str[] = {
    { DH4OPT_DNS_SERVERS, "DNS-server" },
    { DH4OPT_NTP_SERVERS, "NTP-server"},
    { DH4OPT_DOMAIN_SEARCH, "DNS-search" },
    { 0, NULL }
};

/* =====================================================================
 * TARGET FUNCTION -- VERBATIM from
 * dataset/cve_1a64c8b8/target/original_function.c. DO NOT EDIT.
 * ===================================================================== */
static int
dhcpv4_print(netdissect_options *ndo,
             const u_char *cp, u_int length, int indent)
{
    u_int i, t;
    const u_char *tlv, *value;
    uint8_t type, optlen;

    i = 0;
    while (i < length) {
        tlv = cp + i;
        type = (uint8_t)tlv[0];
        optlen = (uint8_t)tlv[1];
        value = tlv + 2;

        ND_PRINT((ndo, "\n"));
        for (t = indent; t > 0; t--)
            ND_PRINT((ndo, "\t"));

        ND_PRINT((ndo, "%s", tok2str(dh4opt_str, "Unknown", type)));
        ND_PRINT((ndo," (%u)", optlen + 2 ));

        switch (type) {
        case DH4OPT_DNS_SERVERS:
        case DH4OPT_NTP_SERVERS: {
            if (optlen < 4 || optlen % 4 != 0) {
                return -1;
            }
            for (t = 0; t < optlen; t += 4)
                ND_PRINT((ndo, " %s", ipaddr_string(ndo, value + t)));
        }
            break;
        case DH4OPT_DOMAIN_SEARCH: {
            const u_char *tp = value;
            while (tp < value + optlen) {
                ND_PRINT((ndo, " "));
                if ((tp = ns_nprint(ndo, tp, value + optlen)) == NULL)
                    return -1;
            }
        }
            break;
        }

        i += 2 + optlen;
    }
    return 0;
}
/* ===================================================================== */

/* ---------------- harness plumbing ---------------- */

static int
harness_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0; /* no-op output -- we only care about the crash, not the text */
}

static void
harness_error(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	fprintf(stderr, "ndo_error: %s\n", fmt);
	exit(1);
}

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
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 1; }
	rewind(f);

	/* Attacker-controlled bytes MUST live in a HEAP allocation, sized
	 * EXACTLY to the input, so ASAN's heap redzone catches any read
	 * that walks past it -- this is what makes the CWE-125
	 * heap-buffer-overflow reproducible. */
	u_char *buf = (u_char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 1; }
	size_t got = fread(buf, 1, (size_t)fsz, f);
	fclose(f);

	netdissect_options ndo_storage;
	memset(&ndo_storage, 0, sizeof(ndo_storage));
	netdissect_options *ndo = &ndo_storage;
	ndo->ndo_nflag = 1;   /* matches the real "-nn" run_template: skip DNS lookups */
	ndo->ndo_Nflag = 0;
	ndo->ndo_printf = harness_printf;
	ndo->ndo_error = harness_error;

	/* Direct call: the whole file IS the DHCPv4-options TLV blob that
	 * dhcpv4_print() walks (cp = buf, length = file size, indent = 0). */
	(void)dhcpv4_print(ndo, buf, (u_int)got, 0);

	free(buf);
	return 0;
}

/*
 * cve_f1d0c70f direct-call crash harness for tcpdump's ip_optprint()
 * (CVE-2017-13022 / CWE-125 heap-buffer-overflow READ).
 *
 * Crash path (case.json dedup_token "getname--ip_printroute--ip_optprint",
 * baseline "heap-buffer-overflow addrtoname.c:245 in getname"):
 *   ip_optprint() sees an IP RR/LSRR/SSRR option, ND_TCHECK2()s option_len
 *   bytes, then calls ip_printroute(cp, option_len). ip_printroute walks the
 *   recorded route in 4-byte strides
 *       for (len = 3; len < length; len += 4)
 *           ipaddr_string(ndo, &cp[len]);   // == getname(ndo, &cp[len])
 *   and getname() does an unchecked memcpy of 4 bytes from &cp[len]. When
 *   option_len is not congruent to 3 (mod 4), the final stride reads up to 3
 *   bytes past the option (past ND_TCHECK2's guarantee and past snapend =
 *   end of the captured packet buffer) -> heap READ overflow inside getname.
 *
 * Assembly of this file:
 *   (a) minimal libc includes,
 *   (b) the REAL tcpdump types/macros ip_optprint needs (struct tok,
 *       netdissect_options, ND_TTEST2/ND_TCHECK2/ND_TCHECK/ND_PRINT,
 *       EXTRACT_16BITS/EXTRACT_32BITS, the IPOPT_* codes) copied with their
 *       real names from source_code/{netdissect.h,extract.h,ip.h},
 *   (c) real callees: tok2str/tok2strbuf (verbatim util-print.c),
 *       ip_printroute + ip_printts (verbatim print-ip.c -- both are direct
 *       callees of ip_optprint), and getname (the faulting frame): a
 *       minimal FAITHFUL stand-in that performs the SAME unchecked 4-byte
 *       memcpy read from its pointer arg as addrtoname.c:245 -- the rest of
 *       real getname() (hostname hash table / DNS resolution) is never
 *       reached because the crash aborts at that first memcpy,
 *   (d) the TARGET ip_optprint() pasted byte-for-byte from
 *       target/original_function.c,
 *   (e) main(): read argv[1] into a HEAP buffer (malloc, so ASAN guards it),
 *       set ndo_snapend to the buffer's exact end (no padding -- the packet
 *       buffer's length IS the snapshot length, as in the real fuzz target),
 *       and call ip_optprint(ndo, buf, buflen) once.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* ---- real BSD scalar typedefs (normally from netdissect-stdinc.h) ---- */
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- struct tok, netdissect.h, verbatim ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

/*
 * netdissect_options, netdissect.h -- trimmed to the fields ip_optprint and
 * its in-file callees actually dereference (ndo_nflag, ndo_snapend,
 * ndo_printf). Real names/types; unused fields (the other ndo_*flag knobs,
 * ndo_error/ndo_warning/ndo_default_print, ndo_if_printer, ...) are omitted
 * rather than fabricated, since they would drag in pcap/if_printer typedefs
 * irrelevant to this bug.
 */
typedef struct netdissect_options netdissect_options;

struct netdissect_options {
	int ndo_nflag;			/* leave addresses as numbers */
	const u_char *ndo_snapend;	/* end of captured packet data */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- netdissect.h macros, verbatim ---- */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/*
 * extract.h, verbatim -- the byte-at-a-time unaligned form (no LBL_ALIGN),
 * safe on any target and used by ip_printts (EXTRACT_32BITS) and ip_optprint
 * (EXTRACT_16BITS).
 */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---- ip.h, verbatim (the IP option codes ip_optprint switches on) ---- */
#define	IPOPT_EOL		0		/* end of option list */
#define	IPOPT_NOP		1		/* no operation */
#define	IPOPT_RR		7		/* record packet route */
#define	IPOPT_TS		68		/* timestamp */
#define	IPOPT_RFC1393           82              /* traceroute RFC 1393 */
#define	IPOPT_SECURITY		130		/* provide s,c,h,tcc */
#define	IPOPT_LSRR		131		/* loose source route */
#define	IPOPT_SSRR		137		/* strict source route */
#define IPOPT_RA                148             /* router-alert, rfc2113 */

#define	IPOPT_TS_TSONLY		0		/* timestamps only */
#define	IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	IPOPT_TS_PRESPEC	3		/* specified modules only */

/* ---- util-print.c, verbatim ---- */
#define TOKBUFSIZE 128

const char *
tok2strbuf(const struct tok *lp, const char *fmt,
	   u_int v, char *buf, size_t bufsize)
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
	idx = (idx+1) & 3;
	return tok2strbuf(lp, fmt, v, ret, sizeof(buf[0]));
}

/*
 * addrtoname.h: ipaddr_string(ndo, p) -> getname(ndo, p). getname's real
 * body (addrtoname.c) resolves the address through a hostname hash table and
 * gethostbyaddr(); the ONLY part reached before the crash is its very first
 * statement, the unchecked 4-byte read
 *     memcpy(&addr, ap, sizeof(addr));      // addrtoname.c:245 -- THE fault
 * (the header even warns ap is "*NOT* necessarily part of the packet" so
 * ND_TCHECK cannot be used on it). This stand-in reproduces exactly that
 * 4-byte read from ap -- the faulting operation, in a frame named getname --
 * then returns a numeric string, matching the -n / numeric behaviour.
 */
#define ipaddr_string(ndo, p) getname(ndo, (const u_char *)(p))

__attribute__((noinline)) const char *
getname(netdissect_options *ndo, const u_char *ap)
{
	static char buf[INET_ADDRSTRLEN];
	struct in_addr in;
	(void)ndo;
	memcpy(&in, ap, sizeof(in));	/* addrtoname.c:245 -- unchecked read */
	return inet_ntop(AF_INET, &in, buf, sizeof(buf));
}

/* ==================================================================
 * VERBATIM real tcpdump source (source_code/print-ip.c):
 *   tstr, ip_option_values, and ip_optprint's two direct callees
 *   ip_printroute() and ip_printts(), followed (below) by
 *   target/original_function.c byte-for-byte (ip_optprint itself).
 * ================================================================== */
static const char tstr[] = "[|ip]";

static const struct tok ip_option_values[] = {
    { IPOPT_EOL, "EOL" },
    { IPOPT_NOP, "NOP" },
    { IPOPT_TS, "timestamp" },
    { IPOPT_SECURITY, "security" },
    { IPOPT_RR, "RR" },
    { IPOPT_SSRR, "SSRR" },
    { IPOPT_LSRR, "LSRR" },
    { IPOPT_RA, "RA" },
    { IPOPT_RFC1393, "traceroute" },
    { 0, NULL }
};

/*
 * print the recorded route in an IP RR, LSRR or SSRR option.
 */
static void
ip_printroute(netdissect_options *ndo,
              register const u_char *cp, u_int length)
{
	register u_int ptr;
	register u_int len;

	if (length < 3) {
		ND_PRINT((ndo, " [bad length %u]", length));
		return;
	}
	if ((length + 1) & 3)
		ND_PRINT((ndo, " [bad length %u]", length));
	ptr = cp[2] - 1;
	if (ptr < 3 || ((ptr + 1) & 3) || ptr > length + 1)
		ND_PRINT((ndo, " [bad ptr %u]", cp[2]));

	for (len = 3; len < length; len += 4) {
		ND_PRINT((ndo, " %s", ipaddr_string(ndo, &cp[len])));
		if (ptr > len)
			ND_PRINT((ndo, ","));
	}
}

static void
ip_printts(netdissect_options *ndo,
           register const u_char *cp, u_int length)
{
	register u_int ptr;
	register u_int len;
	int hoplen;
	const char *type;

	if (length < 4) {
		ND_PRINT((ndo, "[bad length %u]", length));
		return;
	}
	ND_PRINT((ndo, " TS{"));
	hoplen = ((cp[3]&0xF) != IPOPT_TS_TSONLY) ? 8 : 4;
	if ((length - 4) & (hoplen-1))
		ND_PRINT((ndo, "[bad length %u]", length));
	ptr = cp[2] - 1;
	len = 0;
	if (ptr < 4 || ((ptr - 4) & (hoplen-1)) || ptr > length + 1)
		ND_PRINT((ndo, "[bad ptr %u]", cp[2]));
	switch (cp[3]&0xF) {
	case IPOPT_TS_TSONLY:
		ND_PRINT((ndo, "TSONLY"));
		break;
	case IPOPT_TS_TSANDADDR:
		ND_PRINT((ndo, "TS+ADDR"));
		break;
	/*
	 * prespecified should really be 3, but some ones might send 2
	 * instead, and the IPOPT_TS_PRESPEC constant can apparently
	 * have both values, so we have to hard-code it here.
	 */

	case 2:
		ND_PRINT((ndo, "PRESPEC2.0"));
		break;
	case 3:			/* IPOPT_TS_PRESPEC */
		ND_PRINT((ndo, "PRESPEC"));
		break;
	default:
		ND_PRINT((ndo, "[bad ts type %d]", cp[3]&0xF));
		goto done;
	}

	type = " ";
	for (len = 4; len < length; len += hoplen) {
		if (ptr == len)
			type = " ^ ";
		ND_PRINT((ndo, "%s%d@%s", type, EXTRACT_32BITS(&cp[len+hoplen-4]),
		       hoplen!=8 ? "" : ipaddr_string(ndo, &cp[len])));
		type = " ";
	}

done:
	ND_PRINT((ndo, "%s", ptr == len ? " ^ " : ""));

	if (cp[3]>>4)
		ND_PRINT((ndo, " [%d hops not recorded]} ", cp[3]>>4));
	else
		ND_PRINT((ndo, "}"));
}

/* ---- target/original_function.c (ip_optprint), byte-for-byte ---- */
static void
ip_optprint(netdissect_options *ndo,
            register const u_char *cp, u_int length)
{
	register u_int option_len;
	const char *sep = "";

	for (; length > 0; cp += option_len, length -= option_len) {
		u_int option_code;

		ND_PRINT((ndo, "%s", sep));
		sep = ",";

		ND_TCHECK(*cp);
		option_code = *cp;

		ND_PRINT((ndo, "%s",
		          tok2str(ip_option_values,"unknown %u",option_code)));

		if (option_code == IPOPT_NOP ||
                    option_code == IPOPT_EOL)
			option_len = 1;

		else {
			ND_TCHECK(cp[1]);
			option_len = cp[1];
			if (option_len < 2) {
				ND_PRINT((ndo, " [bad length %u]", option_len));
				return;
			}
		}

		if (option_len > length) {
			ND_PRINT((ndo, " [bad length %u]", option_len));
			return;
		}

		ND_TCHECK2(*cp, option_len);

		switch (option_code) {
		case IPOPT_EOL:
			return;

		case IPOPT_TS:
			ip_printts(ndo, cp, option_len);
			break;

		case IPOPT_RR:       /* fall through */
		case IPOPT_SSRR:
		case IPOPT_LSRR:
			ip_printroute(ndo, cp, option_len);
			break;

		case IPOPT_RA:
			if (option_len < 4) {
				ND_PRINT((ndo, " [bad length %u]", option_len));
				break;
			}
			ND_TCHECK(cp[3]);
			if (EXTRACT_16BITS(&cp[2]) != 0)
				ND_PRINT((ndo, " value %u", EXTRACT_16BITS(&cp[2])));
			break;

		case IPOPT_NOP:       /* nothing to print - fall through */
		case IPOPT_SECURITY:
		default:
			break;
		}
	}
	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}

/* ==================================================================
 * end of verbatim tcpdump source
 * ================================================================== */

/* no-op output function pointer, per the direct-call harness recipe */
static int
null_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo; (void)fmt;
	return 0;
}

int
main(int argc, char **argv)
{
	FILE *f;
	long fsz;
	size_t n;
	u_char *buf;
	netdissect_options ndo_storage;
	netdissect_options *ndo = &ndo_storage;

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
	fsz = ftell(f);
	if (fsz < 0) fsz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* attacker data MUST live on the heap so ASAN instruments it */
	buf = (u_char *)malloc((size_t)fsz > 0 ? (size_t)fsz : 1);
	if (!buf) { fclose(f); return 1; }

	n = fsz > 0 ? fread(buf, 1, (size_t)fsz, f) : 0;
	fclose(f);

	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo->ndo_nflag = 1;		/* numeric only -- no DNS, deterministic */
	ndo->ndo_printf = null_printf;
	/*
	 * snapend = exact end of the heap allocation, no padding. The whole
	 * input file IS the IP options buffer and its length IS both the
	 * snapshot length and ip_optprint's `length` argument -- exactly as
	 * the real fuzz harness feeds the captured packet.
	 */
	ndo->ndo_snapend = buf + n;

	ip_optprint(ndo, buf, (u_int)n);

	free(buf);
	return 0;
}

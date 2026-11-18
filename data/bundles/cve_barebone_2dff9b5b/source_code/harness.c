/*
 * Direct-call crash harness for CVE-2017-13053 (tcpdump, print-bgp.c:
 * decode_rt_routing_info) — Decompile-Diverge bundle cve_2dff9b5b.
 *
 * decode_rt_routing_info() is embedded VERBATIM below (byte-for-byte from
 * target/original_function.c). Everything above it is the minimal-but-real
 * subset of tcpdump's netdissect.h / extract.h / print-bgp.c that the
 * function's body actually references (real field/macro/function names,
 * no invented placeholders).
 *
 * Root cause (real CVE): ND_TCHECK2(pptr[1], (plen + 7) / 8) only proves
 * that (plen+7)/8 bytes are captured starting at pptr[1] (this can be as
 * little as 1 byte, when plen==1 after the "-=32" adjustment). But the very
 * next statement's arguments call EXTRACT_32BITS(pptr+1), which
 * unconditionally reads a full 4 bytes at pptr[1..4] regardless of how many
 * bytes were actually proven captured -> heap-buffer-overflow READ
 * (CWE-125) in EXTRACT_32BITS, called from decode_rt_routing_info.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

/* ---------------------------------------------------------------------
 * Minimal faithful defs from tcpdump's netdissect.h / extract.h.
 * Field/macro names are copied verbatim; only fields/branches unused by
 * decode_rt_routing_info's call graph are omitted.
 * --------------------------------------------------------------------- */

typedef unsigned char u_char;
typedef unsigned int u_int;

#if defined(__has_attribute)
# if __has_attribute(no_sanitize)
#  define UNALIGNED_OK __attribute__((no_sanitize("undefined")))
# endif
#endif
#ifndef UNALIGNED_OK
# define UNALIGNED_OK
#endif

/* extract.h: EXTRACT_16BITS/EXTRACT_32BITS, native-unaligned-load path
 * (the LBL_ALIGN branch is not taken on x86_64, matching the real build). */
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

/* netdissect.h: struct netdissect_options — only the two fields
 * decode_rt_routing_info's call graph touches (ndo_snapend for the bounds
 * macros, ndo_bflag for as_printf's AS-format flag). */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_bflag;
	const u_char *ndo_snapend;
};

/* netdissect.h: bounds-check macros, copied verbatim. */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

/* ---------------------------------------------------------------------
 * print-bgp.c: astostr / as_printf / bgp_vpn_rd_print, decode_rt_routing_info's
 * real callees, embedded verbatim. Neither touches pptr/the packet buffer
 * directly (as_printf gets an already-computed u_int; bgp_vpn_rd_print reads
 * only the local route_target[8] array), so they cannot mask or duplicate
 * the crash — they are here purely so the target function's expressions
 * compile and run exactly as in the real binary.
 * --------------------------------------------------------------------- */

static char astostr[20];

static char *
as_printf(netdissect_options *ndo,
          char *str, int size, u_int asnum)
{
	if (!ndo->ndo_bflag || asnum <= 0xFFFF) {
		snprintf(str, size, "%u", asnum);
	} else {
		snprintf(str, size, "%u.%u", asnum >> 16, asnum & 0xFFFF);
	}
	return str;
}

char *
bgp_vpn_rd_print(netdissect_options *ndo,
                 const u_char *pptr)
{
	/* allocate space for the largest possible string */
	static char rd[sizeof("xxxxxxxxxx:xxxxx (xxx.xxx.xxx.xxx:xxxxx)")];
	char *pos = rd;

	switch (EXTRACT_16BITS(pptr)) {

	case 0:
		snprintf(pos, sizeof(rd) - (pos - rd), "%u:%u (= %u.%u.%u.%u)",
		         EXTRACT_16BITS(pptr+2),
		         EXTRACT_32BITS(pptr+4),
		         *(pptr+4), *(pptr+5), *(pptr+6), *(pptr+7));
		break;

	case 1:
		snprintf(pos, sizeof(rd) - (pos - rd), "%u.%u.%u.%u:%u",
		    *(pptr+2), *(pptr+3), *(pptr+4), *(pptr+5), EXTRACT_16BITS(pptr+6));
		break;

	case 2:
		snprintf(pos, sizeof(rd) - (pos - rd), "%s:%u (%u.%u.%u.%u:%u)",
		    as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr+2)),
		    EXTRACT_16BITS(pptr+6), *(pptr+2), *(pptr+3), *(pptr+4),
		    *(pptr+5), EXTRACT_16BITS(pptr+6));
		break;
	default:
		snprintf(pos, sizeof(rd) - (pos - rd), "unknown RD format");
		break;
	}
	pos += strlen(pos);
	*(pos) = '\0';
	return (rd);
}

/* ---------------------------------------------------------------------
 * TARGET FUNCTION — VERBATIM copy of target/original_function.c.
 * Do not modify logic, names, or signature.
 * --------------------------------------------------------------------- */

static int
decode_rt_routing_info(netdissect_options *ndo,
                       const u_char *pptr, char *buf, u_int buflen)
{
	uint8_t route_target[8];
	u_int plen;

	ND_TCHECK(pptr[0]);
	plen = pptr[0];   /* get prefix length */

	if (0 == plen) {
		snprintf(buf, buflen, "default route target");
		return 1;
	}

	if (32 > plen)
		return -1;

        plen-=32; /* adjust prefix length */

	if (64 < plen)
		return -1;

	memset(&route_target, 0, sizeof(route_target));
	ND_TCHECK2(pptr[1], (plen + 7) / 8);
	memcpy(&route_target, &pptr[1], (plen + 7) / 8);
	if (plen % 8) {
		((u_char *)&route_target)[(plen + 7) / 8 - 1] &=
			((0xff00 >> (plen % 8)) & 0xff);
	}
	snprintf(buf, buflen, "origin AS: %s, route target %s",
	    as_printf(ndo, astostr, sizeof(astostr), EXTRACT_32BITS(pptr+1)),
	    bgp_vpn_rd_print(ndo, (u_char *)&route_target));

	return 5 + (plen + 7) / 8;

trunc:
	return -2;
}

/* ---------------------------------------------------------------------
 * Direct-call driver: read argv[1] into a HEAP buffer, mirror how the real
 * caller (bgp_attr_print, print-bgp.c) sets up ndo: pptr = the packet
 * bytes, ndo_snapend = one-past-the-end of what was actually captured. We
 * bound ndo_snapend to EXACTLY the malloc'd+read region so an
 * out-of-bounds parse lands in the ASAN redzone right after the heap
 * allocation, not on unrelated heap memory.
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
	ndo.ndo_bflag = 0;
	ndo.ndo_snapend = data + got;   /* exactly the captured/heap region */

	char outbuf[128];
	memset(outbuf, 0, sizeof(outbuf));
	int ret = decode_rt_routing_info(&ndo, data, outbuf, sizeof(outbuf));
	fprintf(stderr, "decode_rt_routing_info returned %d, buf=\"%s\"\n", ret, outbuf);

	free(data);
	return 0;
}

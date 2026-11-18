/*
 * Direct-call ASAN harness for cve_53ebaca2 (CVE-2017-12896, tcpdump print-isakmp.c).
 *
 * Target: isakmp_rfc3948_print (dataset/cve_53ebaca2/target/original_function.c, embedded
 * VERBATIM below, unmodified). Baseline crash: CWE-125 heap-buffer-overflow READ at
 * print-isakmp.c:3057 in isakmp_rfc3948_print (dedup "isakmp_rfc3948_print--udp_print--ip_print_demux").
 *
 * Root cause: the function's ONLY size guard is `if (length < 4) goto trunc;` on the
 * CALLER-SUPPLIED protocol length. That says nothing about how many bytes are actually
 * present at `bp` -- the real caller (udp_print, via ip_print_demux) derives `length` from
 * the UDP header's length field, which is not required to match the number of bytes actually
 * captured/available at `bp`. So once `length >= 4`, the very next statement
 *     if (bp[0]==0 && bp[1]==0 && bp[2]==0 && bp[3]==0)
 * reads up to 4 bytes through `bp` with NO check that those bytes are actually backed by the
 * buffer -- a classic length/bounds mismatch -> heap-buffer-overflow READ (CWE-125).
 *
 * This harness reproduces exactly that mismatch directly: it heap-allocates a buffer of
 * EXACTLY the number of payload bytes in the input file (so ASAN's redzone sits right at the
 * true end of `bp`), then calls isakmp_rfc3948_print() with a caller-supplied `length` that is
 * independently controlled by the input -- i.e. it plays the role of udp_print, but without
 * any of udp_print/ip_print_demux/the pcap front end, so the crash (or lack of one) is 100%
 * attributable to isakmp_rfc3948_print's own body.
 *
 * Minimal REAL type/macro/prototype definitions are copied VERBATIM (same names, same
 * signatures) from source_code/netdissect.h -- only the pieces isakmp_rfc3948_print itself
 * touches. The full header would need libpcap + the whole autoconf'd build; that dependency
 * carries zero information for this specific bug (isakmp_rfc3948_print only ever touches
 * ndo->ndo_printf via the ND_PRINT macro, and forwards bp/length/bp2 to three callees whose
 * real prototypes are declared below and stubbed for linkage).
 *
 * Input format (this harness's own direct-call encoding -- there is no pcap wire format
 * here, isakmp_rfc3948_print is called directly):
 *   bytes[0:4]  little-endian u32  -> `length` argument (the claimed/caller length)
 *   bytes[4:]   remaining bytes    -> heap-allocated `bp` buffer (exact size, no slack)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <sys/types.h>   /* u_char, u_int -- same basis as source_code/netdissect-stdinc.h */

/* ---- netdissect_options (real name; only the field isakmp_rfc3948_print dereferences,
 * via ND_PRINT) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- real macro, verbatim from source_code/netdissect.h ---- */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- real prototypes of the function's real callees, verbatim from netdissect.h ---- */
extern void isakmp_print(netdissect_options *, const u_char *, u_int, const u_char *);
extern int  esp_print(netdissect_options *, const u_char *, const int, const u_char *, int *, int *);
extern void ip_print_inner(netdissect_options *, const u_char *, u_int, u_int nh, const u_char *);

/* ==================== TARGET FUNCTION (verbatim from target/original_function.c) ==================== */

void
isakmp_rfc3948_print(netdissect_options *ndo,
		     const u_char *bp, u_int length,
		     const u_char *bp2)
{

	if(length == 1 && bp[0]==0xff) {
		ND_PRINT((ndo, "isakmp-nat-keep-alive"));
		return;
	}

	if(length < 4) {
		goto trunc;
	}

	/*
	 * see if this is an IKE packet
	 */
	if(bp[0]==0 && bp[1]==0 && bp[2]==0 && bp[3]==0) {
		ND_PRINT((ndo, "NONESP-encap: "));
		isakmp_print(ndo, bp+4, length-4, bp2);
		return;
	}

	/* must be an ESP packet */
	{
		int nh, enh, padlen;
		int advance;

		ND_PRINT((ndo, "UDP-encap: "));

		advance = esp_print(ndo, bp, length, bp2, &enh, &padlen);
		if(advance <= 0)
			return;

		bp += advance;
		length -= advance + padlen;
		nh = enh & 0xff;

		ip_print_inner(ndo, bp, length, nh, bp2);
		return;
	}

trunc:
	ND_PRINT((ndo,"[|isakmp]"));
	return;
}

/* ==================== callee stubs ====================
 * None of these are on the OOB-read crash path we exercise (the crash happens at the
 * bp[0..3] check, BEFORE any of these would be reached). They only run for the SAFE side of
 * the corpus, so isakmp_rfc3948_print's other real branches still execute for real -- they
 * just don't need to do real protocol parsing themselves to keep the *target* function's own
 * behaviour faithful.
 */

static int noop_printf(netdissect_options *ndo, const char *fmt, ...) {
	(void)ndo; (void)fmt;
	return 0;
}

void isakmp_print(netdissect_options *ndo, const u_char *bp, u_int length, const u_char *bp2) {
	(void)ndo; (void)bp; (void)length; (void)bp2;
}

int esp_print(netdissect_options *ndo, const u_char *bp, const int length,
              const u_char *bp2, int *nhp, int *padlenp) {
	(void)ndo; (void)bp; (void)length; (void)bp2;
	*nhp = 0;
	*padlenp = 0;
	return 0;   /* advance<=0 -> isakmp_rfc3948_print returns right away, always safe */
}

void ip_print_inner(netdissect_options *ndo, const u_char *bp, u_int length, u_int nh, const u_char *bp2) {
	(void)ndo; (void)bp; (void)length; (void)nh; (void)bp2;
}

/* ==================== main: heap buffer + direct call ==================== */

int main(int argc, char **argv) {
	if (argc < 2) return 1;
	FILE *f = fopen(argv[1], "rb");
	if (!f) return 1;
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 1; }
	long fsz = ftell(f);
	if (fsz < 4) { fclose(f); return 0; }   /* not even enough bytes for our length header */
	rewind(f);

	unsigned char hdr[4];
	if (fread(hdr, 1, 4, f) != 4) { fclose(f); return 1; }
	u_int length = (u_int)hdr[0] | ((u_int)hdr[1] << 8) | ((u_int)hdr[2] << 16) | ((u_int)hdr[3] << 24);

	size_t n = (size_t)(fsz - 4);
	u_char *bp = (u_char *)malloc(n);   /* HEAP, exact size -- required so ASAN sees the true end of bp */
	if (n && !bp) { fclose(f); return 1; }
	if (n && fread(bp, 1, n, f) != n) { fclose(f); free(bp); return 1; }
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = noop_printf;

	isakmp_rfc3948_print(&ndo, bp, length, bp);

	free(bp);
	return 0;
}

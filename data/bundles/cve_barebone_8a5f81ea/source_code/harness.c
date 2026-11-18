/*
 * cve_barebone direct-call harness for cve_8a5f81ea (tcpdump, print-pktap.c,
 * CVE-2017-13007-class bug, fix_commit ca336198e8bebccc18502de27672fdbd6eb34856).
 * CWE-125 heap-buffer-overflow READ.
 *
 * TARGET: pktap_if_print() -- embedded VERBATIM below, byte-for-byte identical
 * to data_cve/cve_8a5f81ea/target/original_function.c.
 *
 * ROOT CAUSE: pktap_if_print() parses a pktap_header_t, advances the packet
 * cursor `p` by the attacker-controlled `hdrlen` field (EXTRACT_LE_32BITS of
 * hdr->pkt_len), and for record type PKT_REC_PACKET dispatches to a
 * sub-printer chosen by lookup_printer(dlt):
 *
 *     length -= hdrlen; caplen -= hdrlen; p += hdrlen;
 *     ...
 *     case PKT_REC_PACKET:
 *         if ((printer = lookup_printer(dlt)) != NULL) {
 *             hdrlen += printer(ndo, h, p);
 *
 * `p` is advanced past the pktap header, but `h` (the struct pcap_pkthdr *)
 * handed to `printer()` is the ORIGINAL, UNMODIFIED pointer -- h->caplen and
 * h->len still hold the FULL, pre-advance captured/on-wire lengths, not the
 * (caplen - hdrlen) bytes actually still available at the new `p`. The
 * dispatched sub-printer's own "have I got enough bytes" guard therefore
 * always sees the stale, larger caplen and is fooled whenever hdrlen is close
 * to (or equal to) the real captured length.
 *
 * The fix (ca336198) makes a local `struct pcap_pkthdr nhdr = *h;` with
 * nhdr.caplen/nhdr.len corrected to the post-advance values and passes
 * `&nhdr` to the sub-printer instead of `h`.
 *
 * This harness reaches the fault through DLT_PPP_SERIAL (50) ->
 * ppp_hdlc_if_print() (print-ppp.c), embedded VERBATIM below too, the real
 * next-hop callee lookup_printer() would select for that dlt. When the
 * attacker sets pkt_len (hdrlen) EXACTLY equal to the captured/file length,
 * zero real bytes remain at the advanced `p`, but ppp_hdlc_if_print() sees
 * h->caplen == the stale (large) original length, so its own
 * "if (caplen < 2) ..." guard passes and it falls straight into
 * `switch (p[0])` -- a 1-byte read exactly one byte past the heap
 * allocation -> heap-buffer-overflow READ. Crash stack (innermost first):
 * ppp_hdlc_if_print -> pktap_if_print -> main.
 *
 * Everything besides the two VERBATIM functions above (lookup_printer's
 * dispatch table, chdlc_if_print, handle_ppp, tok2str/ppptype2str,
 * pcap_datalink_val_to_name, the ndo_printf/ndo_default_print/ndo_error/
 * ndo_warning backends) is minimal harness GLUE standing in for the rest of
 * the ~30kLOC project. None of it is on the fault path for any input in this
 * corpus: eflag is always 0 so pktap_header_print() (included verbatim,
 * since pktap_if_print's own body unconditionally references it) is never
 * actually invoked, and the corpus never selects a dlt other than
 * DLT_PPP_SERIAL for a PKT_REC_PACKET record, so lookup_printer's real
 * ~90-entry table collapses to exactly the one entry that matters here
 * ("{ ppp_hdlc_if_print, DLT_PPP_SERIAL }", print.c:221) with the same
 * NULL fallback the real function uses for every other dlt. All real
 * struct/macro/field names come straight from source_code/{netdissect.h,
 * extract.h,ppp.h,chdlc.h,print-pktap.c,print-ppp.c}; nothing is invented.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <arpa/inet.h>

/* real BSD-ish scalar names tcpdump uses throughout (<sys/types.h>) */
typedef unsigned char  u_char;
typedef unsigned int   u_int;

/* ---- funcattrs.h: portability attribute macros used by netdissect.h;
 * no-ops here (diagnostics only, no effect on codegen/ABI). ---- */
#define PRINTFLIKE_FUNCPTR(a, b)
#define NORETURN_FUNCPTR

/* ---- pcap.h, minimal-but-real subset: struct pcap_pkthdr's public layout
 * (ts/caplen/len) plus the ONE dlt constant this corpus dispatches on.
 * Self-defined (not #include <pcap/pcap.h>) to keep the harness fully
 * self-contained / link with just -lm, as tcpdump's own build does not use
 * this exact struct definition text but the real libpcap public API does. */
typedef unsigned int bpf_u_int32;
struct pcap_pkthdr {
	struct { long tv_sec; long tv_usec; } ts;	/* struct timeval, unused here */
	bpf_u_int32 caplen;	/* length of portion present */
	bpf_u_int32 len;	/* length of this packet (off wire) */
};
#define DLT_PPP_SERIAL	50	/* PPP over serial with HDLC encapsulation (pcap/dlt.h) */

/* ---- extract.h, verbatim macros the embedded functions use. x86-64 is not
 * LBL_ALIGN, so the real header compiles the "processor natively handles
 * unaligned loads" static-inline branch for EXTRACT_16BITS; EXTRACT_LE_32BITS
 * is unconditional (byte-at-a-time) in the real header. ---- */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK __attribute__((no_sanitize_undefined))
#elif defined(__has_attribute) && __has_attribute(no_sanitize)
#define UNALIGNED_OK __attribute__((no_sanitize("undefined")))
#else
#define UNALIGNED_OK
#endif

static inline uint16_t UNALIGNED_OK
EXTRACT_16BITS(const void *p)
{
	return ((uint16_t)ntohs(*(const uint16_t *)(p)));
}

#define EXTRACT_LE_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 3)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 0)) << 0)))

/* ---- netdissect.h, verbatim struct/typedef/macro definitions. ---- */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

typedef struct netdissect_options netdissect_options;

#define IF_PRINTER_ARGS (netdissect_options *, const struct pcap_pkthdr *, const u_char *)

typedef u_int (*if_printer) IF_PRINTER_ARGS;

struct netdissect_options {
  int ndo_bflag;		/* print 4 byte ASes in ASDOT notation */
  int ndo_eflag;		/* print ethernet header */
  int ndo_fflag;		/* don't translate "foreign" IP address */
  int ndo_Kflag;		/* don't check TCP checksums */
  int ndo_nflag;		/* leave addresses as numbers */
  int ndo_Nflag;		/* remove domains from printed host names */
  int ndo_qflag;		/* quick (shorter) output */
  int ndo_Sflag;		/* print raw TCP sequence numbers */
  int ndo_tflag;		/* print packet arrival time */
  int ndo_uflag;		/* Print undecoded NFS handles */
  int ndo_vflag;		/* verbosity level */
  int ndo_xflag;		/* print packet in hex */
  int ndo_Xflag;		/* print packet in hex/ASCII */
  int ndo_Aflag;		/* print packet only in ASCII observing TAB,
				 * LF, CR and SPACE as graphical chars
				 */
  int ndo_Hflag;		/* dissect 802.11s draft mesh standard */
  int ndo_packet_number;	/* print a packet number in the beginning of line */
  int ndo_suppress_default_print; /* don't use default_print() for unknown packet types */
  int ndo_tstamp_precision;	/* requested time stamp precision */
  const char *program_name;	/* Name of the program using the library */

  char *ndo_espsecret;
  struct sa_list *ndo_sa_list_head;  /* used by print-esp.c */
  struct sa_list *ndo_sa_default;

  char *ndo_sigsecret;		/* Signature verification secret key */

  int   ndo_packettype;	/* as specified by -T */

  int   ndo_snaplen;

  /*global pointers to beginning and end of current packet (during printing) */
  const u_char *ndo_packetp;
  const u_char *ndo_snapend;

  /* pointer to the if_printer function */
  if_printer ndo_if_printer;

  /* pointer to void function to output stuff */
  void (*ndo_default_print)(netdissect_options *,
			    register const u_char *bp, register u_int length);

  /* pointer to function to do regular output */
  int  (*ndo_printf)(netdissect_options *,
		     const char *fmt, ...)
		     PRINTFLIKE_FUNCPTR(2, 3);
  /* pointer to function to output errors */
  void NORETURN_FUNCPTR (*ndo_error)(netdissect_options *,
				     const char *fmt, ...)
				     PRINTFLIKE_FUNCPTR(2, 3);
  /* pointer to function to output warnings */
  void (*ndo_warning)(netdissect_options *,
		      const char *fmt, ...)
		      PRINTFLIKE_FUNCPTR(2, 3);
};

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF
#define ND_DEFAULTPRINT(ap, length) (*ndo->ndo_default_print)(ndo, ap, length)

/* ---- ppp.h / chdlc.h, verbatim macro values. ---- */
#define PPP_ADDRESS	0xff	/* The address byte value */
#define CHDLC_UNICAST		0x0f
#define CHDLC_BCAST		0x8f

/* ---------------------------------------------------------------------
 * Harness glue: stand-ins for the rest of the project. None of these is
 * ever reached at runtime by any input in this corpus (see the file header
 * comment above) -- they exist only so the VERBATIM functions below compile
 * and link standalone.
 * --------------------------------------------------------------------- */
const char *
pcap_datalink_val_to_name(int dlt)
{
	(void)dlt;
	return "PPP_SERIAL";
}

static u_int
chdlc_if_print(netdissect_options *ndo, const struct pcap_pkthdr *h, const u_char *p)
{
	(void)ndo; (void)h; (void)p;
	return 0;
}

static void
handle_ppp(netdissect_options *ndo, u_int proto, const u_char *p, int length)
{
	(void)ndo; (void)proto; (void)p; (void)length;
}

static const struct tok ppptype2str[] = {
	{ 0, NULL }
};

static const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	(void)lp; (void)v;
	return fmt;
}

/* real prototype, from netdissect.h ("extern u_int ppp_hdlc_if_print
 * IF_PRINTER_ARGS;") -- definition follows pktap_if_print below, matching
 * the real project's file order (print-pktap.c then print-ppp.c). */
extern u_int ppp_hdlc_if_print IF_PRINTER_ARGS;

/*
 * Harness glue: stand-in for print.c's lookup_printer(), a linear search
 * over a ~90-entry {printer,dlt} table spanning the whole project. This
 * corpus only ever asks for DLT_PPP_SERIAL ("{ ppp_hdlc_if_print,
 * DLT_PPP_SERIAL }", print.c:221) -- every other dlt legitimately falls
 * through to the real function's NULL fallback for an unrecognized type.
 */
static if_printer
lookup_printer(int type)
{
	if (type == DLT_PPP_SERIAL)
		return ppp_hdlc_if_print;
	return NULL;
}

/* ========================================================================
 * print-pktap.c -- verbatim (byte-identical to source_code/print-pktap.c).
 * ======================================================================== */
typedef struct pktap_header {
	uint32_t	pkt_len;	/* length of pktap header */
	uint32_t	pkt_rectype;	/* type of record */
	uint32_t	pkt_dlt;	/* DLT type of this packet */
	char		pkt_ifname[24];	/* interface name */
	uint32_t	pkt_flags;
	uint32_t	pkt_pfamily;	/* "protocol family" */
	uint32_t	pkt_llhdrlen;	/* link-layer header length? */
	uint32_t	pkt_lltrlrlen;	/* link-layer trailer length? */
	uint32_t	pkt_pid;	/* process ID */
	char		pkt_cmdname[20]; /* command name */
	uint32_t	pkt_svc_class;	/* "service class" */
	uint16_t	pkt_iftype;	/* "interface type" */
	uint16_t	pkt_ifunit;	/* unit number of interface? */
	uint32_t	pkt_epid;	/* "effective process ID" */
	char		pkt_ecmdname[20]; /* "effective command name" */
} pktap_header_t;

/*
 * Record types.
 */
#define PKT_REC_NONE	0	/* nothing follows the header */
#define PKT_REC_PACKET	1	/* a packet follows the header */

static inline void
pktap_header_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	const pktap_header_t *hdr;
	uint32_t dlt, hdrlen;
	const char *dltname;

	hdr = (const pktap_header_t *)bp;

	dlt = EXTRACT_LE_32BITS(&hdr->pkt_dlt);
	hdrlen = EXTRACT_LE_32BITS(&hdr->pkt_len);
	dltname = pcap_datalink_val_to_name(dlt);
	if (!ndo->ndo_qflag) {
		ND_PRINT((ndo,"DLT %s (%d) len %d",
			  (dltname != NULL ? dltname : "UNKNOWN"), dlt, hdrlen));
        } else {
		ND_PRINT((ndo,"%s", (dltname != NULL ? dltname : "UNKNOWN")));
        }

	ND_PRINT((ndo, ", length %u: ", length));
}

/*
 * This is the top level routine of the printer.  'p' points
 * to the ether header of the packet, 'h->ts' is the timestamp,
 * 'h->len' is the length of the packet off the wire, and 'h->caplen'
 * is the number of bytes actually captured.
 */
u_int
pktap_if_print(netdissect_options *ndo,
               const struct pcap_pkthdr *h, const u_char *p)
{
	uint32_t dlt, hdrlen, rectype;
	u_int caplen = h->caplen;
	u_int length = h->len;
	if_printer printer;
	const pktap_header_t *hdr;

	if (caplen < sizeof(pktap_header_t) || length < sizeof(pktap_header_t)) {
		ND_PRINT((ndo, "[|pktap]"));
		return (0);
	}
	hdr = (const pktap_header_t *)p;
	dlt = EXTRACT_LE_32BITS(&hdr->pkt_dlt);
	hdrlen = EXTRACT_LE_32BITS(&hdr->pkt_len);
	if (hdrlen < sizeof(pktap_header_t)) {
		/*
		 * Claimed header length < structure length.
		 * XXX - does this just mean some fields aren't
		 * being supplied, or is it truly an error (i.e.,
		 * is the length supplied so that the header can
		 * be expanded in the future)?
		 */
		ND_PRINT((ndo, "[|pktap]"));
		return (0);
	}
	if (caplen < hdrlen || length < hdrlen) {
		ND_PRINT((ndo, "[|pktap]"));
		return (hdrlen);
	}

	if (ndo->ndo_eflag)
		pktap_header_print(ndo, p, length);

	length -= hdrlen;
	caplen -= hdrlen;
	p += hdrlen;

	rectype = EXTRACT_LE_32BITS(&hdr->pkt_rectype);
	switch (rectype) {

	case PKT_REC_NONE:
		ND_PRINT((ndo, "no data"));
		break;

	case PKT_REC_PACKET:
		if ((printer = lookup_printer(dlt)) != NULL) {
			hdrlen += printer(ndo, h, p);
		} else {
			if (!ndo->ndo_eflag)
				pktap_header_print(ndo, (const u_char *)hdr,
						length + hdrlen);

			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(p, caplen);
		}
		break;
	}

	return (hdrlen);
}

/* ========================================================================
 * print-ppp.c:1642-1704 -- verbatim. This is the real callee where the
 * fault lives (dedup_token's innermost frame): `switch (p[0])` reads one
 * byte at the (stale-caplen-advanced) `p`, exactly one byte past the heap
 * allocation whenever hdrlen == the buffer's captured length.
 * ======================================================================== */
u_int
ppp_hdlc_if_print(netdissect_options *ndo,
                  const struct pcap_pkthdr *h, register const u_char *p)
{
	register u_int length = h->len;
	register u_int caplen = h->caplen;
	u_int proto;
	u_int hdrlen = 0;

	if (caplen < 2) {
		ND_PRINT((ndo, "[|ppp]"));
		return (caplen);
	}

	switch (p[0]) {

	case PPP_ADDRESS:
		if (caplen < 4) {
			ND_PRINT((ndo, "[|ppp]"));
			return (caplen);
		}

		if (ndo->ndo_eflag)
			ND_PRINT((ndo, "%02x %02x %d ", p[0], p[1], length));
		p += 2;
		length -= 2;
		hdrlen += 2;

		proto = EXTRACT_16BITS(p);
		p += 2;
		length -= 2;
		hdrlen += 2;
		ND_PRINT((ndo, "%s: ", tok2str(ppptype2str, "unknown PPP protocol (0x%04x)", proto)));

		handle_ppp(ndo, proto, p, length);
		break;

	case CHDLC_UNICAST:
	case CHDLC_BCAST:
		return (chdlc_if_print(ndo, h, p));

	default:
		if (caplen < 4) {
			ND_PRINT((ndo, "[|ppp]"));
			return (caplen);
		}

		if (ndo->ndo_eflag)
			ND_PRINT((ndo, "%02x %02x %d ", p[0], p[1], length));
		p += 2;
		hdrlen += 2;

		/*
		 * XXX - NetBSD's "ppp_netbsd_serial_if_print()" treats
		 * the next two octets as an Ethernet type; does that
		 * ever happen?
		 */
		ND_PRINT((ndo, "unknown addr %02x; ctrl %02x", p[0], p[1]));
		break;
	}

	return (hdrlen);
}

/* ---------------------------------------------------------------------
 * main(): minimal harness runtime -- ndo_printf/ndo_default_print/ndo_error/
 * ndo_warning backends and the single direct call into the target function.
 * --------------------------------------------------------------------- */
static int
vb_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return r;
}

static void
vb_default_print(netdissect_options *ndo, register const u_char *bp, register u_int length)
{
	(void)ndo; (void)bp; (void)length;
}

static void NORETURN_FUNCPTR
vb_error(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(2);
}

static void
vb_warning(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
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
	long sz = ftell(f);
	if (sz < 0) sz = 0;
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* Heap buffer sized EXACTLY to the input (FDP-style: the whole file IS
	 * the captured packet), so ASAN's redzone sits immediately past the
	 * attacker-controlled data -- required for the heap-buffer-overflow
	 * READ to be detectable. */
	size_t n = (size_t)sz;
	unsigned char *buf = (unsigned char *)malloc(n > 0 ? n : 1);
	if (!buf) { fclose(f); return 1; }
	size_t rd = 0;
	if (n > 0)
		rd = fread(buf, 1, n, f);
	fclose(f);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = vb_printf;
	ndo.ndo_default_print = vb_default_print;
	ndo.ndo_error = vb_error;
	ndo.ndo_warning = vb_warning;
	ndo.ndo_eflag = 0;
	ndo.ndo_qflag = 0;
	ndo.ndo_suppress_default_print = 1;

	struct pcap_pkthdr h;
	memset(&h, 0, sizeof(h));
	h.caplen = (bpf_u_int32)rd;
	h.len = (bpf_u_int32)rd;

	pktap_if_print(&ndo, &h, buf);

	free(buf);
	return 0;
}

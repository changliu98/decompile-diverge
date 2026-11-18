/*
 * Direct-call crash harness for cvf_5f0e6a55 (CVE-2017-13000, tcpdump
 * print-802_15_4.c, ieee802_15_4_if_print()). CWE-125 heap-buffer-overflow
 * READ.
 *
 * Bug recap (matches baseline dedup_token
 * "ieee802_15_4_if_print--pretty_print_packet--print_packet" / summary
 * "AddressSanitizer: heap-buffer-overflow /work/./print-802_15_4.c:125:4 in
 * ieee802_15_4_if_print" -- print-802_15_4.c line 125 is EXACTLY
 * target/original_function.c line 61, since target/meta.json's
 * start_line=65 and 65+61-1=125):
 *
 * In the FC_ADDRESSING_MODE_SHORT arm of the DESTINATION-address switch
 * (original_function.c:47-65), the destination PAN ID is fetched and the
 * cursor advanced:
 *
 *     if (caplen < 2) { ...return... }        (line 48)
 *     panid = EXTRACT_LE_16BITS(p);            (line 52, reads p[0..1])
 *     p += 2; caplen -= 2; hdrlen += 2;         (lines 53-55)
 *     if (caplen < 2) { ...return... }         (line 56)
 *     if (ndo->ndo_vflag)
 *         ND_PRINT((ndo,"%04x:%04x ", panid, EXTRACT_LE_16BITS(p + 2)));  (line 61)
 *
 * The second bounds check (line 56) only proves 2 more bytes are captured
 * (p[0..1]), but the actual read on line 61 is `EXTRACT_LE_16BITS(p + 2)`,
 * which reads p[2..3] -- 2 bytes further out than what was checked. So
 * whenever exactly 2 bytes remain captured after the second check (not 4),
 * the read runs 1-2 bytes past the end of the captured/heap buffer ->
 * heap-buffer-overflow READ. This requires `ndo->ndo_vflag` truthy (a
 * plain `tcpdump -v` run), since the faulting EXTRACT is only evaluated as
 * an argument to ND_PRINT inside `if (ndo->ndo_vflag)`.
 *
 * ieee802_15_4_if_print() is embedded VERBATIM from target/original_function.c
 * (byte-for-byte identical: no logic/name/signature change). It is a
 * self-contained leaf apart from ND_PRINT (macro, no real callee),
 * ND_DEFAULTPRINT (a real if_printer-supplied function pointer, given a
 * no-op stand-in here since none of the corpus needs its output and it is
 * never on the fault path) and le64addr_string (real addrtoname.c signature,
 * only called from the LONG-addressing arms, both of which are correctly
 * caplen-guarded before the call -- never the fault site -- so it is given a
 * minimal-but-real-signature stand-in that reads exactly the real 8 bytes,
 * matching the real function's memory-access footprint, without the real
 * function's strdup/hash-table bookkeeping).
 *
 * main() reads argv[1] into a HEAP buffer (malloc'd to EXACTLY the file
 * length -- this IS the "captured packet", h->caplen = file length, no
 * padding, ASan's redzone sits immediately past the real data) and calls
 * ieee802_15_4_if_print(&ndo, &h, p) ONCE, directly, with ndo->ndo_vflag=1
 * (mirrors the real `tcpdump -v` caller that this CVE requires).
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

/* ---- pcap.h, minimal-but-real subset: ieee802_15_4_if_print() only
 * touches h->caplen, but the real struct layout is reproduced (ts/caplen/
 * len, bpf_u_int32) so the field it does use has the real type/offset. ---- */
typedef unsigned int bpf_u_int32;
struct pcap_pkthdr {
	struct { long tv_sec; long tv_usec; } ts;	/* struct timeval, unused */
	bpf_u_int32 caplen;
	bpf_u_int32 len;
};

/* ---- netdissect.h, netdissect_options trimmed to the real fields this
 * function (and the macros/callees it uses) actually touch: ndo_vflag,
 * ndo_suppress_default_print, ndo_printf, ndo_default_print. Real names/
 * types; every other ndo_* knob is irrelevant to this function. ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	int ndo_vflag;				/* verbosity level */
	int ndo_suppress_default_print;	/* don't use default_print() for unknown packet types */
	void (*ndo_default_print)(netdissect_options *, const u_char *bp, u_int length);
	int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h macros, verbatim */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF
#define ND_DEFAULTPRINT(ap, length) (*ndo->ndo_default_print)(ndo, ap, length)

/* extract.h, verbatim (only the LE accessors this function uses) */
#define EXTRACT_LE_8BITS(p) (*(p))
#define EXTRACT_LE_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 0)) << 0)))

/* addrtoname.h real prototype; addrtoname.c's le64addr_string() is NOT the
 * fault site (both call sites are caplen>=8 guarded immediately before the
 * call) -- minimal real-signature stand-in that reads the real 8 bytes
 * (matching the real function's memory footprint: `for (i = len; i > 0;
 * --i) ... *(ep + i - 1)`, len==8) without the real strdup/hash-table
 * bookkeeping, per the harness convention for off-fault-path real callees. */
static const char *
le64addr_string(netdissect_options *ndo, const u_char *ep)
{
	static char buf[32];
	(void)ndo;
	snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
	    ep[0], ep[1], ep[2], ep[3], ep[4], ep[5], ep[6], ep[7]);
	return buf;
}

/* print-802_15_4.c file-scope statics ieee802_15_4_if_print() reads
 * directly, verbatim (source_code/print-802_15_4.c lines 34-61). */
static const char *ftypes[] = {
	"Beacon",			/* 0 */
	"Data",				/* 1 */
	"ACK",				/* 2 */
	"Command",			/* 3 */
	"Reserved (0x4)",		/* 4 */
	"Reserved (0x5)",		/* 5 */
	"Reserved (0x6)",		/* 6 */
	"Reserved (0x7)",		/* 7 */
};

/*
 * Frame Control subfields.
 */
#define FC_FRAME_TYPE(fc)		((fc) & 0x7)
#define FC_SECURITY_ENABLED		0x0008
#define FC_FRAME_PENDING		0x0010
#define FC_ACK_REQUEST			0x0020
#define FC_PAN_ID_COMPRESSION		0x0040
#define FC_DEST_ADDRESSING_MODE(fc)	(((fc) >> 10) & 0x3)
#define FC_FRAME_VERSION(fc)		(((fc) >> 12) & 0x3)
#define FC_SRC_ADDRESSING_MODE(fc)	(((fc) >> 14) & 0x3)

#define FC_ADDRESSING_MODE_NONE		0x00
#define FC_ADDRESSING_MODE_RESERVED	0x01
#define FC_ADDRESSING_MODE_SHORT	0x02
#define FC_ADDRESSING_MODE_LONG		0x03

/* ---- target function, embedded VERBATIM from target/original_function.c
 * (byte-for-byte identical -- diffed during validation). ---- */
u_int
ieee802_15_4_if_print(netdissect_options *ndo,
                      const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	u_int hdrlen;
	uint16_t fc;
	uint8_t seq;
	uint16_t panid = 0;

	if (caplen < 3) {
		ND_PRINT((ndo, "[|802.15.4]"));
		return caplen;
	}
	hdrlen = 3;

	fc = EXTRACT_LE_16BITS(p);
	seq = EXTRACT_LE_8BITS(p + 2);

	p += 3;
	caplen -= 3;

	ND_PRINT((ndo,"IEEE 802.15.4 %s packet ", ftypes[FC_FRAME_TYPE(fc)]));
	if (ndo->ndo_vflag)
		ND_PRINT((ndo,"seq %02x ", seq));

	/*
	 * Destination address and PAN ID, if present.
	 */
	switch (FC_DEST_ADDRESSING_MODE(fc)) {
	case FC_ADDRESSING_MODE_NONE:
		if (fc & FC_PAN_ID_COMPRESSION) {
			/*
			 * PAN ID compression; this requires that both
			 * the source and destination addresses be present,
			 * but the destination address is missing.
			 */
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"none "));
		break;
	case FC_ADDRESSING_MODE_RESERVED:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"reserved destination addressing mode"));
		return hdrlen;
	case FC_ADDRESSING_MODE_SHORT:
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		panid = EXTRACT_LE_16BITS(p);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%04x ", panid, EXTRACT_LE_16BITS(p + 2)));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;
	case FC_ADDRESSING_MODE_LONG:
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		panid = EXTRACT_LE_16BITS(p);
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		if (caplen < 8) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%s ", panid, le64addr_string(ndo, p)));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}
	if (ndo->ndo_vflag)
		ND_PRINT((ndo,"< "));

	/*
	 * Source address and PAN ID, if present.
	 */
	switch (FC_SRC_ADDRESSING_MODE(fc)) {
	case FC_ADDRESSING_MODE_NONE:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"none "));
		break;
	case FC_ADDRESSING_MODE_RESERVED:
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"reserved source addressing mode"));
		return 0;
	case FC_ADDRESSING_MODE_SHORT:
		if (!(fc & FC_PAN_ID_COMPRESSION)) {
			/*
			 * The source PAN ID is not compressed out, so
			 * fetch it.  (Otherwise, we'll use the destination
			 * PAN ID, fetched above.)
			 */
			if (caplen < 2) {
				ND_PRINT((ndo, "[|802.15.4]"));
				return hdrlen;
			}
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 2) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%04x ", panid, EXTRACT_LE_16BITS(p)));
		p += 2;
		caplen -= 2;
		hdrlen += 2;
		break;
	case FC_ADDRESSING_MODE_LONG:
		if (!(fc & FC_PAN_ID_COMPRESSION)) {
			/*
			 * The source PAN ID is not compressed out, so
			 * fetch it.  (Otherwise, we'll use the destination
			 * PAN ID, fetched above.)
			 */
			if (caplen < 2) {
				ND_PRINT((ndo, "[|802.15.4]"));
				return hdrlen;
			}
			panid = EXTRACT_LE_16BITS(p);
			p += 2;
			caplen -= 2;
			hdrlen += 2;
		}
		if (caplen < 8) {
			ND_PRINT((ndo, "[|802.15.4]"));
			return hdrlen;
		}
		if (ndo->ndo_vflag)
			ND_PRINT((ndo,"%04x:%s ", panid, le64addr_string(ndo, p)));
		p += 8;
		caplen -= 8;
		hdrlen += 8;
		break;
	}

	if (!ndo->ndo_suppress_default_print)
		ND_DEFAULTPRINT(p, caplen);

	return hdrlen;
}
/* ---- end verbatim target function ---- */

static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = vprintf(fmt, ap);
	va_end(ap);
	return r;
}

static void
nd_default_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	/* no-op output fn pointer (per harness convention): touches no
	 * memory, matches the real ndo_default_print signature. */
	(void)ndo; (void)bp; (void)length;
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
	long len = ftell(f);
	if (len < 0) { fclose(f); return 1; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* REQUIRED: heap buffer for attacker-controlled bytes, malloc'd to
	 * EXACTLY the file length, so ASan's redzone sits immediately past
	 * the real data (mirrors the "captured packet" buffer in tcpdump --
	 * h->caplen IS the file length, no padding). */
	u_char *buf = NULL;
	if (len > 0) {
		buf = malloc((size_t)len);
		if (!buf) { fclose(f); return 1; }
		size_t rd = fread(buf, 1, (size_t)len, f);
		fclose(f);
		if (rd != (size_t)len) { free(buf); return 1; }
	} else {
		fclose(f);
		/* len == 0: still exercise the function with a non-NULL,
		 * zero-size heap allocation so caplen==0 correctly trips the
		 * function's own "caplen < 3" guard on the first line. */
		buf = malloc(1);
		if (!buf) return 1;
	}

	struct pcap_pkthdr h;
	memset(&h, 0, sizeof(h));
	h.caplen = (bpf_u_int32)len;
	h.len = (bpf_u_int32)len;

	netdissect_options ndo_storage;
	memset(&ndo_storage, 0, sizeof(ndo_storage));
	netdissect_options *ndo = &ndo_storage;
	ndo->ndo_printf = nd_printf;
	ndo->ndo_default_print = nd_default_print;
	ndo->ndo_vflag = 1;			/* REQUIRED: this CVE only fires under `tcpdump -v` (the
						 * faulting EXTRACT is an argument only evaluated when
						 * ndo_vflag is truthy) */
	ndo->ndo_suppress_default_print = 0;

	u_int rv = ieee802_15_4_if_print(ndo, &h, buf);

	printf("ieee802_15_4_if_print returned %u (len=%ld)\n", rv, len);

	free(buf);
	return 0;
}

/*
 * cve_barebone direct-call harness for CVE-2017-13010 (tcpdump beep_print).
 *
 * Isolation of the BEEP printer over-read: beep_print() calls l_strnstart(),
 * which guards only on the CLAIMED length (tl1 > l2) and then does
 * strncmp(prefix, bp, 4).  When the caller's claimed `length` (>= 4) exceeds
 * the actual heap allocation backing `bp`, strncmp() reads past the end of the
 * buffer -> heap-buffer-overflow READ (CWE-125) with the crash stack
 *   strncmp -> l_strnstart -> beep_print
 *
 * All real type / field / function names are copied from the tcpdump tree
 * (source_code/netdissect.h, source_code/print-beep.c); nothing is invented.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

/* real BSD-ish scalar names used by tcpdump (from <sys/types.h>) */
typedef unsigned char u_char;
typedef unsigned int  u_int;

/* ---- minimal shims for the compiler attributes tcpdump attaches to the ----
 * ---- netdissect_options function pointers (names kept, no semantics)    ---- */
#define PRINTFLIKE_FUNCPTR(a, b)
#define NORETURN_FUNCPTR

/* referenced only through pointers inside netdissect_options */
struct pcap_pkthdr;
struct sa_list;

/* if_printer typedef, verbatim shape from netdissect.h */
#define IF_PRINTER_ARGS (struct netdissect_options *, const struct pcap_pkthdr *, const u_char *)
typedef u_int (*if_printer) IF_PRINTER_ARGS;

/* netdissect_options: copied from source_code/netdissect.h (real field names) */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
  int ndo_bflag;
  int ndo_eflag;
  int ndo_fflag;
  int ndo_Kflag;
  int ndo_nflag;
  int ndo_Nflag;
  int ndo_qflag;
  int ndo_Sflag;
  int ndo_tflag;
  int ndo_uflag;
  int ndo_vflag;
  int ndo_xflag;
  int ndo_Xflag;
  int ndo_Aflag;
  int ndo_Hflag;
  int ndo_packet_number;
  int ndo_suppress_default_print;
  int ndo_tstamp_precision;
  const char *program_name;

  char *ndo_espsecret;
  struct sa_list *ndo_sa_list_head;
  struct sa_list *ndo_sa_default;

  char *ndo_sigsecret;

  int   ndo_packettype;

  int   ndo_snaplen;

  const u_char *ndo_packetp;
  const u_char *ndo_snapend;

  if_printer ndo_if_printer;

  void (*ndo_default_print)(netdissect_options *,
			    register const u_char *bp, register u_int length);

  int  (*ndo_printf)(netdissect_options *,
		     const char *fmt, ...)
		     PRINTFLIKE_FUNCPTR(2, 3);

  void NORETURN_FUNCPTR (*ndo_error)(netdissect_options *,
				     const char *fmt, ...)
				     PRINTFLIKE_FUNCPTR(2, 3);

  void (*ndo_warning)(netdissect_options *,
		      const char *fmt, ...)
		      PRINTFLIKE_FUNCPTR(2, 3);
};

/* ND_PRINT macro, verbatim from netdissect.h */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* faithful output sink for ndo_printf (real signature; prints to stdout) */
static int
nd_printf(netdissect_options *ndo, const char *fmt, ...)
{
	int ret;
	va_list ap;
	(void)ndo;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);
	return ret;
}

/* ==== ON THE CRASH PATH: l_strnstart(), verbatim from print-beep.c ==== */
static int
l_strnstart(const char *tstr1, u_int tl1, const char *str2, u_int l2)
{

	if (tl1 > l2)
		return 0;

	return (strncmp(tstr1, str2, tl1) == 0 ? 1 : 0);
}

/* ==== TARGET: beep_print(), byte-for-byte from target/original_function.c ==== */
void
beep_print(netdissect_options *ndo, const u_char *bp, u_int length)
{

	if (l_strnstart("MSG", 4, (const char *)bp, length)) /* A REQuest */
		ND_PRINT((ndo, " BEEP MSG"));
	else if (l_strnstart("RPY ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP RPY"));
	else if (l_strnstart("ERR ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP ERR"));
	else if (l_strnstart("ANS ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP ANS"));
	else if (l_strnstart("NUL ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP NUL"));
	else if (l_strnstart("SEQ ", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP SEQ"));
	else if (l_strnstart("END", 4, (const char *)bp, length))
		ND_PRINT((ndo, " BEEP END"));
	else
		ND_PRINT((ndo, " BEEP (payload or undecoded)"));
}

/* ---------------------------------------------------------------------------
 * main(): read argv[1] into a heap buffer (FDP-style).
 *   [0..3]  little-endian u_int  = the CLAIMED length passed to beep_print
 *   [4..]   = packet payload, copied into a TIGHT malloc()'d buffer (bp)
 * The claimed length is independent of the real allocation size, mirroring
 * tcpdump handing beep_print an on-wire length that exceeds the captured bytes.
 * ------------------------------------------------------------------------- */
int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input>\n", argv[0]);
		return 2;
	}

	FILE *f = fopen(argv[1], "rb");
	if (!f) {
		perror("fopen");
		return 2;
	}
	if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 2; }
	long fsz = ftell(f);
	if (fsz < 0) { fclose(f); return 2; }
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 2; }

	unsigned char *data = (unsigned char *)malloc(fsz ? (size_t)fsz : 1);
	if (!data) { fclose(f); return 2; }
	size_t got = fread(data, 1, (size_t)fsz, f);
	fclose(f);

	/* need at least the 4-byte length header + 1 payload byte */
	if (got < 5) {
		free(data);
		return 0; /* too short to exercise the parser */
	}

	u_int length = (u_int)data[0]
	             | ((u_int)data[1] << 8)
	             | ((u_int)data[2] << 16)
	             | ((u_int)data[3] << 24);

	size_t plen = got - 4;             /* payload byte count */
	unsigned char *bp = (unsigned char *)malloc(plen);  /* TIGHT, ASAN-guarded */
	if (!bp) { free(data); return 2; }
	memcpy(bp, data + 4, plen);

	netdissect_options ndo_storage;
	memset(&ndo_storage, 0, sizeof(ndo_storage));
	ndo_storage.ndo_printf = nd_printf;
	netdissect_options *ndo = &ndo_storage;

	beep_print(ndo, (const u_char *)bp, length);

	printf("\n");
	free(bp);
	free(data);
	return 0;
}

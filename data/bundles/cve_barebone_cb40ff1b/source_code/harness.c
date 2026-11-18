/*
 * Direct-call crash harness -- CVE-2017-13026 (tcpdump, print-isoclns.c)
 * Bundle: cve_cb40ff1b | Target: isis_print_mt_capability_subtlv | CWE-125 heap-buffer-overflow READ
 *
 * isis_print_mt_capability_subtlv() walks a chain of ISIS MT-Capability
 * sub-TLVs:
 *     while (len > 2) {
 *       stlv_type = *(tptr++);
 *       stlv_len  = *(tptr++);
 *       ...
 *       len = len - 2;
 *       switch (stlv_type) { case ISIS_SUBTLV_SPB_INSTANCE: ...(TCHECK'd)...
 *                            case ISIS_SUBTLV_SPBM_SI: ...(TCHECK'd)...
 *                            default: break; }
 *     }
 * The loop-condition/2-byte-header read at the TOP of the loop
 * (`stlv_type = *(tptr++); stlv_len = *(tptr++);`) has NO ND_TCHECK2/
 * ND_TTEST2 guard at all -- only the two known sub-TLV bodies (SPB_INSTANCE,
 * SPBM_SI) are bounds-checked, and only AFTER the header is already read.
 * `len` here is the caller's CLAIMED remaining sub-TLV length (taken from an
 * earlier TLV length byte inside the packet, attacker-controlled), which is
 * never validated against how many bytes were actually captured
 * (`ndo_snapend`). So a claimed `len` larger than the real captured buffer
 * makes the loop keep issuing 2-byte header reads past the end of the
 * buffer -- heap-buffer-overflow READ (CWE-125), firing directly at
 * `stlv_type = *(tptr++);` (print-isoclns.c:1514, exactly the frozen
 * baseline's crash site/summary). Original baseline dedup_token:
 * isis_print_mt_capability_subtlv--isis_print--isoclns_print.
 *
 * This harness reproduces the SAME site/class fault -- inside
 * isis_print_mt_capability_subtlv itself -- by calling it DIRECTLY on a
 * HEAP buffer malloc'd to the exact size of the attacker-controlled input,
 * with no dependency on isis_print / isoclns_print / the rest of tcpdump.
 *
 * Input file format (interpreted by harness main(), NOT part of the target
 * function): a 4-byte big-endian "claimed length" header, followed by the
 * sub-TLV byte stream itself. main() reads the WHOLE file into ONE heap
 * allocation (malloc(fsz)); the sub-TLV pointer passed as `tptr` is
 * `raw + 4` and `ndo_snapend` is set to `raw + fsz` -- the true end of that
 * SAME allocation, mirroring how the real caller's ndo_snapend marks the
 * end of the actual captured packet buffer. The 4-byte header supplies the
 * `len` argument directly (the claimed/declared remaining length, decoupled
 * from how many bytes actually follow) -- exactly the real-world condition
 * this bug depends on (a length claim not checked against what was really
 * captured).
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
	const char *s;		/* string */
};

/* netdissect.h: netdissect_options, trimmed to the fields
 * isis_print_mt_capability_subtlv actually touches (ndo_printf via
 * ND_PRINT, ndo_snapend via ND_TCHECK2/ND_TTEST2); real field names + real
 * function-pointer signature. */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	const u_char *ndo_snapend;
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h, verbatim */
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* netdissect.h, verbatim -- the exact bounds-check machinery the
 * SPB_INSTANCE/SPBM_SI sub-cases rely on (their reads ARE properly
 * guarded; only the 2-byte sub-TLV header read at the top of the loop is
 * not, which is the actual CVE). */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))
#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))
#define ND_TTEST(var) ND_TTEST2(var, sizeof(var))
#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc
#define ND_TCHECK(var) ND_TCHECK2(var, sizeof(var))

/* extract.h, EXTRACT_16BITS/24BITS/32BITS copied VERBATIM (the portable,
 * byte-at-a-time form -- semantically identical to the LBL_ALIGN-native
 * variant the real header picks on this target). */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))
#define EXTRACT_24BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 0)))

/* print-isoclns.c, verbatim: the real truncation string this function
 * prints via `ND_PRINT((ndo, "%s", tstr));` on the trunc: path. */
static const char tstr[] = " [|isis]";

/* print-isoclns.c, verbatim: the two known MT-Capability sub-TLV codes +
 * their string table, exactly as isis_print_mt_capability_subtlv uses them
 * (real names/values, not stand-ins). */
#define ISIS_SUBTLV_SPB_INSTANCE      1
#define ISIS_SUBTLV_SPBM_SI           3

#define ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN          19
#define ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN   8

static const struct tok isis_mt_capability_subtlv_values[] = {
    { ISIS_SUBTLV_SPB_INSTANCE,      "SPB Instance" },
    { ISIS_SUBTLV_SPBM_SI,      "SPBM Service Identifier and Unicast Address" },
    { 0, NULL }
};

/* util-print.c, verbatim -- the function calls tok2str() on every sub-TLV
 * header, so this is real+correct, not a stub. */
static const char *
tok2str(const struct tok *lp, const char *fmt, u_int v)
{
	static char buf[128];

	if (lp != NULL) {
		while (lp->s != NULL) {
			if (lp->v == v)
				return (lp->s);
			++lp;
		}
	}
	if (fmt == NULL)
		fmt = "#%d";
	(void)snprintf(buf, sizeof(buf), fmt, v);
	return buf;
}

/* ------------------------------------------------------------------ */
/* TARGET FUNCTION -- verbatim from target/original_function.c        */
/* ------------------------------------------------------------------ */

static int
isis_print_mt_capability_subtlv(netdissect_options *ndo,
                                const uint8_t *tptr, int len)
{
  int stlv_type, stlv_len, tmp;

  while (len > 2)
  {
    stlv_type = *(tptr++);
    stlv_len  = *(tptr++);

    /* first lets see if we know the subTLVs name*/
    ND_PRINT((ndo, "\n\t      %s subTLV #%u, length: %u",
               tok2str(isis_mt_capability_subtlv_values, "unknown", stlv_type),
               stlv_type,
               stlv_len));

    len = len - 2;

    switch (stlv_type)
    {
      case ISIS_SUBTLV_SPB_INSTANCE:

          ND_TCHECK2(*tptr, ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN);

          ND_PRINT((ndo, "\n\t        CIST Root-ID: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, " %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", Path Cost: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", Prio: %d", EXTRACT_16BITS(tptr)));
          tptr = tptr + 2;
          ND_PRINT((ndo, "\n\t        RES: %d",
                    EXTRACT_16BITS(tptr) >> 5));
          ND_PRINT((ndo, ", V: %d",
                    (EXTRACT_16BITS(tptr) >> 4) & 0x0001));
          ND_PRINT((ndo, ", SPSource-ID: %d",
                    (EXTRACT_32BITS(tptr) & 0x000fffff)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", No of Trees: %x", *(tptr)));

          tmp = *(tptr++);

          len = len - ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN;

          while (tmp)
          {
            ND_TCHECK2(*tptr, ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN);

            ND_PRINT((ndo, "\n\t         U:%d, M:%d, A:%d, RES:%d",
                      *(tptr) >> 7, (*(tptr) >> 6) & 0x01,
                      (*(tptr) >> 5) & 0x01, (*(tptr) & 0x1f)));

            tptr++;

            ND_PRINT((ndo, ", ECT: %08x", EXTRACT_32BITS(tptr)));

            tptr = tptr + 4;

            ND_PRINT((ndo, ", BVID: %d, SPVID: %d",
                      (EXTRACT_24BITS(tptr) >> 12) & 0x000fff,
                      EXTRACT_24BITS(tptr) & 0x000fff));

            tptr = tptr + 3;
            len = len - ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN;
            tmp--;
          }

          break;

      case ISIS_SUBTLV_SPBM_SI:

          ND_TCHECK2(*tptr, 8);

          ND_PRINT((ndo, "\n\t        BMAC: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, "%04x", EXTRACT_16BITS(tptr)));
          tptr = tptr+2;

          ND_PRINT((ndo, ", RES: %d, VID: %d", EXTRACT_16BITS(tptr) >> 12,
                    (EXTRACT_16BITS(tptr)) & 0x0fff));

          tptr = tptr+2;
          len = len - 8;
          stlv_len = stlv_len - 8;

          while (stlv_len >= 4) {
            ND_TCHECK2(*tptr, 4);
            ND_PRINT((ndo, "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
                    (EXTRACT_32BITS(tptr) >> 31),
                    (EXTRACT_32BITS(tptr) >> 30) & 0x01,
                    (EXTRACT_32BITS(tptr) >> 24) & 0x03f,
                    (EXTRACT_32BITS(tptr)) & 0x0ffffff));

            tptr = tptr + 4;
            len = len - 4;
            stlv_len = stlv_len - 4;
          }

        break;

      default:
        break;
    }
  }
  return 0;

  trunc:
    ND_PRINT((ndo, "\n\t\t"));
    ND_PRINT((ndo, "%s", tstr));
    return(1);
}
/* ------------------------------------------------------------------ */
/* Harness main()                                                     */
/* ------------------------------------------------------------------ */

/* Real varargs consumer (not a pure no-op): a truly empty ndo_printf body
 * lets the optimizer prove stlv_type/stlv_len are otherwise unobserved and
 * fold the whole default-case loop body away at -O1, hiding the bug (seen
 * in other tcpdump direct-call harnesses in this dataset). Routing through
 * vfprintf(stderr, ...) is an opaque libc call the compiler can't elide,
 * so the OOB header read stays live. */
static int
fake_printf(netdissect_options *ndo, const char *fmt, ...)
{
	va_list ap;
	int ret;

	(void)ndo;
	va_start(ap, fmt);
	ret = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return ret;
}

int
main(int argc, char **argv)
{
	FILE *f;
	long sz;
	uint8_t *raw;
	uint32_t claimed_len;
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
	if (sz < 4) {
		/* Need at least the 4-byte claimed-length header. Not enough
		 * input to exercise the target meaningfully -- exit clean. */
		fclose(f);
		return 0;
	}
	if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 1; }

	/* ONE heap allocation, sized EXACTLY to the attacker-controlled
	 * input, so an ASAN redzone sits immediately past the last real
	 * byte -- required for the unguarded 2-byte header read to fault.
	 * Bytes [0,4) are the claimed-length header (harness-side framing,
	 * not part of the target function's own memory); bytes [4,sz) are
	 * the sub-TLV stream `tptr` points into -- both live in the SAME
	 * malloc'd chunk. */
	raw = (uint8_t *)malloc((size_t)sz);
	if (!raw) { fclose(f); return 1; }
	if (fread(raw, 1, (size_t)sz, f) != (size_t)sz) {
		free(raw);
		fclose(f);
		return 1;
	}
	fclose(f);

	claimed_len = ((uint32_t)raw[0] << 24) | ((uint32_t)raw[1] << 16) |
	              ((uint32_t)raw[2] << 8) | (uint32_t)raw[3];

	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_printf = fake_printf;
	/* Real caller behaviour: ndo_snapend marks the end of the captured
	 * packet buffer -- exactly this heap allocation's end here. */
	ndo.ndo_snapend = raw + sz;

	isis_print_mt_capability_subtlv(&ndo, raw + 4, (int)claimed_len);

	free(raw);
	return 0;
}

/*
 * Direct-call crash harness for cvf_d9b0c815 (CVE-2017-12998, tcpdump print-isoclns.c,
 * isis_print_extd_ip_reach) -- CWE-125 heap-buffer-overflow READ.
 *
 * Root cause (matches the frozen baseline dedup "isis_print_extd_ip_reach--isis_print--
 * isoclns_print" / summary "print-isoclns.c:2044:20 in isis_print_extd_ip_reach"):
 * in the AF_INET6 branch the code checks only ONE byte is available
 *     if (!ND_TTEST2(*tptr, 1)) return (0);
 * but then reads TWO bytes before touching the pointer again:
 *     status_byte=*(tptr++);      -- byte checked to be available
 *     bit_length=*(tptr++);       -- NOT checked -- 1-byte heap-buffer-overflow READ
 *                                    when exactly 1 byte remains in the captured buffer.
 *
 * ND_TTEST2 compares the read against ndo->ndo_snapend (the "end of captured packet"
 * pointer), NOT against any notion of the true allocation size, so to make the bug
 * observable under ASAN we mirror the real tcpdump packet buffer contract: the heap
 * buffer IS the captured region, sized EXACTLY to (and ndo_snapend pointing exactly at
 * the end of) whatever the input supplies -- so reading one byte past ndo_snapend is
 * also reading one byte past the actual malloc'd allocation.
 *
 * Input file format (argv[1]):
 *   byte 0     = afi selector: odd -> AF_INET6 (the buggy branch), even -> AF_INET
 *                (the AF_INET branch reads exactly 1 byte after checking 1 byte -- safe).
 *                any other value falls into isis_print_extd_ip_reach's "somebody is
 *                fooling us" branch and returns immediately (also safe).
 *   bytes 1..N = the packet body: malloc'd on the HEAP as an N-byte buffer and passed as
 *                tptr, with ndo->ndo_snapend set to exactly buf+N (the real ndo_snapend/
 *                captured-length contract). N==5 with an odd afi byte hits the exact
 *                off-by-one above (4 bytes metric + 1 byte status_byte leaves precisely
 *                one more byte "captured" per ND_TTEST2, but bit_length's read consumes a
 *                second byte that was never checked) -- deterministic CWE-125 regardless
 *                of the 5 bytes' actual values, so the 25 triggering inputs vary content
 *                (metric / status-byte patterns) at that fixed critical length. Other
 *                lengths/afi combinations (N<4 truncates immediately, N==4 truncates
 *                right at the branch, N>=6 gives the second read enough real bytes so it
 *                lands in-bounds and the function proceeds or cleanly truncates later,
 *                AF_INET with any N) are used for the 25 safe inputs to also exercise
 *                the metric/status/bit-length/prefix-copy code deeper without crashing.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* ---- minimal REAL type defs, mirroring netdissect.h's netdissect_options (only the
 * fields isis_print_extd_ip_reach / ND_TTEST2 / ND_PRINT actually touch) ---- */
typedef struct netdissect_options netdissect_options;
struct netdissect_options {
    const u_char *ndo_packetp;   /* beginning of captured packet */
    const u_char *ndo_snapend;   /* end of captured packet */
    int  (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* ---- ND_TTEST2 / ND_PRINT, VERBATIM from netdissect.h (references caller's "ndo") ---- */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))
#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))
#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* ---- EXTRACT_32BITS, VERBATIM from extract.h (byte-at-a-time form) ---- */
#define EXTRACT_32BITS(p) \
	((uint32_t)(((uint32_t)(*((const uint8_t *)(p) + 0)) << 24) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 1)) << 16) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 2)) << 8) | \
	            ((uint32_t)(*((const uint8_t *)(p) + 3)) << 0)))

/* ---- ISIS_MASK_TLV_EXTD_IP* macros, VERBATIM from print-isoclns.c ---- */
#define ISIS_MASK_TLV_EXTD_IP_UPDOWN(x)     ((x)&0x80)
#define ISIS_MASK_TLV_EXTD_IP_SUBTLV(x)     ((x)&0x40)
#define ISIS_MASK_TLV_EXTD_IP6_IE(x)        ((x)&0x40)
#define ISIS_MASK_TLV_EXTD_IP6_SUBTLV(x)    ((x)&0x20)

/* ---- real callee, matching the real signature (print-isoclns.c:1727) -- stubbed:
 * the fault is NOT inside this callee (it does its own ND_TCHECK2(*tptr,subl) before
 * reading), so it is only reachable when the SUBTLV bit is set in a >=6-byte-body input,
 * and a harmless stub keeps the harness free of addrtoname.c / tok2str table deps. ---- */
static int
isis_print_ip_reach_subtlv(netdissect_options *ndo,
                           const uint8_t *tptr, int subt, int subl,
                           const char *ident)
{
    (void)ndo; (void)tptr; (void)subt; (void)subl; (void)ident;
    return (1);
}

/* ---- real callees getname()/ipaddr_string() and getname6()/ip6addr_string(), matching
 * the real signatures (addrtoname.h:51-61) -- stubbed: they only format an address string
 * for printing and are not the fault site; the real versions pull in DNS/hash-table
 * machinery from the rest of the project. ---- */
static const char *
ipaddr_string(netdissect_options *ndo, const u_char *ap)
{
    (void)ndo; (void)ap;
    return "0.0.0.0";
}

static const char *
ip6addr_string(netdissect_options *ndo, const u_char *ap)
{
    (void)ndo; (void)ap;
    return "::";
}

/* no-op sink matching ndo_printf's signature -- never crashes/allocates */
static int
vb_printf(netdissect_options *ndo, const char *fmt, ...)
{
    (void)ndo; (void)fmt;
    return 0;
}

/* ---- target function, VERBATIM from target/original_function.c (real declared return
 * type is "static int" -- print-isoclns.c:2014-2015; meta.json's return_type is empty
 * because the byte-range extraction starts at the function name, but the caller side
 * (print-isoclns.c:2152 "uint8_t ext_ip_len" / int-typed comparisons) confirms "int"). ---- */
static int
isis_print_extd_ip_reach(netdissect_options *ndo,
                         const uint8_t *tptr, const char *ident, uint16_t afi)
{
    char ident_buffer[20];
    uint8_t prefix[sizeof(struct in6_addr)]; /* shared copy buffer for IPv4 and IPv6 prefixes */
    u_int metric, status_byte, bit_length, byte_length, sublen, processed, subtlvtype, subtlvlen;

    if (!ND_TTEST2(*tptr, 4))
        return (0);
    metric = EXTRACT_32BITS(tptr);
    processed=4;
    tptr+=4;

    if (afi == AF_INET) {
        if (!ND_TTEST2(*tptr, 1)) /* fetch status byte */
            return (0);
        status_byte=*(tptr++);
        bit_length = status_byte&0x3f;
        if (bit_length > 32) {
            ND_PRINT((ndo, "%sIPv4 prefix: bad bit length %u",
                   ident,
                   bit_length));
            return (0);
        }
        processed++;
    } else if (afi == AF_INET6) {
        if (!ND_TTEST2(*tptr, 1)) /* fetch status & prefix_len byte */
            return (0);
        status_byte=*(tptr++);
        bit_length=*(tptr++);
        if (bit_length > 128) {
            ND_PRINT((ndo, "%sIPv6 prefix: bad bit length %u",
                   ident,
                   bit_length));
            return (0);
        }
        processed+=2;
    } else
        return (0); /* somebody is fooling us */

    byte_length = (bit_length + 7) / 8; /* prefix has variable length encoding */

    if (!ND_TTEST2(*tptr, byte_length))
        return (0);
    memset(prefix, 0, sizeof prefix);   /* clear the copy buffer */
    memcpy(prefix,tptr,byte_length);    /* copy as much as is stored in the TLV */
    tptr+=byte_length;
    processed+=byte_length;

    if (afi == AF_INET)
        ND_PRINT((ndo, "%sIPv4 prefix: %15s/%u",
               ident,
               ipaddr_string(ndo, prefix),
               bit_length));
    else if (afi == AF_INET6)
        ND_PRINT((ndo, "%sIPv6 prefix: %s/%u",
               ident,
               ip6addr_string(ndo, prefix),
               bit_length));

    ND_PRINT((ndo, ", Distribution: %s, Metric: %u",
           ISIS_MASK_TLV_EXTD_IP_UPDOWN(status_byte) ? "down" : "up",
           metric));

    if (afi == AF_INET && ISIS_MASK_TLV_EXTD_IP_SUBTLV(status_byte))
        ND_PRINT((ndo, ", sub-TLVs present"));
    else if (afi == AF_INET6)
        ND_PRINT((ndo, ", %s%s",
               ISIS_MASK_TLV_EXTD_IP6_IE(status_byte) ? "External" : "Internal",
               ISIS_MASK_TLV_EXTD_IP6_SUBTLV(status_byte) ? ", sub-TLVs present" : ""));

    if ((afi == AF_INET  && ISIS_MASK_TLV_EXTD_IP_SUBTLV(status_byte))
     || (afi == AF_INET6 && ISIS_MASK_TLV_EXTD_IP6_SUBTLV(status_byte))
	) {
        /* assume that one prefix can hold more
           than one subTLV - therefore the first byte must reflect
           the aggregate bytecount of the subTLVs for this prefix
        */
        if (!ND_TTEST2(*tptr, 1))
            return (0);
        sublen=*(tptr++);
        processed+=sublen+1;
        ND_PRINT((ndo, " (%u)", sublen));   /* print out subTLV length */

        while (sublen>0) {
            if (!ND_TTEST2(*tptr,2))
                return (0);
            subtlvtype=*(tptr++);
            subtlvlen=*(tptr++);
            /* prepend the indent string */
            snprintf(ident_buffer, sizeof(ident_buffer), "%s  ",ident);
            if (!isis_print_ip_reach_subtlv(ndo, tptr, subtlvtype, subtlvlen, ident_buffer))
                return(0);
            tptr+=subtlvlen;
            sublen-=(subtlvlen+2);
        }
    }
    return (processed);
}

int
main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
        return 2;
    }

    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cannot open %s\n", argv[1]);
        return 2;
    }
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 2; }
    long fsz = ftell(f);
    if (fsz < 1) { fclose(f); return 2; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 2; }

    unsigned char afi_sel;
    if (fread(&afi_sel, 1, 1, f) != 1) { fclose(f); return 2; }
    uint16_t afi = (afi_sel & 1u) ? AF_INET6 : AF_INET;

    long n = fsz - 1;
    if (n < 0) n = 0;
    if (n == 0) n = 1; /* keep a real (small) heap allocation even for a 1-byte file */

    /* HEAP buffer that IS the captured packet body ("tptr"), sized EXACTLY to the bytes
     * supplied -- ndo_snapend below is set to point exactly at its end, mirroring the
     * real ndo_packetp/ndo_snapend contract, so any read ND_TTEST2 mis-clears is also a
     * real ASAN heap-buffer-overflow. */
    unsigned char *buf = (unsigned char *)malloc((size_t)n);
    if (!buf) { fclose(f); return 2; }
    size_t got = fread(buf, 1, (size_t)n, f);
    fclose(f);
    if (got < (size_t)n) memset(buf + got, 0, (size_t)n - got);

    netdissect_options ndo;
    memset(&ndo, 0, sizeof(ndo));
    ndo.ndo_packetp = buf;
    ndo.ndo_snapend = buf + n;
    ndo.ndo_printf = vb_printf;

    static const char ident[] = "  ";

    int rc = isis_print_extd_ip_reach(&ndo, (const uint8_t *)buf, ident, afi);
    printf("isis_print_extd_ip_reach(afi=%u, body_bytes=%ld) -> %d\n", (unsigned)afi, n, rc);

    free(buf);
    return 0;
}

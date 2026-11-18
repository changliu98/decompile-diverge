/* Direct-call crash harness for tcpdump rx_cache_find
 * (CVE-2018-14466, CWE-125, print-rx.c).
 *
 * rx_cache_find() searches the (process-lifetime) rx_cache[] table for an
 * entry matching the packet's RX header, comparing (among other fields):
 *
 *     rxent->serviceId == EXTRACT_32BITS(&rxh->serviceId) &&
 *
 * struct rx_header's `serviceId` field is only 2 bytes wide (nd_uint16_t)
 * AND is the LAST field in the struct (sizeof(struct rx_header) == 28,
 * serviceId at offset 26). EXTRACT_32BITS() unconditionally reads 4 bytes
 * from that address -> it walks 2 bytes past the end of struct rx_header.
 * rx_print() (the real caller) only checks that
 * `ndo->ndo_snapend - bp >= sizeof(struct rx_header)` (28 bytes) before
 * calling rx_cache_find() -- it never guarantees the extra 2 bytes past
 * the struct are captured. If `rxh` points into a heap buffer exactly 28
 * (or up to 29) bytes long, this walks straight past the end of the
 * allocation -> heap-buffer-overflow READ inside EXTRACT_32BITS, matching
 * baseline dedup_token "EXTRACT_32BITS--rx_cache_find--rx_print" and
 * baseline.cwe CWE-125 exactly. (The earlier `EXTRACT_32BITS(&rxh->callNumber)`
 * read, offset 8 size 4, is unconditional too -- a buffer shorter than 12
 * bytes overflows there instead, same target function / same dedup
 * function-stack, same CWE-125 heap-overflow READ class.)
 *
 * The upstream fix (commit c24922e692a5) changes both reads of serviceId
 * (here and in the sibling rx_cache_insert()) from EXTRACT_32BITS to
 * EXTRACT_16BITS, matching the field's real 2-byte width.
 *
 * rx_cache_find() only reaches the vulnerable serviceId read if the three
 * preceding comparisons (callnum/client/server) already matched some
 * rx_cache[] entry. rx_cache[] is a file-scope static array -- zero-
 * initialized at process start, and this harness never calls
 * rx_cache_insert() -- so on a fresh run every entry's callnum/client/
 * server/dport is exactly {0,0.0.0.0,0.0.0.0,0}. Driving the search into
 * the vulnerable read is then just a matter of feeding a zero callNumber
 * field, a zeroed (calloc'd) `struct ip` (ip_src == ip_dst == 0.0.0.0),
 * and sport == 0: the very first cache slot (rx_cache_hint == 0 on a
 * fresh process) matches on all three guard fields and evaluation proceeds
 * into the serviceId read.
 *
 * main() reads the whole input file into a HEAP buffer sized EXACTLY to
 * the file length (no slack, so ASAN's redzone sits immediately after the
 * "captured packet" bytes -- mirrors the real capture buffer / snapend
 * semantics: rx_print()'s caller only ever hands rx_cache_find() a pointer
 * into however much of the packet was actually captured) and calls
 * rx_cache_find() on it directly, once.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>   /* ntohl -- what tcpdump's netdissect-stdinc.h
                             includes for this */
#include <netinet/in.h>  /* struct in_addr */

/* ---- minimal but faithful type/macro defs the function needs ---- */
/* (real names verbatim from netdissect.h / extract.h / print-rx.c) */

typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned short u_short;

/* extract.h -- native (non-LBL_ALIGN) x86_64 unaligned-load variant
 * (verbatim; this is the branch that applies on x86_64, which is what
 * the ASAN build here runs on) */
#if defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 409)
#define UNALIGNED_OK	__attribute__((no_sanitize_undefined))
#elif defined(__has_attribute)
#if __has_attribute(no_sanitize)
#define UNALIGNED_OK	__attribute__((no_sanitize("undefined")))
#else
#define UNALIGNED_OK
#endif
#else
#define UNALIGNED_OK
#endif

static inline uint32_t UNALIGNED_OK
EXTRACT_32BITS(const void *p)
{
	return ((uint32_t)ntohl(*(const uint32_t *)(p)));
}

/* netdissect.h -- UNALIGNED_MEMCPY, native (non-LBL_ALIGN) x86_64 variant
 * (verbatim: the processor natively handles unaligned loads, so it's
 * plain memcpy()) */
#define UNALIGNED_MEMCPY(p, q, l)	memcpy((p), (q), (l))

/* print-rx.c -- struct rx_header (verbatim field-for-field; the real
 * fields are nd_uintN_t byte-array typedefs, which have the same size/
 * alignment/offset as the plain uintN_t scalars used here -- sizeof == 28
 * either way, matching the offsets rx_cache_find's own reads are computed
 * from) */
struct rx_header {
	uint32_t epoch;
	uint32_t cid;
	uint32_t callNumber;
	uint32_t seq;
	uint32_t serial;
	uint8_t type;
	uint8_t flags;
	uint8_t userStatus;
	uint8_t securityIndex;
	uint16_t spare;
	uint16_t serviceId;
};

/* ip.h -- struct ip. rx_cache_find only ever touches ip_src/ip_dst (by
 * field name, never by raw offset arithmetic), so only those two fields'
 * real names + 4-byte width matter here; the preceding fields are kept
 * (verbatim names) purely for documentation and collapsed to plain
 * scalars since their exact width has no bearing on this function's
 * behaviour. */
struct ip {
	uint8_t  ip_vhl;
	uint8_t  ip_tos;
	uint16_t ip_len;
	uint16_t ip_id;
	uint16_t ip_off;
	uint8_t  ip_ttl;
	uint8_t  ip_p;
	uint16_t ip_sum;
	struct in_addr ip_src;
	struct in_addr ip_dst;
};

/* print-rx.c -- struct rx_cache_entry + the cache globals rx_cache_find
 * searches (verbatim) */
struct rx_cache_entry {
	uint32_t	callnum;	/* Call number (net order) */
	struct in_addr	client;		/* client IP address (net order) */
	struct in_addr	server;		/* server IP address (net order) */
	int		dport;		/* server port (host order) */
	u_short		serviceId;	/* Service identifier (net order) */
	uint32_t	opcode;		/* RX opcode (host order) */
};

#define RX_CACHE_SIZE	64

static struct rx_cache_entry	rx_cache[RX_CACHE_SIZE];

static int	rx_cache_hint = 0;

/* ---- verbatim target function (target/original_function.c), unchanged ---- */
static int
rx_cache_find(const struct rx_header *rxh, const struct ip *ip, int sport,
	      int32_t *opcode)
{
	int i;
	struct rx_cache_entry *rxent;
	uint32_t clip;
	uint32_t sip;

	UNALIGNED_MEMCPY(&clip, &ip->ip_dst, sizeof(uint32_t));
	UNALIGNED_MEMCPY(&sip, &ip->ip_src, sizeof(uint32_t));

	/* Start the search where we last left off */

	i = rx_cache_hint;
	do {
		rxent = &rx_cache[i];
		if (rxent->callnum == EXTRACT_32BITS(&rxh->callNumber) &&
		    rxent->client.s_addr == clip &&
		    rxent->server.s_addr == sip &&
		    rxent->serviceId == EXTRACT_32BITS(&rxh->serviceId) &&
		    rxent->dport == sport) {

			/* We got a match! */

			rx_cache_hint = i;
			*opcode = rxent->opcode;
			return(1);
		}
		if (++i >= RX_CACHE_SIZE)
			i = 0;
	} while (i != rx_cache_hint);

	/* Our search failed */
	return(0);
}
/* ---- end verbatim target function ---- */

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 1;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror("fopen");
		return 1;
	}
	if (fseek(fp, 0, SEEK_END) != 0) {
		perror("fseek");
		fclose(fp);
		return 1;
	}
	long len = ftell(fp);
	if (len < 0) {
		perror("ftell");
		fclose(fp);
		return 1;
	}
	rewind(fp);

	/* Heap buffer, sized to EXACTLY the file length (no slack) so ASAN's
	 * redzone sits immediately after the real "captured packet" data --
	 * mirrors the real capture buffer tcpdump allocates per-packet, and
	 * the ndo_snapend semantics rx_print() (the real caller) uses to
	 * bound rxh. */
	size_t alloc_len = (size_t)len > 0 ? (size_t)len : 1;
	u_char *data = malloc(alloc_len);
	if (!data) {
		perror("malloc");
		fclose(fp);
		return 1;
	}
	if (len > 0 && fread(data, (size_t)len, 1, fp) != 1) {
		fprintf(stderr, "short read\n");
		fclose(fp);
		free(data);
		return 1;
	}
	fclose(fp);

	/* struct ip -- a SEPARATE, always fully-sized, zeroed allocation.
	 * This is not the field under test: the real caller derives `ip`
	 * from an EARLIER, independently-bounds-checked part of the packet
	 * (ip_print()'s own struct ip *), so it never aliases the rx_header
	 * buffer. Zeroed so ip_src == ip_dst == 0.0.0.0, matching every
	 * (zero-initialized) rx_cache[] entry's client/server fields on a
	 * fresh process -- this makes the cache-lookup match logic always
	 * proceed into the vulnerable serviceId comparison instead of being
	 * masked by an unrelated client/server mismatch. */
	struct ip *ip = calloc(1, sizeof(struct ip));
	if (!ip) {
		perror("calloc");
		free(data);
		return 1;
	}

	int32_t opcode = 0;
	int sport = 0;   /* matches every rx_cache[] entry's zero-initialized dport */

	(void)rx_cache_find((const struct rx_header *)data, ip, sport, &opcode);

	printf("rx_cache_find done, len=%ld, opcode=%d\n", len, opcode);

	free(ip);
	free(data);
	return 0;
}

/*
 * Direct-call crash harness for cvf_d89565f9 (CVE-2017-13032, tcpdump print-radius.c,
 * print_attr_string) -- CWE-125 heap-buffer-overflow READ.
 *
 * print_attr_string() decodes a single RADIUS attribute's TLV value. It is a
 * self-contained leaf: given (ndo, data, length, attr_code) it walks `data` for
 * up to `length` bytes and prints it, guided only by ND_TCHECK2/ND_TTEST2
 * (which compare pointers against ndo->ndo_snapend -- the "end of captured
 * packet" marker) -- no other project state is touched. Two independent
 * out-of-bounds reads live in the verbatim function body:
 *
 *  (1) TUNNEL_CLIENT_END / TUNNEL_SERVER_END / TUNNEL_PRIV_GROUP /
 *      TUNNEL_ASSIGN_ID / TUNNEL_CLIENT_AUTH / TUNNEL_SERVER_AUTH
 *      (original_function.c:32) -- `if (*data <= 0x1F)` dereferences `*data`
 *      BEFORE the `if (length < 1)` bounds check two lines later, so a
 *      zero-length attribute (length==0, i.e. ND_TCHECK2(data[0],0) trivially
 *      passes because the check is for <= 0 bytes) reads one byte past the
 *      captured buffer.
 *  (2) The trailing `for (i=0; *data && i < length ; i++, data++)` loop
 *      (original_function.c:56, the historical CVE-2017-13032 crash site,
 *      upstream print-radius.c:550) evaluates `*data` BEFORE `i < length`
 *      due to left-to-right `&&` short-circuiting -- so once `data` has
 *      walked to exactly `length` consumed (non-NUL) bytes, the loop peeks
 *      one byte past the end of the captured region before discovering it
 *      should have stopped.
 *
 * Both are pure "declared length says stop here, but the code reads one
 * further" bugs, so the harness's job is just to make the *actual* heap
 * allocation end exactly where "declared length" (or "captured"/snapend)
 * says it does -- then any of these code paths reading past it is a real
 * ASAN heap-buffer-overflow.
 *
 * Input file format (argv[1]):
 *   byte 0      = attr_code (0-255, used as the function's u_short attr_code)
 *   byte 1      = declared_length (0-255, used as the function's u_int length)
 *   bytes 2..N  = payload; malloc'd on the HEAP with size == (N-2) bytes
 *                 EXACTLY (the attacker-controlled "declared/captured" data);
 *                 ndo->ndo_snapend is set to data + (N-2), i.e. the true end
 *                 of the heap allocation, mirroring the real capture buffer.
 *
 * A crash lands inside print_attr_string with AddressSanitizer:
 * heap-buffer-overflow READ, matching CWE-125 / the frozen baseline dedup
 * "print_attr_string--radius_attrs_print--radius_print".
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/* ---- minimal but REAL type/macro defs (real names, from netdissect.h /
 * netdissect-stdinc.h / print-radius.c) ---- */

typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;

typedef struct netdissect_options netdissect_options;
struct netdissect_options {
	const u_char *ndo_packetp;	/* global pointer to beginning of current packet */
	const u_char *ndo_snapend;	/* global pointer to end of current packet */
	/* pointer to function to do regular output (netdissect.h) */
	int (*ndo_printf)(netdissect_options *, const char *fmt, ...);
};

/* netdissect.h -- verbatim */
#define IS_NOT_NEGATIVE(x) (((x) > 0) || ((x) == 0))

#define ND_TTEST2(var, l) \
  (IS_NOT_NEGATIVE(l) && \
	((uintptr_t)ndo->ndo_snapend - (l) <= (uintptr_t)ndo->ndo_snapend && \
         (uintptr_t)&(var) <= (uintptr_t)ndo->ndo_snapend - (l)))

#define ND_TCHECK2(var, l) if (!ND_TTEST2(var, l)) goto trunc

#define ND_PRINT(STUFF) (*ndo->ndo_printf)STUFF

/* extract.h -- byte-at-a-time EXTRACT_16BITS (verbatim, non-UNALIGNED_OK arm) */
#define EXTRACT_16BITS(p) \
	((uint16_t)(((uint16_t)(*((const uint8_t *)(p) + 0)) << 8) | \
	            ((uint16_t)(*((const uint8_t *)(p) + 1)) << 0)))

/* netdissect.h -- struct tok + tok2str/tok2strbuf (verbatim, util-print.c) */
struct tok {
	u_int v;		/* value */
	const char *s;		/* string */
};

#define TOKBUFSIZE 128

static const char *
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

static const char *
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

/* print-radius.c -- verbatim attribute-code constants + rfc4675 table + tstr */
#define RFC4675_TAGGED   0x31
#define RFC4675_UNTAGGED 0x32

static const struct tok rfc4675_tagged[] = {
    { RFC4675_TAGGED,   "Tagged" },
    { RFC4675_UNTAGGED, "Untagged" },
    { 0, NULL}
};

#define EGRESS_VLAN_NAME   58
#define TUNNEL_CLIENT_END  66
#define TUNNEL_SERVER_END  67
#define TUNNEL_PASS        69
#define TUNNEL_PRIV_GROUP  81
#define TUNNEL_ASSIGN_ID   82
#define TUNNEL_CLIENT_AUTH 90
#define TUNNEL_SERVER_AUTH 91

static const char tstr[] = " [|radius]";

/* ---- target function, VERBATIM from target/original_function.c ---- */
static void
print_attr_string(netdissect_options *ndo,
                  register const u_char *data, u_int length, u_short attr_code)
{
   register u_int i;

   ND_TCHECK2(data[0],length);

   switch(attr_code)
   {
      case TUNNEL_PASS:
           if (length < 3)
           {
              ND_PRINT((ndo, "%s", tstr));
              return;
           }
           if (*data && (*data <=0x1F) )
              ND_PRINT((ndo, "Tag[%u] ", *data));
           else
              ND_PRINT((ndo, "Tag[Unused] "));
           data++;
           length--;
           ND_PRINT((ndo, "Salt %u ", EXTRACT_16BITS(data)));
           data+=2;
           length-=2;
        break;
      case TUNNEL_CLIENT_END:
      case TUNNEL_SERVER_END:
      case TUNNEL_PRIV_GROUP:
      case TUNNEL_ASSIGN_ID:
      case TUNNEL_CLIENT_AUTH:
      case TUNNEL_SERVER_AUTH:
           if (*data <= 0x1F)
           {
              if (length < 1)
              {
                 ND_PRINT((ndo, "%s", tstr));
                 return;
              }
              if (*data)
                ND_PRINT((ndo, "Tag[%u] ", *data));
              else
                ND_PRINT((ndo, "Tag[Unused] "));
              data++;
              length--;
           }
        break;
      case EGRESS_VLAN_NAME:
           ND_PRINT((ndo, "%s (0x%02x) ",
                  tok2str(rfc4675_tagged,"Unknown tag",*data),
                  *data));
           data++;
           length--;
        break;
   }

   for (i=0; *data && i < length ; i++, data++)
       ND_PRINT((ndo, "%c", (*data < 32 || *data > 126) ? '.' : *data));

   return;

   trunc:
      ND_PRINT((ndo, "%s", tstr));
}
/* ---- end verbatim target function ---- */

static int
fake_printf(netdissect_options *ndo, const char *fmt, ...)
{
	(void)ndo;
	va_list ap;
	va_start(ap, fmt);
	int r = vfprintf(stderr, fmt, ap);
	va_end(ap);
	return r;
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <input-file>\n", argv[0]);
		return 2;
	}

	FILE *fp = fopen(argv[1], "rb");
	if (!fp) {
		perror("fopen");
		return 2;
	}
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 2; }
	long fsz = ftell(fp);
	if (fsz < 2) { fclose(fp); return 2; } /* need attr_code + declared_length header bytes */
	rewind(fp);

	unsigned char hdr[2];
	if (fread(hdr, 1, 2, fp) != 2) { fclose(fp); return 2; }
	u_short attr_code = (u_short)hdr[0];
	u_int declared_length = (u_int)hdr[1];

	long paylen = fsz - 2;
	size_t alloc_len = (size_t)paylen; /* may legitimately be 0 */

	/* HEAP buffer sized to EXACTLY the payload length -- ASAN's redzone sits
	 * immediately after it (even for a 0-byte allocation), mirroring the
	 * real per-packet capture buffer whose end is ndo_snapend. */
	unsigned char *data = (unsigned char *)malloc(alloc_len);
	if (alloc_len > 0 && !data) {
		fclose(fp);
		return 2;
	}
	if (alloc_len > 0) {
		size_t got = fread(data, 1, alloc_len, fp);
		if (got != alloc_len) {
			fclose(fp);
			free(data);
			return 2;
		}
	}
	fclose(fp);

	netdissect_options ndo;
	memset(&ndo, 0, sizeof(ndo));
	ndo.ndo_packetp = data;
	/* Only the actual payload bytes are "captured" -- matches the real
	 * caller, where ndo_snapend marks the end of what was captured off
	 * the wire, independent of any length field encoded inside the packet. */
	ndo.ndo_snapend = data + alloc_len;
	ndo.ndo_printf = fake_printf;

	print_attr_string(&ndo, data, declared_length, attr_code);

	free(data);
	return 0;
}

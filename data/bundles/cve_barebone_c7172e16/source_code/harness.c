/* cve_barebone direct-call harness for cve_c7172e16 (pjproject / pjsip)
 * Target: get_name_len  (pjlib-util/src/pjlib-util/dns.c -- static, recursive DNS
 *   name-length walker used while parsing a received DNS response packet)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * fix_commit 5311aee398ae9d623829a6bad7b679a193c9e199 adds, immediately before the
 * 2-byte pj_memcpy() that decodes a DNS name-compression pointer:
 *     if (p + 1 >= max)
 *         return PJLIB_UTIL_EDNSINNAMEPTR;
 * Pre-fix, get_name_len only ever validates that the CURRENT byte `p` is inside
 * [pkt,max) before dereferencing it (`while (*p)` / `(*p & 0xc0)`); it never checks
 * that a SECOND byte is available before doing
 *     pj_memcpy(&offset, p, 2);
 * If the walk (an ordinary sequence of length-prefixed labels, each hop bounds-
 * checked correctly) lands EXACTLY on the last valid byte of the packet buffer
 * (p == max-1) and that byte's top two bits are `11` (a DNS name-compression
 * marker, RFC 1035 S4.1.4), the 2-byte memcpy reads p[0] (valid, == max-1) and
 * p[1] (== max itself, one byte past the packet's real allocation) -- a 1-byte
 * heap-buffer-overflow READ. That is exactly the access the added check now blocks
 * (p+1 == max there triggers the new early return).
 *
 * get_name_len is called DIRECTLY here on a heap buffer built entirely from the raw
 * input file bytes: pkt=start=buf, max=buf+n. This mirrors exactly how the real
 * callers (get_name() and pj_dns_parse_packet(), both in this same TU) hand it a
 * raw, attacker-controlled DNS response packet -- get_name_len needs no other
 * project state, so nothing beyond its own pjlib primitives below is required to
 * isolate it faithfully.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>          /* real htons()/ntohs() -- what pj_htons/pj_ntohs call on POSIX */

/* ---- pjlib base typedefs, verbatim (pjlib/include/pj/types.h) ---- */
typedef unsigned short  pj_uint16_t;
typedef unsigned char   pj_uint8_t;
typedef size_t          pj_size_t;
typedef int             pj_status_t;

/* ---- pjlib-util/include/pjlib-util/errno.h + pjlib/include/pj/errno.h (real,
 * documented values -- PJLIB_UTIL_ERRNO_START+43, per the header's own comment). ---- */
#define PJLIB_UTIL_EDNSINNAMEPTR   320043
#define PJ_SUCCESS                 0

/* ---- pjlib/include/pj/string.h: PJ_INLINE(void*) pj_memcpy(...) { return memcpy(...); }
 * verbatim body, real name/signature (PJ_INLINE just expands to a plain inline fn on
 * this POSIX target). ---- */
static void *pj_memcpy(void *dst, const void *src, pj_size_t size)
{
    return memcpy(dst, src, size);
}

/* ---- pjlib/src/pj/sock_bsd.c: PJ_DEF(pj_uint16_t) pj_htons()/pj_ntohs() -- verbatim
 * bodies, real names. On this POSIX/BSD-sockets build, pjproject's own implementation
 * is a straight passthrough to the system htons()/ntohs(). ---- */
static pj_uint16_t pj_htons(pj_uint16_t hostshort) { return htons(hostshort); }
static pj_uint16_t pj_ntohs(pj_uint16_t netshort)  { return ntohs(netshort); }

/* ================= TARGET (VERBATIM, byte-for-byte target/original_function.c) =================
 * noinline + called only through a volatile function pointer below, so the crash
 * keeps its own stack frame (dc_batch matches the target's NAME in the ASAN
 * backtrace) and the call can't be proven dead / folded away. */
__attribute__((noinline))
static pj_status_t get_name_len(int rec_counter, const pj_uint8_t *pkt, 
                                const pj_uint8_t *start, const pj_uint8_t *max, 
                                int *parsed_len, int *name_len)
{
    const pj_uint8_t *p;
    pj_status_t status;

    /* Limit the number of recursion */
    if (rec_counter > 10) {
        /* Too many name recursion */
        return PJLIB_UTIL_EDNSINNAMEPTR;
    }

    if (start >= max)
        return PJLIB_UTIL_EDNSINNAMEPTR;

    *name_len = *parsed_len = 0;
    p = start;
    while (*p) {
        if ((*p & 0xc0) == 0xc0) {
            /* Compression is found! */
            int ptr_len = 0;
            int dummy;
            pj_uint16_t offset;

            /* Get the 14bit offset */
            pj_memcpy(&offset, p, 2);
            offset ^= pj_htons((pj_uint16_t)(0xc0 << 8));
            offset = pj_ntohs(offset);

            /* Check that offset is valid */
            if (offset >= max - pkt)
                return PJLIB_UTIL_EDNSINNAMEPTR;

            /* Get the name length from that offset. */
            status = get_name_len(rec_counter+1, pkt, pkt + offset, max, 
                                  &dummy, &ptr_len);
            if (status != PJ_SUCCESS)
                return status;

            *parsed_len += 2;
            *name_len += ptr_len;

            return PJ_SUCCESS;
        } else {
            unsigned label_len = *p;

            /* Check that label length is valid.
             * Each label consists of an octet length (of size 1) followed
             * by the octet of the specified length (label_len). Then it
             * must be followed by either another label's octet length or
             * a zero length octet (that terminates the sequence).
             */
            if (p+1+label_len+1 > max)
                return PJLIB_UTIL_EDNSINNAMEPTR;

            p += (label_len + 1);
            *parsed_len += (label_len + 1);

            if (*p != 0)
                ++label_len;
            
            *name_len += label_len;
        }
    }
    ++p;
    (*parsed_len)++;

    return PJ_SUCCESS;
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 2; }
    long sz = ftell(fp);
    if (sz < 0) sz = 0;
    if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 2; }
    size_t n = (size_t)sz;

    /* HEAP-allocate the input, ASAN-guarded, EXACTLY n bytes for n>0 so the redzone
     * starts precisely at buf+n -- that boundary IS `max` below. */
    pj_uint8_t *pkt = (pj_uint8_t *)malloc(n ? n : 1);
    if (!pkt) { fclose(fp); return 2; }
    size_t got = n ? fread(pkt, 1, n, fp) : 0;
    fclose(fp);
    if (got != n) n = got;                     /* short read: shrink to what we actually got */

    /* get_name_len's real calling convention (get_name()/pj_dns_parse_packet(), same
     * TU): pkt = start of the whole received packet, start = where THIS name begins
     * (here: offset 0), max = one-past the last valid packet byte. The whole file IS
     * the packet -- exactly what a libFuzzer-style entry point for this parser would
     * hand it. */
    const pj_uint8_t *start = pkt;
    const pj_uint8_t *max   = pkt + n;
    int parsed_len = 0, name_len = 0;

    pj_status_t (*volatile fn)(int, const pj_uint8_t *, const pj_uint8_t *,
                                const pj_uint8_t *, int *, int *) = get_name_len;
    fn(0, pkt, start, max, &parsed_len, &name_len);

    free(pkt);
    return 0;
}

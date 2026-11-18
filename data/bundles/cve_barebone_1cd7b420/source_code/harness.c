/* cve_barebone direct-call harness for CVE-2022-24793 (pjproject pjlib-util DNS parser)
 * Target: get_name_len  (pjlib-util/src/pjlib-util/dns.c)
 * Bug class: CWE-125 heap-buffer-overflow READ.
 *
 * get_name_len() validates each uncompressed label's length against the PACKET ORIGIN
 * (`pkt`) instead of the CURRENT parse position (`p`):
 *     if (pkt + label_len > max) return PJLIB_UTIL_EDNSINNAMEPTR;
 * On the first label p==pkt so this happens to be correct; after p has advanced past one
 * or more labels the check no longer bounds anything real (a label merely <= the whole
 * packet size always passes), so `p += (label_len + 1)` can walk `p` past `max`, and the
 * very next line dereferences it: `if (*p != 0) ++label_len;` -- a heap-buffer-overflow
 * READ. Upstream's fix (9fae8f43accef8ea65d4a8ae9cdf297c46cfe29a) re-bases the check on
 * `p`: `if (p + 1 + label_len + 1 > max) return ...;`. The root cause is entirely inside
 * get_name_len's own body (a bounds check using the wrong pointer) -- exactly the class of
 * bug this benchmark targets.
 *
 * Expected crash stack (dedup-relevant frame): get_name_len -- main. get_name_len is
 * called through a volatile function pointer in main() so it can't be inlined away and
 * disappear from the ASAN backtrace (it is naturally self-recursive too, which already
 * keeps it out-of-line at -O1, but the pointer indirection makes that non-negotiable); the
 * recursive self-calls inside get_name_len's own body are untouched (same source bytes).
 *
 * pj_status_t/pj_uint8_t/pj_uint16_t (pjlib/include/pj/types.h), PJ_SUCCESS (same file,
 * enum pj_constants_), PJLIB_UTIL_EDNSINSIZE/PJLIB_UTIL_EDNSINNAMEPTR
 * (pjlib-util/include/pjlib-util/errno.h, literal values from that file's own comments:
 * PJLIB_UTIL_ERRNO_START+41 = 320041, +43 = 320043) and pj_memcpy/pj_htons/pj_ntohs (real
 * one-line bodies: pjlib/include/pj/string.h's pj_memcpy is `memcpy(dst,src,size)`;
 * pjlib/src/pj/sock_bsd.c's pj_htons/pj_ntohs are `htons(...)`/`ntohs(...)`) are copied
 * verbatim/real-named. No other pjlib machinery (pools, sockets, logging) is on this path.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

/* ---- pjlib base typedefs (real names, pjlib/include/pj/types.h) ---- */
typedef int             pj_status_t;
typedef unsigned char    pj_uint8_t;
typedef unsigned short   pj_uint16_t;

/* ---- PJ_SUCCESS (pjlib/include/pj/types.h, enum pj_constants_) ---- */
#define PJ_SUCCESS 0

/* ---- pjlib-util error codes (pjlib-util/include/pjlib-util/errno.h, literal values from
 * that file's own comments) ---- */
#define PJLIB_UTIL_EDNSINSIZE      320041   /* PJLIB_UTIL_ERRNO_START+41 */
#define PJLIB_UTIL_EDNSINNAMEPTR   320043   /* PJLIB_UTIL_ERRNO_START+43 */

/* ---- pjlib wrappers: REAL bodies (pjlib/include/pj/string.h pj_memcpy is `return
 * memcpy(dst,src,size);`; pjlib/src/pj/sock_bsd.c pj_htons/pj_ntohs are `return
 * htons(...)/ntohs(...)`) ---- */
static void *pj_memcpy(void *dst, const void *src, size_t size) { return memcpy(dst, src, size); }
static pj_uint16_t pj_htons(pj_uint16_t hostshort) { return htons(hostshort); }
static pj_uint16_t pj_ntohs(pj_uint16_t netshort) { return ntohs(netshort); }

/* ======================================================================================== */
/* TARGET FUNCTION -- copied BYTE-FOR-BYTE from data_cve/cve_1cd7b420/target/original_function.c */
/* ======================================================================================== */
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

	    /* Check that label length is valid */
	    if (pkt+label_len > max)
		return PJLIB_UTIL_EDNSINNAMEPTR;

	    p += (label_len + 1);
	    *parsed_len += (label_len + 1);

	    if (*p != 0)
		++label_len;
	    
	    *name_len += label_len;

	    if (p >= max)
		return PJLIB_UTIL_EDNSINSIZE;
	}
    }
    ++p;
    (*parsed_len)++;

    return PJ_SUCCESS;
}
/* ==== end verbatim target function ==== */

/* ---- driver -------------------------------------------------------------------------------
 * Reads argv[1] VERBATIM into a HEAP buffer (malloc, ASAN-guarded): the file bytes ARE the
 * DNS packet. pkt == start == the buffer base, mirroring the real caller pattern
 * `get_name_len(0, pkt, start, max, ...)` from parse_query()/parse_rr() with the name at the
 * very start of the region handed in; max == pkt+size is the exact end of the allocation, so
 * a read at or past it is a genuine heap-buffer-overflow. */
int main(int argc, char **argv)
{
	if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 64; }
	FILE *fp = fopen(argv[1], "rb");
	if (!fp) { perror("fopen"); return 64; }
	if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 64; }
	long fsz = ftell(fp);
	if (fsz < 0) { fclose(fp); return 64; }
	if (fseek(fp, 0, SEEK_SET) != 0) { fclose(fp); return 64; }

	size_t n = (size_t)fsz;
	pj_uint8_t *pkt = (pj_uint8_t *)malloc(n ? n : 1);
	if (!pkt) { fclose(fp); return 64; }
	size_t got = n ? fread(pkt, 1, n, fp) : 0;
	fclose(fp);

	if (got == 0) { free(pkt); return 0; }   /* empty file: nothing to parse, clean exit */

	int parsed_len = 0, name_len = 0;
	const pj_uint8_t *max = pkt + got;

	/* volatile function pointer: forbid inlining get_name_len into main() so it stays a
	 * real stack frame (dc_batch requires the target function in the crash stack). */
	pj_status_t (*volatile fn)(int, const pj_uint8_t *, const pj_uint8_t *,
	                            const pj_uint8_t *, int *, int *) = get_name_len;
	pj_status_t status = fn(0, pkt, pkt, max, &parsed_len, &name_len);

	fprintf(stderr, "status=%d parsed_len=%d name_len=%d\n", status, parsed_len, name_len);

	free(pkt);
	return 0;
}

/*
 * Direct-call crash harness for cvf_11075ce0 (CVE-2017-13035, tcpdump print-isoclns.c,
 * isis_print_id) — CWE-125 heap-buffer-overflow READ.
 *
 * isis_print_id() is a self-contained leaf function: it takes a raw byte pointer + a
 * declared length and unconditionally reads SYSTEM_ID_LEN (6) bytes from that pointer
 * in its first loop, regardless of what the caller says id_len actually is. Real
 * tcpdump callers pass a pointer into the captured packet together with a
 * packet-derived "LAN address length" (id_len) that can be SHORTER than 6 (IS-IS TLVs
 * carry a 1-byte address-length field) — the fixed 6-iteration loop then walks past
 * the end of the true id_len-sized field. We reproduce that exact mismatch directly:
 * a heap buffer sized to id_len bytes, passed with that id_len, calling isis_print_id
 * exactly like the real caller (e.g. print-isoclns.c:2598 `isis_print_id(tptr, lan_alen)`)
 * does.
 *
 * Input file format (argv[1]):
 *   byte 0      = id_len (0-255, interpreted as int; matches the real packet's
 *                 1-byte address-length field)
 *   bytes 1..N  = the "id" bytes; N of them are malloc'd on the HEAP and passed as cp.
 *
 * Crash condition: N < 6 (or more precisely N less than whatever isis_print_id will
 * actually read for the given id_len) -> heap-buffer-overflow READ inside
 * isis_print_id, matching the frozen baseline dedup
 * "isis_print_id--isis_print--isoclns_print" / CWE-125.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- minimal REAL macro defs from print-isoclns.c / addrtoname.c ---- */
#define ETHER_ADDR_LEN  6
#define SYSTEM_ID_LEN   ETHER_ADDR_LEN
#define NODE_ID_LEN     SYSTEM_ID_LEN+1
#define LSP_ID_LEN      SYSTEM_ID_LEN+2

/* ---- target function, VERBATIM from source_code/print-isoclns.c:1643-1663
 * (target/original_function.c splice omits the "static char *" return-type
 * line that precedes the byte range; reconstructed here from the real source). */
static char *
isis_print_id(const uint8_t *cp, int id_len)
{
    int i;
    static char id[sizeof("xxxx.xxxx.xxxx.yy-zz")];
    char *pos = id;

    for (i = 1; i <= SYSTEM_ID_LEN; i++) {
        snprintf(pos, sizeof(id) - (pos - id), "%02x", *cp++);
	pos += strlen(pos);
	if (i == 2 || i == 4)
	    *pos++ = '.';
	}
    if (id_len >= NODE_ID_LEN) {
        snprintf(pos, sizeof(id) - (pos - id), ".%02x", *cp++);
	pos += strlen(pos);
    }
    if (id_len == LSP_ID_LEN)
        snprintf(pos, sizeof(id) - (pos - id), "-%02x", *cp);
    return (id);
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

    unsigned char first;
    if (fread(&first, 1, 1, f) != 1) { fclose(f); return 2; }
    int id_len = (int)first;

    long n = fsz - 1;
    if (n < 1) n = 1; /* keep a real (small) heap allocation even for a 1-byte file */

    /* HEAP buffer sized to the DECLARED field length (n bytes follow byte 0),
     * mirroring the real packet buffer that only actually holds id_len-ish bytes. */
    unsigned char *cp = (unsigned char *)malloc((size_t)n);
    if (!cp) { fclose(f); return 2; }

    size_t got = fread(cp, 1, (size_t)n, f);
    fclose(f);
    /* zero any bytes the file didn't supply so the read content is deterministic
     * (does not affect whether/where the overflow happens - that's governed by
     * the malloc size vs. isis_print_id's fixed read pattern). */
    if (got < (size_t)n) memset(cp + got, 0, (size_t)n - got);

    char *result = isis_print_id((const uint8_t *)cp, id_len);
    printf("isis_print_id(id_len=%d, buf_bytes=%ld) -> %s\n", id_len, n, result);

    free(cp);
    return 0;
}

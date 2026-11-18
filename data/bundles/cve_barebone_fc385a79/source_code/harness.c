/*
 * cve_barebone direct-call harness for riot-os/riot gnrc_rpl_srh_process
 * CVE fix commit 34dc1757f5621be48e226cfebb2f4c63505b5360
 *
 * Real type/macro/callee definitions copied verbatim (trimmed of comments)
 * from the vulnerable tree:
 *   sys/include/byteorder.h        (be_uintNN_t / network_uintNN_t)
 *   sys/include/net/ipv6/addr.h    (ipv6_addr_t, ipv6_addr_is_multicast)
 *   sys/include/net/ipv6/hdr.h     (ipv6_hdr_t)
 *   sys/include/net/gnrc/rpl/srh.h (gnrc_rpl_srh_t)
 *   sys/include/net/gnrc/ipv6/ext/rh.h (GNRC_IPV6_EXT_RH_* enum)
 *   sys/net/gnrc/routing/rpl/srh/gnrc_rpl_srh.c
 *       (GNRC_RPL_SRH_* macros, _contains_multiple_of_my_addr,
 *        gnrc_rpl_srh_process -- byte-for-byte from target/original_function.c)
 *
 * gnrc_netif_get_by_ipv6_addr() is a stub (always "not found") -- it is not
 * on the crash path for the triggering inputs (the OOB read/write inside
 * gnrc_rpl_srh_process's own body happens before it is ever called).
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/* ---- byteorder.h (verbatim field layout) ---- */

typedef union __attribute__((packed)) {
    uint16_t u16;
    uint8_t u8[2];
} be_uint16_t;

typedef union __attribute__((packed)) {
    uint32_t u32;
    uint8_t u8[4];
    uint16_t u16[2];
} be_uint32_t;

typedef union __attribute__((packed)) {
    uint64_t u64;
    uint8_t u8[8];
    uint16_t u16[4];
    uint32_t u32[2];
} be_uint64_t;

typedef be_uint16_t network_uint16_t;
typedef be_uint32_t network_uint32_t;
typedef be_uint64_t network_uint64_t;

/* ---- net/ipv6/addr.h (verbatim) ---- */

typedef union {
    uint8_t u8[16];
    network_uint16_t u16[8];
    network_uint32_t u32[4];
    network_uint64_t u64[2];
} ipv6_addr_t;

static inline bool ipv6_addr_is_multicast(const ipv6_addr_t *addr)
{
    return (addr->u8[0] == 0xff);
}

/* ---- net/ipv6/hdr.h (verbatim struct layout) ---- */

typedef struct __attribute__((packed)) {
    network_uint32_t v_tc_fl;
    network_uint16_t len;
    uint8_t nh;
    uint8_t hl;
    ipv6_addr_t src;
    ipv6_addr_t dst;
} ipv6_hdr_t;

/* ---- net/gnrc/rpl/srh.h (verbatim struct layout) ---- */

typedef struct __attribute__((packed)) {
    uint8_t nh;
    uint8_t len;
    uint8_t type;
    uint8_t seg_left;
    uint8_t compr;
    uint8_t pad_resv;
    uint16_t resv;
} gnrc_rpl_srh_t;

/* ---- net/gnrc/ipv6/ext/rh.h (verbatim enum) ---- */

enum {
    GNRC_IPV6_EXT_RH_ERROR = 0,
    GNRC_IPV6_EXT_RH_AT_DST,
    GNRC_IPV6_EXT_RH_FORWARDED,
};

/* ---- net/gnrc/netif/internal.h: gnrc_netif_get_by_ipv6_addr ----
 * Stub: never on the crash path for the triggering inputs (the vulnerable
 * OOB access happens earlier, in gnrc_rpl_srh_process's own body). */

typedef struct gnrc_netif gnrc_netif_t;

static gnrc_netif_t *gnrc_netif_get_by_ipv6_addr(const ipv6_addr_t *addr)
{
    (void)addr;
    return NULL;
}

/* DEBUG(...) is compiled out in the real tree (ENABLE_DEBUG 0); replicate
 * that as a pure no-op so we don't need ipv6_addr_to_str()/addr_str. */
#define DEBUG(...) do {} while (0)

/* ---- sys/net/gnrc/routing/rpl/srh/gnrc_rpl_srh.c (verbatim macros) ---- */

#define GNRC_RPL_SRH_PADDING(X)     ((X & 0xF0) >> 4)
#define GNRC_RPL_SRH_COMPRE(X)      (X & 0x0F)
#define GNRC_RPL_SRH_COMPRI(X)      ((X & 0xF0) >> 4)

/* ---- sys/net/gnrc/routing/rpl/srh/gnrc_rpl_srh.c (verbatim) ---- */

static void *_contains_multiple_of_my_addr(const ipv6_addr_t *dst,
                                           const gnrc_rpl_srh_t *rh,
                                           unsigned num_addr,
                                           unsigned compri_addr_len)
{
    ipv6_addr_t addr;
    uint8_t *addr_vec = (uint8_t *) (rh + 1);
    bool found = false;
    uint8_t pref_elided = GNRC_RPL_SRH_COMPRI(rh->compr);
    uint8_t addr_len = compri_addr_len;
    uint8_t found_pos = 0;

    memcpy(&addr, dst, pref_elided);
    for (unsigned i = 0; i < num_addr; i++) {
        uint8_t *addr_vec_ptr = &addr_vec[i * compri_addr_len];

        if (i == num_addr - 1) {
            pref_elided = GNRC_RPL_SRH_COMPRE(rh->compr);
            addr_len = sizeof(ipv6_addr_t) - pref_elided;
        }
        memcpy(&addr.u8[pref_elided], addr_vec_ptr, addr_len);
        if (gnrc_netif_get_by_ipv6_addr(&addr) != NULL) {
            if (found && ((i - found_pos) > 1)) {
                DEBUG("RPL SRH: found multiple addresses that belong to me - "
                      "discard\n");
                return addr_vec_ptr;
            }
            found_pos = i;
            found = true;
        }
    }
    return NULL;
}

/* ==== BEGIN target/original_function.c (byte-for-byte) ==== */
int gnrc_rpl_srh_process(ipv6_hdr_t *ipv6, gnrc_rpl_srh_t *rh, void **err_ptr)
{
    ipv6_addr_t addr;
    uint8_t *addr_vec = (uint8_t *) (rh + 1), *current_address;
    uint8_t num_addr;
    uint8_t current_pos, pref_elided, addr_len, compri_addr_len;
    const uint8_t new_seg_left = rh->seg_left - 1;

    assert(rh->seg_left > 0);
    num_addr = (((rh->len * 8) - GNRC_RPL_SRH_PADDING(rh->pad_resv) -
                 (16 - GNRC_RPL_SRH_COMPRE(rh->compr))) /
                (16 - GNRC_RPL_SRH_COMPRI(rh->compr))) + 1;

    DEBUG("RPL SRH: %u addresses in the routing header\n", (unsigned) num_addr);

    if (rh->seg_left > num_addr) {
        DEBUG("RPL SRH: number of segments left > number of addresses - "
              "discard\n");
        *err_ptr = &rh->seg_left;
        return GNRC_IPV6_EXT_RH_ERROR;
    }

    current_pos = num_addr - new_seg_left;
    pref_elided = (new_seg_left)
                ? GNRC_RPL_SRH_COMPRI(rh->compr)
                : GNRC_RPL_SRH_COMPRE(rh->compr);
    compri_addr_len = sizeof(ipv6_addr_t) - GNRC_RPL_SRH_COMPRI(rh->compr);
    addr_len = sizeof(ipv6_addr_t) - pref_elided;
    memcpy(&addr, &ipv6->dst, pref_elided);
    current_address = &addr_vec[(current_pos - 1) * compri_addr_len];
    memcpy(&addr.u8[pref_elided], current_address, addr_len);

    if (ipv6_addr_is_multicast(&ipv6->dst)) {
        DEBUG("RPL SRH: found a multicast destination address - discard\n");
        return GNRC_IPV6_EXT_RH_ERROR;
    }
    if (ipv6_addr_is_multicast(&addr)) {
        DEBUG("RPL SRH: found a multicast address in next address - discard\n");
        return GNRC_IPV6_EXT_RH_ERROR;
    }

    /* check if multiple addresses of my interface exist */
    if ((*err_ptr = _contains_multiple_of_my_addr(&ipv6->dst, rh, num_addr,
                                                  compri_addr_len))) {
        return GNRC_IPV6_EXT_RH_ERROR;
    }
    rh->seg_left = new_seg_left;
    memcpy(current_address, &ipv6->dst.u8[pref_elided], addr_len);

    DEBUG("RPL SRH: Next hop: %s at position %d\n",
          ipv6_addr_to_str(addr_str, &addr, sizeof(addr_str)), current_pos);

    memcpy(&ipv6->dst, &addr, sizeof(ipv6->dst));

    return GNRC_IPV6_EXT_RH_FORWARDED;
}
/* ==== END target/original_function.c ==== */

/*
 * Input file layout (raw bytes, all heap-allocated so ASAN guards every
 * boundary):
 *   [0:40)  ipv6_hdr_t   (v_tc_fl 4, len 2, nh 1, hl 1, src 16, dst 16)
 *   [40:48) gnrc_rpl_srh_t fixed header (nh,len,type,seg_left,compr,
 *           pad_resv,resv[2])
 *   [48:)   address vector -- exactly as many bytes as the file provides
 *           beyond the 48-byte prefix; this is the REAL invariant from the
 *           RIOT RPL SRH wire format (the extension header carries exactly
 *           rh->len*8 bytes of address data after its own 8-byte fixed
 *           part), so a file that supplies zero (or too few) trailing bytes
 *           together with a header whose GNRC_RPL_SRH_* macros make
 *           (rh->len*8) < padding + (16 - COMPRE) reproduces the exact
 *           integer-underflow bug the fix commit guards against: num_addr
 *           wraps to a large uint8_t while the real buffer stays tiny/zero,
 *           and the very next memcpy() reads/writes far past it.
 */
int main(int argc, char **argv)
{
    if (argc < 2) {
        return 0;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        return 0;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return 0;
    }
    long fsz = ftell(f);
    if (fsz < 48) {
        fclose(f);
        return 0;
    }
    rewind(f);

    uint8_t *filebuf = (uint8_t *)malloc((size_t)fsz);
    if (!filebuf) {
        fclose(f);
        return 0;
    }
    size_t got = fread(filebuf, 1, (size_t)fsz, f);
    fclose(f);
    if (got != (size_t)fsz) {
        free(filebuf);
        return 0;
    }

    uint8_t *ipv6_buf = (uint8_t *)malloc(sizeof(ipv6_hdr_t));
    memcpy(ipv6_buf, filebuf, sizeof(ipv6_hdr_t));

    size_t rh_total = (size_t)fsz - sizeof(ipv6_hdr_t); /* 8-byte header + addr vec */
    uint8_t *rh_buf = (uint8_t *)malloc(rh_total);
    memcpy(rh_buf, filebuf + sizeof(ipv6_hdr_t), rh_total);

    free(filebuf);

    ipv6_hdr_t *ipv6 = (ipv6_hdr_t *)ipv6_buf;
    gnrc_rpl_srh_t *rh = (gnrc_rpl_srh_t *)rh_buf;

    void *err_val = NULL;
    void **err_ptr = &err_val;

    int ret = gnrc_rpl_srh_process(ipv6, rh, err_ptr);

    free(ipv6_buf);
    free(rh_buf);

    fprintf(stderr, "ret=%d\n", ret);
    return 0;
}

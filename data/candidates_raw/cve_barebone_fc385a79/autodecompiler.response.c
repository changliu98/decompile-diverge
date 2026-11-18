static int _srh_process_ipv6_header(ipv6_hdr_t *ipv6, gnrc_rpl_srh_t *rh, void **next)
{
    unsigned char *addr_vec = ((unsigned char *) (((void *) ((rh) + 1))));
    unsigned char seg_left = ((rh)->flags & 0x3f) - 1;
    unsigned char num_addr;
    ipv6_addr_t addr;
    unsigned char *current_address;
    unsigned char pref_elided, compri_addr_len, addr_len;
    unsigned char current_pos;
    int res;

    do { if (!(((rh->seg_left > 0))) { ___assert_fail("rh->seg_left > 0", "harness.c", 165, "int gnrc_rpl_srh_process(ipv6_hdr_t *, gnrc_rpl_srh_t *, void **)"); } } while (0);
    num_addr = ((((rh->hlen * 8) - ((rh->cpos & 0xf0) >> 4)) - (16 - (rh->cpos & 0x0f))) / (16 - ((rh->cpos & 0xf0) >> 4)) + 1);

    while (1) {
        if (rh->seg_left > num_addr) {
            continue;
        }

        current_pos = num_addr - seg_left;

        if (seg_left) {
            pref_elided = ((rh->cpos & 0xf0) >> 4);
        }
        else {
            pref_elided = (rh->cpos & 0x0f);
        }

        compri_addr_len = 16 - pref_elided;
        addr_len = 16 - pref_elided;

        memcpy(&addr, &ipv6->src, pref_elided);
        current_address = addr_vec + (current_pos - 1) * compri_addr_len;
        memcpy((unsigned char *) (&addr) + pref_elided, current_address, addr_len);

        if (ipv6_addr_is_multicast(&ipv6->src)) {
            while (1) {

                if (ipv6_addr_is_multicast(&addr)) {
                    continue;
                }

                break;
            }
        }

        if (ipv6_addr_is_multicast(&addr)) {
            while (1) {

                if (ipv6_addr_is_multicast(&addr)) {
                    continue;
                }

                break;
            }
        }

        *next = _contains_multiple_of_my_addr(&ipv6->src, rh, num_addr, compri_addr_len);

        if (*next != NULL) {
            res = 0;
            goto out;
        }

        rh->seg_left = seg_left;
        memcpy(current_address, &ipv6->src + pref_elided, addr_len);
        break;
    }

    ipv6->src = addr;
    res = 2;

out:
    return res;
}
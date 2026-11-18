int gnrc_rpl_srh_process(ipv6_hdr_t *ipv6, gnrc_rpl_srh_t *rh, void **err_ptr)
{
    unsigned char num_addr;
    unsigned char addr_len;
    unsigned char compri_addr_len;
    unsigned char pref_elided;
    unsigned char current_pos;
    unsigned char new_seg_left;
    unsigned char *addr_vec;
    unsigned char *current_address;
    ipv6_addr_t addr;

    do { if (!(rh->seg_left > 0)) __assert_fail("rh->seg_left > 0", "/work/harness.c", 165, "int gnrc_rpl_srh_process(ipv6_hdr_t *, gnrc_rpl_srh_t *, void **)"); } while (0);

    num_addr = ((rh->len * 8) - ((rh->pad_resv & 0xF0) >> 4) - (16 - (rh->compr & 0x0F))) / (16 - ((rh->compr & 0xF0) >> 4)) + 1;

    if (num_addr < rh->seg_left) {
        *err_ptr = &rh->seg_left;
        return 0;
    }

    new_seg_left = rh->seg_left - 1;

    if (new_seg_left == 0) {
        pref_elided = rh->compr & 0x0F;
    }
    else {
        pref_elided = (rh->compr & 0xF0) >> 4;
    }

    addr_len = 16 - ((rh->compr & 0xF0) >> 4);

    memcpy(&addr, &ipv6->dst, pref_elided);
    memcpy(((char *)&addr) + pref_elided, ((char *)rh) + (16 - pref_elided) * (num_addr - new_seg_left - 1) + 8, 16 - pref_elided);

    if (ipv6_addr_is_multicast(&ipv6->dst) || ipv6_addr_is_multicast(&addr)) {
        return 0;
    }

    *err_ptr = _contains_multiple_of_my_addr(&ipv6->dst, rh, num_addr, addr_len);
    if (*err_ptr) {
        return 0;
    }

    rh->seg_left = new_seg_left;

    current_pos = (16 - pref_elided) * (num_addr - new_seg_left - 1) + 8;
    addr_vec = ((char *)&ipv6->dst) + pref_elided;
    memcpy(((char *)rh) + current_pos, addr_vec, 16 - pref_elided);

    ipv6->dst = addr;

    return 2;
}
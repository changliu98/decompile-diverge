int gnrc_rpl_srh_process(struct ipv6_hdr *hdr, struct gnrc_rpl_srh *rh, struct rh_header *rh_out) {
    struct ipv6_addr *addr = &rh->prefix[0];
    unsigned char seg_left = rh->seg_left - 1;
    
    assert(rh->seg_left > 0);

    unsigned char i = (rh->nmf << 3) - ((rh->cmpri & 0xF0) >> 4) - (16 - (rh->cmpre & 0x0F)) / (16 - ((rh->cmpre & 0xF0) >> 4)) + 1;

    if (rh->seg_left <= i) {
        rh_out->next = &rh->seg_left;
        return 0;
    }

    unsigned char n = i - seg_left;
    unsigned char k;
    if (seg_left != 0) {
        k = (rh->cmpri & 0xF0) >> 4;
    } else {
        k = rh->cmpri & 0x0F;
    }
    
    unsigned char m = k;
    unsigned char l = 16 - k;
    unsigned char o = 16 - m;

    struct ipv6_addr tmp;
    memcpy(&tmp, &hdr->dst, m);
    
    struct ipv6_addr *new_addr = &addr[n - 1] + l;
    memcpy((unsigned char *)&tmp + m, new_addr, o);

    if (ipv6_addr_is_multicast(&hdr->dst)) {
        return 0;
    }
    if (ipv6_addr_is_multicast(&tmp)) {
        return 0;
    }

    struct ipv6_addr *res = _contains_multiple_of_my_addr(&hdr->dst, rh, i, l);
    rh_out->next = res;
    if (res != NULL) {
        return 0;
    }

    rh->seg_left = seg_left;
    memcpy(new_addr, &hdr->dst, o);
    
    hdr->dst = tmp;
    
    return 2;
}
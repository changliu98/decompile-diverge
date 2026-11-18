int _dns_encode_HTTPS(struct dns_packet *packet, struct dns_rr *rr) {
    int ret = 0;
    int len1 = 0;
    int len2 = 0;
    char domain[256];
    memset(domain, 0, sizeof(domain));
    
    uint64_t start_ptr = 0;
    uint64_t domain_ptr = 0;
    uint64_t rr_head_ptr = 0;
    int out1 = 0;
    int out2 = 0;
    uint64_t svcparm = 0;

    svcparm = dns_get_HTTPS_svcparm_start(rr, domain, 256, &out1, &out2, domain, 256, &svcparm);
    if (svcparm == 0) {
        tlog_ext(4, "dns_encode.c", 0x2b6, "_dns_encode_HTTPS", 0, "get svcparm failed");
        return -1;
    }

    ret = _dns_encode_rr_head(packet, domain, len1, len2, out1, 0, &rr_head_ptr);
    if (ret < 0) {
        return -1;
    }

    start_ptr = (uint64_t)packet->ptr;

    if (_dns_left_len(packet) < 2) {
        tlog_ext(4, "dns_encode.c", 0x2c1, "_dns_encode_HTTPS", 0, "left len too small");
        return -1;
    }

    _dns_write_short(packet, (uint16_t)out2);
    ret = _dns_encode_domain(packet, domain);
    if (ret < 0) {
        return -1;
    }

    domain_ptr = (uint64_t)packet->ptr;

    while (svcparm != 0) {
        if ((uint64_t)packet->ptr - domain_ptr > rr->len) {
            if (_dns_left_len(packet) <= 0) {
                return -1;
            }
        }

        _dns_write_short(packet, *(uint16_t *)svcparm);
        _dns_write_short(packet, *(uint16_t *)(svcparm + 2));

        uint16_t svcparm_type = *(uint16_t *)svcparm;
        if (svcparm_type <= 6) {
            memcpy(packet->ptr, (void *)(svcparm + 4), *(uint16_t *)(svcparm + 2));
            packet->ptr += *(int16_t *)(svcparm + 2);
        } else {
            packet->ptr -= 4;
        }

        dns_get_HTTPS_svcparm_next(rr, &svcparm);
    }

    _dns_write_short(packet, (uint16_t)((uint64_t)packet->ptr - start_ptr));
    return 0;
}
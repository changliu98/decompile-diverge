int decode_multicast_vpn(void *p, const unsigned char *pp, char *buf, size_t buflen) {
    unsigned int len = *(unsigned int *)((char *)p + 8);
    unsigned char type;
    unsigned char addr_len;
    int ret_val;

    if (len - 2 > len || pp > len - 2) {
        return -2;
    }

    type = *pp++;
    addr_len = *pp++;

    snprintf(buf, buflen, "%s (0x%02x), %s: %u",
             tok2str(bgp_multicast_vpn_route_type_values, "unknown", type),
             type, "address length", addr_len);

    switch (type - 1) {
    case 0:
        if (len - 8 > len || pp > len - 8) {
            return -2;
        }
        {
            int slen = strlen(buf);
            char *bp = buf + slen;
            size_t blen = buflen - slen;
            char *rd = bgp_vpn_rd_print(p, pp);
            char *ip = bgp_vpn_ip_print(p, pp + 8, (addr_len - 8) * 8);
            snprintf(bp, blen, "%s%s", rd, ip);
        }
        break;

    case 1:
        if (len - 12 > len || pp > len - 12) {
            return -2;
        }
        {
            int slen = strlen(buf);
            char *bp = buf + slen;
            size_t blen = buflen - slen;
            char *rd = bgp_vpn_rd_print(p, pp);
            char *as_str = as_printf(astostr, 20, EXTRACT_32BITS(pp + 8));
            snprintf(bp, blen, "%s%s", rd, as_str);
        }
        break;

    case 2:
        if (len - 8 > len || pp > len - 8) {
            return -2;
        }
        {
            int slen = strlen(buf);
            char *bp = buf + slen;
            size_t blen = buflen - slen;
            char *rd = bgp_vpn_rd_print(p, pp);
            snprintf(bp, blen, "%s", rd);
            pp += 8;
            unsigned char sg_len = bgp_vpn_sg_print(p, pp, buf, buflen);
            unsigned char rem_len = addr_len - sg_len;
            if (rem_len > 0 || rem_len == 0) {
                if (len - rem_len > len || pp > len - rem_len) {
                    return -2;
                }
                slen = strlen(buf);
                bp = buf + slen;
                blen = buflen - slen;
                char *ip = bgp_vpn_ip_print(p, pp, rem_len * 8);
                snprintf(bp, blen, "%s", ip);
            }
        }
        break;

    case 3:
        if (len - 8 > len || pp > len - 8) {
            return -2;
        }
        {
            int slen = strlen(buf);
            char *bp = buf + slen;
            size_t blen = buflen - slen;
            char *rd = bgp_vpn_rd_print(p, pp);
            snprintf(bp, blen, "%s", rd);
            pp += 8;
            bgp_vpn_sg_print(p, pp, buf, buflen);
        }
        break;

    case 4:
        if (len - 8 > len || pp > len - 8) {
            return -2;
        }
        {
            int slen = strlen(buf);
            char *bp = buf + slen;
            size_t blen = buflen - slen;
            char *rd = bgp_vpn_rd_print(p, pp);
            char *as_str = as_printf(astostr, 20, EXTRACT_32BITS(pp + 8));
            snprintf(bp, blen, "%s%s", rd, as_str);
            pp += 8;
            bgp_vpn_sg_print(p, pp, buf, buflen);
        }
        break;

    case 5:
    case 6:
        break;
    }

    ret_val = addr_len + 2;
    return ret_val;
}
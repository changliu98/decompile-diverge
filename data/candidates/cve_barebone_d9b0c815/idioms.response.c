static int isis_print_extd_ip_reach(struct netdissect_options *ndo, void *rtattr, char *prefix, int afi)
{
    struct rtattr *tb[-1];
    struct rtattr *attr;
    unsigned int len;
    unsigned int sublen;
    unsigned int metric;
    unsigned int bit_length;
    unsigned int byte_length;
    unsigned int processed;
    unsigned int processeda;
    unsigned char status_byte;
    struct in_addr in4addr;
    struct in6_addr in6addr;
    int (*ndo_printf)(struct netdissect_options *, char *fmt, ...);
    int (*ndo_printfa)(struct netdissect_options *, char *fmt, ...);
    char subprefix[20];
    if ((((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) )) > (ndo->ndo_snapend) ||
        ((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) > (ndo->ndo_snapend))
        return (0);
    metric = (((unsigned int) (((unsigned char *)rtattr)[(0)])) << 24 | (((unsigned int) (((unsigned char *)rtattr)[(1)])) << 16 | (((unsigned int) (((unsigned char *)rtattr)[(2)])) << 8 | (((unsigned int) (((unsigned char *)rtattr)[(3)])))));
    rtattr += 4;
    if (afi == 2) {
        if ((((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) )) > (ndo->ndo_snapend) ||
            ((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) > (ndo->ndo_snapend))
            return (0);
        status_byte = *((unsigned char *)rtattr++);
        bit_length = (status_byte & 0x3f);
        if (bit_length > 32 / 8 * 8) {
            ndo->ndo_printf(ndo, "%sIPv4 prefix: bad bit length %u", prefix,
                    bit_length);
            return (0);
        }
        processed = sizeof(struct rtattr);
    } else if (afi == 10) {
        if ((((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) )) > (ndo->ndo_snapend) ||
            ((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) > (ndo->ndo_snapend))
            return (0);
        status_byte = *((unsigned char *)rtattr++);
        bit_length = *((unsigned char *)rtattr++);
        if (bit_length > 128 / 8 * 8) {
            ndo->ndo_printf(ndo, "%sIPv6 prefix: bad bit length %u", prefix,
                    bit_length);
            return (0);
        }
        processed = sizeof(struct rtattr) + 1;
    } else
        return (0);
    byte_length = (bit_length + 7) / 8;
    if ((((unsigned char *)rtattr) + ( ((unsigned int)byte_length)*((unsigned int)sizeof(unsigned char))+4U -1) & ~(4U -1)) > (ndo->ndo_snapend) ||
        ((unsigned char *)rtattr) + ( ((unsigned int)byte_length)*((unsigned int)sizeof(unsigned char))+4U -1) > (ndo->ndo_snapend))
        return (0);
    rtattr_addrs_init(&in4addr, &in6addr, 0);
    rtattr_addrs_add(&in4addr, &in6addr, rtattr, byte_length);
    rtattr += byte_length;
    processed += byte_length;
    if (afi == 2) {
        ndo_printf = ndo->ndo_printf;
        ndo_printfa = ndo->ndo_printfa;
        ndo_printf(ndo, "%sIPv4 prefix: %15s/%u", prefix,
                rtattr_addr2str(ndo, &in4addr), bit_length);
    } else if (afi == 10) {
        ndo_printf = ndo->ndo_printf;
        ndo_printfa = ndo->ndo_printfa;
        ndo_printf(ndo, "%sIPv6 prefix: %s/%u", prefix,
                rtattr_addr6str(ndo, &in6addr), bit_length);
    }
    ndo->ndo_printf(ndo, ", Distribution: %s, Metric: %u",
            status_byte & 0x80 ? "down" : "up", metric);
    if (afi == 2 && status_byte & 0x40)
        ndo->ndo_printf(ndo, ", sub-TLVs present");
    else if (afi == 10 && status_byte & 0x20)
        ndo->ndo_printf(ndo, ", sub-TLVs present");
    if (afi == 2 && status_byte & 0x40 ||
        afi == 10 && status_byte & 0x20) {
        if ((((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) )) > (ndo->ndo_snapend) ||
            ((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) > (ndo->ndo_snapend))
            return (0);
        sublen = *((unsigned char *)rtattr);
        processed += sublen + 1;
        ndo->ndo_printf(ndo, " (%u)", sublen);
        while (sublen > 0) {
            if ((((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) )) > (ndo->ndo_snapend) ||
                ((unsigned char *)rtattr) + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) > (ndo->ndo_snapend))
                return (0);
            attr = (struct rtattr *)rtattr;
            rtattr = (void *)((char *)rtattr + (( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (attr)->rta_len));
            if (rtattr < (void *)((char *)rtattr + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (sublen - 1)))
                return (0);
            if (rtattr < (void *)((char *)rtattr + ( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (sublen - 1)))
                return (0);
            sublen -= (( ((sizeof(struct rtattr))+4U -1) & ~(4U -1) ) + (attr)->rta_len);
            if (rtattr_print(ndo, attr, prefix) == 0)
                return (0);
        }
    }
    return (processed);
}
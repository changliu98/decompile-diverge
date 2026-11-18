static int print_ssrr(struct netdissect_options *ndo, unsigned char *options, unsigned int oplen, unsigned char flags)
{
    unsigned char *end; unsigned char *p;
    int (*printf)(struct netdissect_options *ndo, char *fmt, ...);
    if (oplen != mp_dss_len(options, 1) &&
        oplen != mp_dss_len(options, 0))
        return (0);
    if (flags & 0x02)
        return (0);
    if (options[3] & 0x10)
        ndo->ndo_printf(" fin");
    p = options + 4;
    if (options[3] & 0x01) {
        ndo->ndo_printf(" ack ");
        if (options[3] & 0x02) {
            printf = ndo->ndo_printf;
            printf(ndo, "%lu", mp_ullong(p));
            p += 8;
        } else {
            printf = ndo->ndo_printf;
            printf(ndo, "%u", mp_ullong(p));
            p += 4;
        }
    }
    if (options[3] & 0x04) {
        ndo->ndo_printf(" seq ");
        if (options[3] & 0x08) {
            printf = ndo->ndo_printf;
            printf(ndo, "%lu", mp_ullong(p));
            p += 4;
        } else {
            printf = ndo->ndo_printf;
            printf(ndo, "%u", mp_ullong(p));
            p += 2;
        }
        printf = ndo->ndo_printf;
        printf(ndo, " subseq %u", mp_ullong(p));
        p += 2;
        printf = ndo->ndo_printf;
        printf(ndo, " len %u", mp_ullong(p));
        p += 2;
        if (mp_dss_len(options, 1) == oplen) {
            printf = ndo->ndo_printf;
            printf(ndo, " csum 0x%x", mp_ullong(p));
        }
    }
    return (1);
}
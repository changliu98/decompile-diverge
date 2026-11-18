__attribute__((used)) static int
frag_print(netdissect_options *ndo,
           register const u_char *bp, register u_int length)
{
    register const struct ip *dp = (const struct ip *)bp;
    register const struct ip *dpx;
    register u_int hlen;
    register u_int offset;
    int n;

    if (length < dp->ip_hl * 4 - sizeof(struct ip))
        goto trunc;
    if (dp->ip_hl * 4 > ndo->ndo_snapend - ndo->ndo_snapstart)
        goto trunc;
    if (dp->ip_off & IP_OFFMASK) {
        (*ndo->ndo_printf)(ndo, "frag (0x%08x:%d|%ld)",
            EXTRACT_32BITS(&dp->ip_id),
            EXTRACT_16BITS(&dp->ip_off) & IP_OFFMASK,
            (long)(EXTRACT_16BITS(&dpx->ip_len) + sizeof(struct ip) - (bp - (const u_char *)dpx) - sizeof(struct ip)));
    } else {
        (*ndo->ndo_printf)(ndo, "frag (%d|%ld)",
            EXTRACT_16BITS(&dp->ip_off) & IP_OFFMASK,
            (long)(EXTRACT_16BITS(&dpx->ip_len) + sizeof(struct ip) - (bp - (const u_char *)dpx) - sizeof(struct ip)));
    }
    if ((EXTRACT_16BITS(&dp->ip_off) & IP_OFFMASK) == 0) {
        (*ndo->ndo_printf)(ndo, " ");
        hlen = dp->ip_hl * 4;
        offset = 0;
    } else {
        hlen = sizeof(struct ip);
        offset = EXTRACT_16BITS(&dp->ip_off) & IP_OFFMASK;
    }
    n = EXTRACT_16BITS(&dpx->ip_len) + sizeof(struct ip) - (bp - (const u_char *)dpx) - hlen;
    if (hlen < ndo->ndo_snapend - ndo->ndo_snapstart && n > 0) {
        if (hlen < ndo->ndo_snapend - ndo->ndo_snapstart)
            print_unknown_data(ndo, bp+hlen, "\n\t", n);
        else
            (*ndo->ndo_printf)(ndo, "[|%s]", proto2name(dpx->ip_p));
    }
    return (hlen);

trunc:
    (*ndo->ndo_printf)(ndo, "[|frag]");
    return (-1);
}
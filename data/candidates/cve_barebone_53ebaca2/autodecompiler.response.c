void
isakmp_rfc3948_print(struct netdissect_options *ndo,
             register const u_char *cp, register int len, register int verbose)
{
    int plen;
    int padlen;
    int nh;
    int ret;

    if (len == 1 && (*cp & 0xff) == 0xff) {
        (*ndo->ndo_printf)(ndo, "isakmp-nat-keep-alive");
        return;
    }

    if (len < 4)
        goto trunc;

    if ((cp[0] == 0) && (cp[1] == 0) && (cp[2] == 0) && (cp[3] == 0)) {
        (*ndo->ndo_printf)(ndo, "NONESP-encap: ");
        isakmp_rfc3948_print(ndo, cp + 4, len - 4, verbose);
        return;
    }

    (*ndo->ndo_printf)(ndo, "UDP-encap: ");

    ret = esp_print(ndo, cp, len, verbose, &plen, &padlen);
    if (ret <= 0)
        return;

    cp += ret;
    len -= ret + padlen;
    nh = plen & 0xff;

    ip_print_inner(ndo, cp, len, nh, verbose);
    return;

trunc:
    (*ndo->ndo_printf)(ndo, "[|isakmp]");
}
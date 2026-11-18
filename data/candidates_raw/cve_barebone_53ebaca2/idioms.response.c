static void
isakmp_print(struct netdissect_options *ndo, u_char *bp, unsigned int length, u_char *next)
{
    int encap; int padlen; int advance;
    int nh;
    if (length == 1 && bp[0] == 0xff) {
        ndo->ndo_printf(ndo, "isakmp-nat-keep-alive");
        return;
    }
    if (length < 4) {
        ndo->ndo_printf(ndo, "[|isakmp]");
        return;
    }
    if (bp[0] == 0 && bp[1] == 0 && bp[2] == 0 && bp[3] == 0) {
        ndo->ndo_printf(ndo, "NONESP-encap: ");
        isakmp_ip_print(ndo, bp + 4, length - 4, next);
        return;
    }
    ndo->ndo_printf(ndo, "UDP-encap: ");
    advance = isakmp_udp_print(ndo, bp, length, next, &encap, &padlen);
    if (advance > 0) {
        bp += advance;
        length -= padlen + advance;
        nh = encap & 0xff;
        isakmp_ip_print(ndo, bp, length, nh, next);
    }
    return;
}
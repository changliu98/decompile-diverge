void
arp_print(netdissect_options *ndo,
            register const u_char *bp, register u_int length, register u_int caplen)
{
    register const struct atmarphdr *ap = (const struct atmarphdr *)bp;
    unsigned hrd, pro, op;
    int hln, pln, lnh, lnp;
    int phl, lnhl, lnpk, lnlk, lnph, lnpl;

    if (caplen < sizeof(struct atmarphdr) || length < sizeof(struct atmarphdr)) {
trunc:
 (*ndo->ndo_error)(ndo, "%s", "[|ARP]");
 (*ndo->ndo_default_print)(ndo, bp, caplen);
 return;
    }

    hrd = EXTRACT_16BITS(&ap->ar_hrd);
    pro = EXTRACT_16BITS(&ap->ar_pro);
    op = EXTRACT_16BITS(&ap->ar_op);

    switch (hrd) {

    case 1:
    case 7:
    case 15:
    case 19:
    case 21:
    case 23:
    case 25:
    case
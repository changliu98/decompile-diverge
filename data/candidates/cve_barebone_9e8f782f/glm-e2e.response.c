void isoclns_print(struct netdissect_options *ndo, const uint8_t *p, int length, int caplen) {
    uint8_t nlpid;

    if (caplen <= 1) {
        (*ndo->ndo_printf)(ndo, " [|iso]");
        return;
    }

    if (ndo->ndo_eflag) {
        const char *str = tok2str(nlpid_values, "Unknown NLPID(0x%02x)", *p);
        (*ndo->ndo_printf)(ndo, ", %s (0x%02x)", str, *p);
    }

    nlpid = *p;
    switch (nlpid) {
        case 0x00:
            (*ndo->ndo_printf)(ndo, "%s", ndo->ndo_eflag ? "" : "ISO NLPID 0x00 ");
            break;
        case 0x08:
            q933_print(ndo, p + 1, length - 1);
            break;
        case 0x81:
            if (clnp_print(ndo, p, length) == 0)
                print_unknown_data(ndo, p, "\n\t", caplen);
            break;
        case 0x82:
            esis_print(ndo, p, length);
            break;
        case 0x83:
            if (isis_print(ndo, p, length) == 0)
                print_unknown_data(ndo, p, "\n\t", caplen);
            break;
        case 0x8e:
            ip6_print(ndo, p + 1, length - 1);
            break;
        case 0xcc:
            ip_print(ndo, p + 1, length - 1);
            break;
        case 0xcf:
            ppp_print(ndo, p + 1, length - 1);
            break;
        default:
            if (!ndo->ndo_eflag)
                (*ndo->ndo_printf)(ndo, "Unknown NLPID 0x%02x ", *p);
            (*ndo->ndo_printf)(ndo, "%s", ndo->ndo_eflag ? "" : "ISO NLPID 0x00 ");
            if (caplen > 1)
                print_unknown_data(ndo, p, "\n\t", caplen);
            break;
    }
}
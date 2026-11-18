int print_ipsec_options(struct netdissect_options *ndo, unsigned char *ipsec, unsigned int length, int indent)
{
    int i;
    unsigned int optlen;
    unsigned char *optval;
    int j;
    for (i = 0; i < length; i += (optlen + 2)) {
        unsigned char type = ipsec[i];
        optlen = ipsec[i + 1];
        optval = ipsec + i + 2;
        ndo->ndo_printf("\n");
        for (j = indent; j > 0; j--)
            ndo->ndo_printf("\t");
        ndo->ndo_printf("%s", dh4opt_str(ndo, type));
        ndo->ndo_printf(" (%u)", optlen + 2);
        if (type == 6 || type == 42) {
            if (optlen < 4 || optlen % 4 != 0)
                return -1;
            for (j = 0; j < optlen; j += 4)
                ndo->ndo_printf(" %s",
                                 ipsec_addr_ntoa(ndo, optval + j));
        } else if (type == 119) {
            unsigned char *ptr = optval;
            while (ptr < optval + optlen) {
                ndo->ndo_printf(" ");
                ptr = ipsec_addr_ntoa_print(ndo, ptr, optval + optlen);
                if (ptr == ((void *)0))
                    return -1;
            }
        }
    }
    return 0;
}
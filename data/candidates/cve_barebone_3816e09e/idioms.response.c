static int mobility_opt_print(struct netdissect_options *ndo, unsigned char *bp, unsigned int len)
{
    unsigned int i = 0;
    unsigned int optlen;
    int (*ndo_printf)(struct netdissect_options *ndo, char *fmt, ...);
    int (*ndo_printf2)(struct netdissect_options *ndo, char *fmt, ...);
    char *str;
    unsigned int ho;
    for ( ; i < len; i += optlen ) {
        if ( ((char *) (void *) (bp + i)) > (char *) (void *) (ndo->ndo_snapend - 1) )
            return (1);
        if (bp[i] == 0)
            optlen = 1;
        else {
            if (i + 1 >= len || ((char *) (void *) (bp + i + 1)) > (char *) (void *) (ndo->ndo_snapend - 1))
                return (1);
            optlen = (bp[i + 1]) + 2;
        }
        if (i + optlen > len || ((char *) (void *) (bp + i + optlen)) > (char *) (void *) (ndo->ndo_snapend - 1))
            return (1);
        switch (bp[i]) {
        case 0:
            ndo->ndo_printf(ndo, "(pad1)");
            break;
        case 1:
            if (len - i < 2) {
                ndo->ndo_printf(ndo, "(padn: trunc)");
                return (1);
            }
            ndo->ndo_printf(ndo, "(padn)");
            break;
        case 2:
            if (len - i < 4) {
                ndo->ndo_printf(ndo, "(refresh: trunc)");
                return (1);
            }
            ndo_printf = ndo->ndo_printf;
            ndo_printf(ndo, "(refresh: %u)",
                       ((uint32_t)(ntohl((unsigned int)(*((unsigned int *) (void *) (bp + i + 2)))))) * 4);
            break;
        case 3:
            if (len - i < 18) {
                ndo->ndo_printf(ndo, "(altcoa: trunc)");
                return (1);
            }
            ndo_printf2 = ndo->ndo_printf;
            str = alt_coa_to_string(ndo, (char *) (void *) (bp + i + 2));
            ndo_printf2(ndo, "(alt-CoA: %s)", str);
            break;
        case 4:
            if (len - i < 6) {
                ndo->ndo_printf(ndo, "(ni: trunc)");
                return (1);
            }
            ndo_printf2 = ndo->ndo_printf;
            ho = ((uint32_t)(ntohl((unsigned int)(*((unsigned int *) (void *) (bp + i + 2))))));
            ndo_printf2(ndo, "(ni: ho=0x%04x co=0x%04x)",
                        ho, ((uint32_t)(ntohl((unsigned int)(*((unsigned int *) (void *) (bp + i + 4)))))));
            break;
        case 5:
            if (len - i < 12) {
                ndo->ndo_printf(ndo, "(auth: trunc)");
                return (1);
            }
            ndo->ndo_printf(ndo, "(auth)");
            break;
        default:
            if (len - i < 2) {
                ndo->ndo_printf(ndo, "(sopt_type %u: trunc)", bp[i]);
                return (1);
            }
            ndo->ndo_printf(ndo, "(type-0x%02x: len=%u)", bp[i], bp[i + 1]);
        }
    }
    return (0);
}
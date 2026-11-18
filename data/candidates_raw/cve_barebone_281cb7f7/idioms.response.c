int print_dh6opt(struct netdissect_options *ndo, unsigned char *pp, unsigned int length, int indent)
{
    unsigned int i;
    unsigned int optlen;
    unsigned int type;
    unsigned char *value;
    int j;
    int (*print)(struct netdissect_options *, char *, ...);
    for (i = 0; i < length; i += 4 + optlen) {
        type = (((u_int16_t)(((unsigned char *)(pp)[i])) << 8) | ((u_int16_t)(((unsigned char *)(pp)[i + 1]))));
        optlen = (((u_int16_t)(((unsigned char *)(pp)[i + 2])) << 8) | ((u_int16_t)(((unsigned char *)(pp)[i + 3]))));
        value = pp + i + 4;
        ndo->ndo_printf(ndo, "\n");
        for (j = indent; j > 0; j--)
            ndo->ndo_printf(ndo, "\t");
        print = ndo->ndo_printf;
        print(ndo, "%s", dh6opt_str(type));
        ndo->ndo_printf(ndo, " (%u)", optlen + 4);
        if (type == 23 || type == 24 || type == 31) {
            if (optlen % 16 != 0) {
                ndo->ndo_printf(ndo, " %s", " (invalid)");
                return -1;
            }
            for (optlen = 0; optlen < length; optlen += 16)
                ndo->ndo_printf(ndo, " %s", print_bytes(ndo, value + optlen));
        }
    }
    return 0;
}
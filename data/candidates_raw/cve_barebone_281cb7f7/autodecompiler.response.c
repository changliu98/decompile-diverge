static int
decode_opt(netdissect_options *ndo,
           const unsigned char *cp, u_int len, u_int indent)
{
    unsigned i, j;
    int ret;

    for (i = 0; ; ) {
        if (i >= len)
            break;

        const unsigned char *tp = cp + i;
        unsigned short type = ((unsigned short)((tp[0] << 8) | tp[1]));
        unsigned short optlen = ((unsigned short)((tp[2] << 8) | tp[3]));
        const unsigned char *value = &tp[4];

        (*ndo->ndo_printf)(ndo, "\n");
        for (j = indent; j > 0; j--)
            (*ndo->ndo_printf)(ndo, "\t");

        (*ndo->ndo_printf)(ndo, "%s",
                           tok2str(dhcp6opt_str, "Unknown", type));
        (*ndo->ndo_printf)(ndo, " (%u)", optlen + 4);

        switch (type) {
        case 23:
            if (optlen % 16 != 0) {
                (*ndo->ndo_printf)(ndo, " %s", "(invalid)");
                ret = -1;
                goto out;
            }
            for (j = 0; j < optlen; j += 16)
                (*ndo->ndo_printf)(ndo, " %s", getname6(ndo, &value[j]));
            break;
        case 24:
            {
                const unsigned char *p = value;
                while (p < value + optlen) {
                    (*ndo->ndo_printf)(ndo, " ");
                    p = ns_nprint(ndo, p, value + optlen);
                    if (!p) {
                        ret = -1;
                        goto out;
                    }
                }
            }
            break;
        case 31:
            break;
        }

        i += optlen + 4;
    }

    ret = 0;
out:
    return (ret);
}
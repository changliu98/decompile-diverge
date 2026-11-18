static int
decode_opt(netdissect_options *ndo,
           const u_char *cp, u_int len, u_int indent)
{
    unsigned i, j;
    int ret;

    for (i = 0;;) {
        if (i >= len)
            break;

        const struct dhcp_opt *opt = (const struct dhcp_opt *)&cp[i];
        unsigned type = opt->type;
        unsigned optlen = opt->len;
        const char *value = (const char *)opt + 2;

        (*ndo->ndo_printf)(ndo, "\n");
        for (j = indent; j > 0; j--)
            (*ndo->ndo_printf)(ndo, "\t");

        (*ndo->ndo_printf)(ndo, "%s", tok2str(dhcp_opt_str, "Unknown", type));
        (*ndo->ndo_printf)(ndo, " (%u)", optlen + 2);

        switch (type) {
        case 6:
        case 42:
            if (optlen < 4 || optlen % 4 != 0) {
                ret = -1;
                goto out;
            }
            for (j = 0; j < optlen; j += 4)
                (*ndo->ndo_printf)(ndo, " %s",
                                   getname(ndo, &value[j]));
            break;
        case 119:
            {
                const char *p = value;
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
        }

        i += optlen + 2;
    }

    ret = 0;
out:
    return ret;
}
int dhcpv4_print(struct netdissect_options *ndo, const u_char *cp, u_int length, u_int indent) {
    u_int i = 0;
    const u_char *bp;
    u_char option, opt_len;
    const u_char *opt_data;
    u_int indent_step;
    const u_char *tp;

    while (i < length) {
        bp = cp + i;
        option = *bp;
        opt_len = *(bp + 1);
        opt_data = bp + 2;

        // ndo->ndo_printf("\n");
        ((int (*)(struct netdissect_options *, const char *, ...))ndo->ndo_printf)(ndo, "\n");

        indent_step = indent;
        while (indent_step > 0) {
            // ndo->ndo_printf("\t");
            ((int (*)(struct netdissect_options *, const char *, ...))ndo->ndo_printf)(ndo, "\t");
            indent_step--;
        }

        // ndo->ndo_printf(" %s (%u)", tok2str(dh4opt_str, "unknown", option), opt_len + 2);
        ((int (*)(struct netdissect_options *, const char *, ...))ndo->ndo_printf)(
            ndo, " %s (%u)", tok2str(dh4opt_str, "unknown", option), opt_len + 2);

        switch (option) {
            case 6:   // DNS Server
            case 42:  // NTP Servers
                if (opt_len < 4 || (opt_len % 4) != 0) {
                    return -1;
                }
                for (u_int j = 0; j < opt_len; j += 4) {
                    char *name = getname(ndo, opt_data + j);
                    // ndo->ndo_printf(" %s", name);
                    ((int (*)(struct netdissect_options *, const char *, ...))ndo->ndo_printf)(ndo, " %s", name);
                }
                break;

            case 119: // Domain Search
                tp = opt_data;
                while (tp < opt_data + opt_len) {
                    // ndo->ndo_printf(" ");
                    ((int (*)(struct netdissect_options *, const char *, ...))ndo->ndo_printf)(ndo, " ");
                    tp = ns_nprint(ndo, tp, opt_data + opt_len);
                    if (tp == NULL) {
                        return -1;
                    }
                }
                break;

            default:
                break;
        }

        i += opt_len + 2;
    }

    return 0;
}
void
rfc4675_print_discover(netdissect_options *ndo,
                      register const u_char *cp, register u_int len)
{

    if ((len > 0 || len == 0) && ndo->ndo_snapend - len <= ndo->ndo_snapend && cp <= ndo->ndo_snapend - len) {
        (*ndo->ndo_printf)(ndo, "Discover");
        while (len > 0) {
            (*ndo->ndo_printf)(ndo, " ");
            switch (*cp) {
            case 0x3a:
            case 0x3b:
            case 0x3c:
            case 0x3d:
            case 0x3e:
            case 0x3f:
                rfc4675_print(ndo, cp, len, *cp);
                return;
            default:
                (*ndo->ndo_printf)(ndo, "Unknown tag");
                cp++;
                len--;
                break;
            }
        }
    } else {
        trunc(ndo);
    }
}
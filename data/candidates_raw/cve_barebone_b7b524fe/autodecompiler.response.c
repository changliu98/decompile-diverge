__attribute__((used)) static int
ospf6_option_print(netdissect_options *ndo,
                   const u_char *cp, const u_char *ep)
{
    int optlen;

    switch (cp[1]) { /* RFC2472 */
    case OSPF6_OPT_HN:
        {
            const char *cp_name;
            cp += 2;
            ND_TCHECK(cp[0]);
            if (cp[0] > 127) {
                ND_TCHECK(cp[0] - 127);
                cp_name = getname(cp + 1, cp[0] - 127);
            } else {
                ND_TCHECK(cp[0]);
                cp_name = getname(cp, cp[0]);
            }
            (*ndo->ndo_printf)(ndo, "\n\tHostname %s", cp_name);
            break;
        }
    case OSPF6_OPT_RI: /* RFC2485 */
        {
            int i, n;
            const char *cp_name;
            cp += 2;
            ND_TCHECK(cp[0]);
            n = cp[0];
            (*ndo->ndo_printf)(ndo, "\n\tRouter-ID");
            for (i = 0; i < n; i++) {
                ND_TCHECK(cp[1 + i]);
                (*ndo->ndo_printf)(ndo, " %d", cp[1 + i]);
            }
            break;
        }
    case OSPF6_OPT_RLP: /* RFC2486 */
        {
            int i, n;
            const char *cp_name;
            cp += 2;
            ND_TCHECK(cp[0]);
            n = cp[0];
            (*ndo->ndo_printf)(ndo, "\n\tRLLP");
            for (i = 0; i < n; i++) {
                ND_TCHECK(cp[1 + i]);
                (*ndo->ndo_printf)(ndo, " %d", cp[1 + i]);
            }
            break;
        }
    case OSPF6_OPT_LI: /* RFC2590 */
        {
            int i, n;
            const char *cp_name;
            cp += 2;
            ND_TCHECK(cp[0]);
            n = cp[0];
            (*ndo->ndo_printf)(ndo, "\n\tLink-ID");
            for (i = 0; i < n; i++) {
                ND_TCHECK(cp[1 + i]);
                (*ndo->ndo_printf)(ndo, " %d", cp[1 + i]);
            }
            break;
        }
    case OSPF6_OPT_MSDP: /* RFC3678 */
        {
            int i, n;
            const char *cp_name;
            cp += 2;
            ND_TCHECK(cp[0]);
            n = cp[0];
            (*ndo->ndo_printf)(ndo, "\n\tMSDP");
            for (i = 0; i < n; i++) {
                ND_TCHECK(cp[1 + i]);
                (*ndo->ndo_printf)(ndo, " %d", cp[1 + i]);
            }
            break;
        }
    default:
        return(1);
    }

trunc:
    (*ndo->ndo_printf)(ndo, "[|OSPF6]");
    return(1);
}
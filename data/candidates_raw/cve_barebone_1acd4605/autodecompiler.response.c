__attribute__((used)) static int
chdlc_header_print(netdissect_options *ndo,
                   register const u_char *bp, register u_int length)
{
    register const struct chdlc_header *dp = (const struct chdlc_header *)bp;
    register u_short type;

    type = EXTRACT_16BITS(&dp->type);

    if (ndo->ndo_qflag) {
        (*ndo->ndo_qprint)(ndo, "%s, cisco %s, length %u: ",
                           tok2str(chdlc_dig_values, "0x%02x", dp->type),
                           tok2str(ethertype_values, "Unknown", type),
                           length);
    }

    length -= sizeof(struct chdlc_header);
    bp += sizeof(struct chdlc_header);

    switch (type) {
    case ETHERTYPE_IP:
        ip_print(ndo, bp, length);
        break;
    case ETHERTYPE_IPV6:
        ip6_print(ndo, bp, length);
        break;
    case ETHERTYPE_SLARP:
        chdlc_slarp_print(ndo, bp, length);
        break;
    case ETHERTYPE_MPLS:
    case ETHERTYPE_MPLS_OVERLAY:
    case ETHERTYPE_MPLS_OVERLAY_OLD:
        mpls_print(ndo, bp, length);
        break;
    case ETHERTYPE_ATALK:
    case ETHERTYPE_ATALKARP:
    case ETHERTYPE_ATALKIP:
        /*
         * This is a wild guess, but it seems that the DLT_CHDLC
         * type is used for AppleTalk over HDLC as well.
         */
        if (type == ETHERTYPE_ATALK)
            (*ndo->ndo_printf)(ndo, "atalk");
        else
            (*ndo->ndo_printf)(ndo, "atalk-arp");
        (*ndo->ndo_printf)(ndo, ", length %u: ", length);
        atalk_print(ndo, bp, length);
        break;
    case 0xfefe:
        /* RFC 1490 */
        if ((*(bp + 1) == 0x81) || (*(bp + 1) == 0x82) || (*(bp + 1) == 0x83))
            isoclns_print(ndo, bp + 1, length - 1, ndo->ndo_snapend - bp - 1);
        else
            isoclns_print(ndo, bp, length, ndo->ndo_snapend - bp);
        break;
    default:
        if (!ndo->ndo_qflag)
            (*ndo->ndo_printf)(ndo, "unknown CHDLC protocol (0x%04x)", type);
        break;
    }
    return (sizeof(struct chdlc_header));
}
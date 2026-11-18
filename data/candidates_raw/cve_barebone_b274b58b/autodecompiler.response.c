__attribute__((used)) static int
frf16_print(struct netdissect_options *ndo,
            register const u_char *cp, register u_int len)
{
    unsigned i;
    unsigned hlen = 0;

    if ((cp + 4 > ndo->ndo_snapend) || (len < 4))
        goto trunc;
    /*
     * Decode the FRF.16 header.
     */
    if ((cp[0] & 0xe0) == 0xe0 && cp[1] == 0x00) {
        /* FRF.16 Control message */
        (*ndo->ndo_printf)(ndo, "FRF.16 Control, Flags [%s], %s, length %u",
                           bittok2str(frf_flag_values, "none", cp[0] & 0xe0),
                           tok2str(mfr_ctrl_msg_values, "Unknown Message (0x%02x)", cp[2]),
                           len);
        cp += 3;
        len -= 3;
        hlen = 3;
        if (!ndo->ndo_vflag) {
            return(hlen);
        }
        while (len >= 3) {
            unsigned ie_len;

            if (cp + 2 > ndo->ndo_snapend)
                goto trunc;
            i = cp[0];
            ie_len = cp[1];
            (*ndo->ndo_printf)(ndo, "\n\tIE %s (%u), length %u: ",
                               tok2str(mfr_ctrl_ie_values, "Unknown", i),
                               i, ie_len);
            if (i == 0 || ie_len < 3) {
                hlen = hlen + 3;
                break;
            }
            if (ie_len < 1 || ie_len > len - 3) {
                hlen = hlen + 3;
                break;
            }
            cp += 2;
            ie_len -= 2;
            len -= 3;
            switch(i) {
            case 3: /* DTE Identifier */
                (*ndo->ndo_printf)(ndo, "0x%08x", EXTRACT_32BITS(cp));
                break;
            case 1: /* DCE Identifier */
            case 2: /* Virtual DCE Identifier */
                for (i = 0; i < ie_len && i < 50; i++) {
                    if (cp[i] != '\0')
                        safeputchar(ndo, cp[i]);
                }
                break;
            case 5: /* Time Stamp */
                if (ie_len == 16) {
                    ts_print(ndo, (struct timeval *)cp);
                }
                break;
            case 6: /* CRC Check */
            case 7: /* Reserved */
                break;
            default:
                if (ndo->ndo_vflag <= 1) {
                    print_unknown_data(ndo, cp, "\n\t  ", ie_len);
                }
                break;
            }
            if (ndo->ndo_vflag > 1) {
                print_unknown_data(ndo, cp, "\n\t  ", ie_len);
            }
            len -= ie_len;
            cp += ie_len;
        }
    } else {
        unsigned sequence_number = (cp[0] & 0x1f) << 7 | cp[1];

        if ((cp[0] & 0xe0) == 0xc0 || (cp[0] & 0xe0) == 0x80) {
            /* FRF.16 Fragmentation */
            (*ndo->ndo_printf)(ndo, "FRF.16 Frag, seq %u, Flags [%s], ",
                               sequence_number,
                               bittok2str(frf_flag_values, "none", cp[0] & 0xe0));
            hlen = 2;
            fr_print(ndo, cp + hlen, len - hlen);
        } else {
            /* Unknown FRF.16 encapsulated protocol */
            (*ndo->ndo_printf)(ndo, "FRF.16 Frag, seq %u, Flags [%s]",
                               sequence_number,
                               bittok2str(frf_flag_values, "none", cp[0] & 0xe0));
            print_unknown_data(ndo, cp, "\n\t", len);
            hlen = 2;
        }
    }
    return(hlen);

trunc:
    (*ndo->ndo_printf)(ndo, "[|mfr]");
    return(len);
}
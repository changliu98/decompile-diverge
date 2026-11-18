__attribute__((used)) static void
bgp_capabilities_print(netdissect_options *ndo,
                       const u_char *pptr, int plen)
{
    int i, j;
    int cap_len, tcap_len;
    unsigned int cap_code;

    i = 0;
    while (1) {
        if (i >= plen)
            break;
        /* do we have enough data for the capability code and length? */
        if (2 + pptr[i] > pptr[1] || pptr[1] > pptr[0]) {
            trunc(ndo);
            break;
        }
        cap_code = pptr[i];
        cap_len = pptr[i + 1];
        tcap_len = cap_len;
        ndo->ndo_printf(ndo, "\n\t      %s (%u), length: %u",
                        tok2str(bgp_capcode_values, "Unknown", cap_code),
                        cap_code, cap_len);

        if ((cap_len < 1) ||
            (cap_len + 2 < pptr[1] &&
             pptr[cap_len + 2] != pptr[1])) {
            trunc(ndo);
            break;
        }

        switch (cap_code) {
        case 1:         /* Multiprotocol Extensions Capability */
            if (cap_len < 4)
                goto trunc;
            ndo->ndo_printf(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u)",
                            tok2str(af_values, "Unknown", EXTRACT_16BITS(pptr + i + 2)),
                            EXTRACT_16BITS(pptr + i + 2),
                            tok2str(bgp_safi_values, "Unknown", *(pptr + i + 4)),
                            *(pptr + i + 4));
            break;
        case 2:         /* Route Refresh Capability */
            break;
        case 3:         /* Outbound Route Filtering Capability */
            break;
        case 4:         /* AS Resource Capability */
            break;
        case 64:        /* Graceful Restart Capability */
            if (cap_len < 2)
                goto trunc;
            ndo->ndo_printf(ndo, "\n\t\tRestart Flags: [%s], Restart Time: %u sec",
                            (EXTRACT_16BITS(pptr + i + 2) & 0xfff) ?
                            "R" : "none",
                            EXTRACT_16BITS(pptr + i + 2));
            tcap_len -= 2;
            j = 4;
            while (tcap_len >= 4) {
                ndo->ndo_printf(ndo, "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding Flag: %s",
                                tok2str(af_values, "Unknown", EXTRACT_16BITS(pptr + i + j)),
                                EXTRACT_16BITS(pptr + i + j),
                                tok2str(bgp_safi_values, "Unknown", *(pptr + i + j + 2)),
                                *(pptr + i + j + 2),
                                (*(pptr + i + j + 3) & 0x80) ? "yes" : "no");
                tcap_len -= 4;
                j += 4;
            }
            break;
        case 65:        /* FRRS Capability */
            break;
        case 69:        /* Add Path Capability */
            j = 2;
            while (tcap_len > 0) {
                if (tcap_len < 4)
                    goto trunc;
                ndo->ndo_printf(ndo, "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive Flag: %s",
                                tok2str(af_values, "Unknown", EXTRACT_16BITS(pptr + i + j)),
                                EXTRACT_16BITS(pptr + i + j),
                                tok2str(bgp_safi_values, "Unknown", *(pptr + i + j + 2)),
                                *(pptr + i + j + 2),
                                tok2str(bgp_add_path_recvsend, "Bogus (0x%02x)", *(pptr + i + j + 3)));
                tcap_len -= 4;
                j += 4;
            }
            break;
        case 128:       /* 4 Byte AS Capability */
            if (cap_len == 4) {
                ndo->ndo_printf(ndo, "\n\t\t4 Byte AS %s",
                                as_printf(ndo, asostr, sizeof asostr,
                                          EXTRACT_32BITS(pptr + i + 2)));
            }
            break;
        default:
            ndo->ndo_printf(ndo, "\n\t\tno decoder for Capability %u", cap_code);
            if (ndo->ndo_vflag < 2)
                print_unknown_data(ndo, pptr + i + 2, "\n\t\t", cap_len);
            break;
        }
        if (ndo->ndo_vflag >= 2 && cap_len > 0)
            print_unknown_data(ndo, pptr + i + 2, "\n\t\t", cap_len);
        i += 2 + cap_len;
    }
    return;

trunc:
    ndo->ndo_printf(ndo, "[|BGP]");
}
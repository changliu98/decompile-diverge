static void
bgp_capabilities_print(netdissect_options *ndo,
                      const u_char *pptr, int plen)
{
    int i = 0;

    while (1) {
        int cap_code;
        int cap_len;
        int tcap_len;
        int j;

        if (i >= plen)
            break;

        if (i + 2 > ndo->ndo_snapend || pptr + i + 2 > ndo->ndo_snapend)
            goto trunc;

        cap_code = pptr[i];
        cap_len = tcap_len = pptr[i + 1];

        (*ndo).ndo_printf((ndo), "\n\t      %s (%u), length: %u",
                          tok2str(&bgp_capcode_values, "Unknown", cap_code),
                          cap_code, cap_len);

        if ((cap_len < 1 && cap_len != 0) ||
            (cap_len > ndo->ndo_snapend - i - 2) ||
            (pptr + i + 2 + cap_len > ndo->ndo_snapend))
            goto trunc;

        switch (cap_code) {
        case 1:
            (*ndo).ndo_printf((ndo), "\n\t\tAFI %s (%u), SAFI %s (%u)",
                              tok2str(&af_values, "Unknown", ((unsigned)(pptr[i + 2]) << 8) | pptr[i + 3]),
                              ((unsigned)(pptr[i + 2]) << 8) | pptr[i + 3],
                              tok2str(&bgp_safi_values, "Unknown", pptr[i + 5]),
                              pptr[i + 5]);
            break;
        case 2:
            if (i + 2 > ndo->ndo_snapend || pptr + i + 2 > ndo->ndo_snapend)
                goto trunc;
            (*ndo).ndo_printf((ndo), "\n\t\tRestart Flags: [%s], Restart Time: %u sec",
                              (pptr[i + 2] & 0x80) ? "R" : "none",
                              ((unsigned)(pptr[i + 2] & 0x0f) << 8) | pptr[i + 3]);
            tcap_len -= 2;
            j = 4;
            while (tcap_len >= 5) {
                (*ndo).ndo_printf((ndo), "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding flag: %s",
                                  tok2str(&af_values, "Unknown", ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1]),
                                  ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1],
                                  tok2str(&bgp_safi_values, "Unknown", pptr[i + j + 2]),
                                  pptr[i + j + 2],
                                  (pptr[i + j + 3] & 0x80) ? "yes" : "no");
                tcap_len -= 4;
                j += 4;
            }
            break;
        case 64:
            if (i + 2 > ndo->ndo_snapend || pptr + i + 2 > ndo->ndo_snapend)
                goto trunc;
            (*ndo).ndo_printf((ndo), "\n\t\tRestart Flags: [%s], Restart Time: %u sec",
                              (pptr[i + 2] & 0x80) ? "R" : "none",
                              ((unsigned)(pptr[i + 2] & 0x0f) << 8) | pptr[i + 3]);
            tcap_len -= 2;
            j = 4;
            while (tcap_len >= 5) {
                (*ndo).ndo_printf((ndo), "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding flag: %s",
                                  tok2str(&af_values, "Unknown", ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1]),
                                  ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1],
                                  tok2str(&bgp_safi_values, "Unknown", pptr[i + j + 2]),
                                  pptr[i + j + 2],
                                  (pptr[i + j + 3] & 0x80) ? "yes" : "no");
                tcap_len -= 4;
                j += 4;
            }
            break;
        case 65:
            if (cap_len == 4) {
                (*ndo).ndo_printf((ndo), "\n\t\t 4 Byte AS %s",
                                  as_printf(ndo, &astostr, 20,
                                            ((unsigned)(pptr[i + 2]) << 24) |
                                            ((unsigned)(pptr[i + 3]) << 16) |
                                            ((unsigned)(pptr[i + 4]) << 8) |
                                            (unsigned)pptr[i + 5]));
            }
            break;
        case 69:
            j = 2;
            if (tcap_len == 0) {
                (*ndo).ndo_printf((ndo), " (bogus)");
                break;
            }
            while (tcap_len > 0) {
                if (tcap_len < 5)
                    goto trunc;
                (*ndo).ndo_printf((ndo), "\n\t\tAFI %s (%u), SAFI %s (%u), Send/Receive: %s",
                                  tok2str(&af_values, "Unknown", ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1]),
                                  ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1],
                                  tok2str(&bgp_safi_values, "Unknown", pptr[i + j + 2]),
                                  pptr[i + j + 2],
                                  tok2str(&bgp_add_path_recvsend, "Bogus (0x%02x)", pptr[i + j + 3]));
                tcap_len -= 4;
                j += 4;
            }
            break;
        case 128:
            if (i + 2 > ndo->ndo_snapend || pptr + i + 2 > ndo->ndo_snapend)
                goto trunc;
            (*ndo).ndo_printf((ndo), "\n\t\tRestart Flags: [%s], Restart Time: %u sec",
                              (pptr[i + 2] & 0x80) ? "R" : "none",
                              ((unsigned)(pptr[i + 2] & 0x0f) << 8) | pptr[i + 3]);
            tcap_len -= 2;
            j = 4;
            while (tcap_len >= 5) {
                (*ndo).ndo_printf((ndo), "\n\t\t  AFI %s (%u), SAFI %s (%u), Forwarding flag: %s",
                                  tok2str(&af_values, "Unknown", ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1]),
                                  ((unsigned)(pptr[i + j]) << 8) | pptr[i + j + 1],
                                  tok2str(&bgp_safi_values, "Unknown", pptr[i + j + 2]),
                                  pptr[i + j + 2],
                                  (pptr[i + j + 3] & 0x80) ? "yes" : "no");
                tcap_len -= 4;
                j += 4;
            }
            break;
        default:
            (*ndo).ndo_printf((ndo), "\n\t\tno decoder for Capability %u", cap_code);
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
    (*ndo).ndo_printf((ndo), "[|BGP]");
}
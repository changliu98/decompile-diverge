void bgp_capabilities_print(netdissect_options *ndo, const uint8_t *cp, int len) {
    int i;
    int cap_type, cap_len, alen;
    int off;
    uint16_t af;
    uint8_t safi;
    const char *safi_str;
    const char *af_str;
    int capcode;

    for (i = 0; i < len; ) {
        if ((size_t)ndo->some_len - 2 > (size_t)ndo->some_len || 
            (size_t)(cp + i) > (size_t)(ndo->some_len - 2)) {
            goto trunc;
        }

        cap_type = cp[i];
        cap_len = cp[i + 1];
        alen = cap_len;
        capcode = cap_type;

        s = tok2str(bgp_capcode_values, "Unknown", cap_type);
        ndo->ndo_printf(ndo, "\n\t\tCapability %s, length=%u", s, cap_type, cap_len);

        if (cap_len > 0) {
            if ((size_t)ndo->some_len - cap_len > (size_t)ndo->some_len ||
                (size_t)(cp + i + 2) > (size_t)(ndo->some_len - cap_len)) {
                goto trunc;
            }
        }

        switch (capcode) {
            case 1:
                af = (cp[i + 2] << 8) | cp[i + 3];
                af_str = tok2str(af_values, "Unknown AFI", af);
                safi = cp[i + 5];
                safi_str = tok2str(bgp_safi_values, "Unknown SAFI", safi);
                ndo->ndo_printf(ndo, " (%s/%s)", af_str, af, safi_str, safi);
                break;

            case 0x40:
                ndo->ndo_printf(ndo, " Stateful SWAP (%s, 0x%04x)",
                                (cp[i + 2] & 0x80) ? "Forwarding State Preserved" : "No Forwarding State",
                                ((cp[i + 2] << 8) | cp[i + 3]) & 0xfff);
                alen -= 2;
                off = 4;
                while (alen >= 4) {
                    af = (cp[i + off] << 8) | cp[i + off + 1];
                    af_str = tok2str(af_values, "Unknown AFI", af);
                    safi = cp[i + off + 2];
                    safi_str = tok2str(bgp_safi_values, "Unknown SAFI", safi);
                    ndo->ndo_printf(ndo, " %s(%s/%s)",
                                    (cp[i + off + 3] & 0x80) ? "Dependent" : "Independent",
                                    af_str, af, safi_str, safi);
                    alen -= 4;
                    off += 4;
                }
                break;

            case 0x41:
                if (cap_len == 4) {
                    uint32_t as = (cp[i + 2] << 24) | (cp[i + 3] << 16) | (cp[i + 4] << 8) | cp[i + 5];
                    char astostr[20];
                    as_printf(astostr, 20, as);
                    ndo->ndo_printf(ndo, " (4 octets) AS: %s", astostr);
                }
                break;

            case 0x45:
                off = 2;
                if (alen == 0) {
                    ndo->ndo_printf(ndo, " (IPv4, Unicast, Both)");
                    break;
                }
                while (alen > 0) {
                    if (alen < 4) {
                        ndo->ndo_printf(ndo, " (invalid length)");
                        break;
                    }
                    af = (cp[i + off] << 8) | cp[i + off + 1];
                    af_str = tok2str(af_values, "Unknown AFI", af);
                    safi = cp[i + off + 2];
                    safi_str = tok2str(bgp_safi_values, "Unknown SAFI", safi);
                    const char *add_path_str = tok2str(bgp_add_path_recvsend, "Unknown", cp[i + off + 3]);
                    ndo->ndo_printf(ndo, " (%s, %s, %s)", af_str, af, safi_str, safi, add_path_str);
                    alen -= 4;
                    off += 4;
                }
                break;

            case 2:
            case 0x80:
                break;

            default:
                ndo->ndo_printf(ndo, " (unknown cap %d)", cap_type);
                if (ndo->ndo_vflag > 1) {
                    print_unknown_data(ndo, cp + i + 2, "\n\t\t", cap_len);
                }
                break;
        }

        if (ndo->ndo_vflag > 1 && cap_len > 0) {
            print_unknown_data(ndo, cp + i + 2, "\n\t\t", cap_len);
        }

        i += cap_len + 2;
    }
    return;

trunc:
    ndo->ndo_printf(ndo, "[|BGP]");
}
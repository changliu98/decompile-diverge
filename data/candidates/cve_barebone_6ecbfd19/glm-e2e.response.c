int ieee802_11_print(struct netdissect_options *ndo, const uint8_t *p, int length, int hdr_len, int pad, int caplen) {
    int var_4;
    uint16_t fc;
    int extracted_hdr_len;
    int mesh_hdr_len = 0;
    int llc_ret;
    uint8_t src_mac[8];
    uint8_t dst_mac[8];

    if ((uint32_t)length < (uint32_t)caplen) {
        ndo->ndo_error(ndo, "[|802.11]", tstr);
        var_4 = hdr_len;
        return var_4;
    }

    length -= caplen;
    if (hdr_len > length) {
        caplen = hdr_len - length;
        hdr_len -= caplen;
        ndo->ndo_packet += caplen;
    }

    if (hdr_len < 2) {
        ndo->ndo_error(ndo, "[|802.11]", tstr);
        var_4 = hdr_len;
        return var_4;
    }

    fc = (p[1] << 8) | p[0];
    extracted_hdr_len = extract_header_length(ndo, fc);
    if (extracted_hdr_len == 0) {
        var_4 = 0;
        return var_4;
    }

    if (pad != 0) {
        extracted_hdr_len = (extracted_hdr_len + 3) & ~3;
    }

    if (ndo->ndo_ll_header != 0 && ((fc >> 2) & 3) == 2 && ((fc >> 4) & 8) != 0) {
        mesh_hdr_len = extract_mesh_header_length(p + extracted_hdr_len);
        extracted_hdr_len += mesh_hdr_len;
    }

    if (hdr_len < extracted_hdr_len) {
        ndo->ndo_error(ndo, "[|802.11]", tstr);
        var_4 = extracted_hdr_len;
        return var_4;
    }

    if (ndo->ndo_prints != 0) {
        ieee_802_11_hdr_print(ndo, fc, p, extracted_hdr_len, mesh_hdr_len);
    }

    length -= extracted_hdr_len;
    hdr_len -= extracted_hdr_len;
    p += extracted_hdr_len;

    src_mac[0] = 0; // Dummy initialization to map stack layout
    dst_mac[0] = 0; // Dummy initialization to map stack layout

    switch ((fc >> 2) & 3) {
        case 0:
            get_mgmt_src_dst_mac(p - extracted_hdr_len, src_mac, dst_mac);
            if (mgmt_body_print(ndo, fc, src_mac, p, length) == 0) {
                ndo->ndo_error(ndo, "[|802.11]", tstr);
                var_4 = extracted_hdr_len;
                return var_4;
            }
            break;
        case 1:
            if (ctrl_body_print(ndo, fc, p - extracted_hdr_len) == 0) {
                ndo->ndo_error(ndo, "[|802.11]", tstr);
                var_4 = extracted_hdr_len;
                return var_4;
            }
            break;
        case 2:
            if ((fc >> 4) & 4) {
                var_4 = extracted_hdr_len;
                return var_4;
            }
            if (fc & 0x4000) {
                ndo->ndo_error(ndo, "WEP encrypted");
                if (wep_print(ndo, p) == 0) {
                    ndo->ndo_error(ndo, "[|802.11]", tstr);
                    var_4 = extracted_hdr_len;
                    return var_4;
                }
            } else {
                get_data_src_dst_mac(fc, p - extracted_hdr_len, src_mac, dst_mac);
                llc_ret = llc_print(ndo, p, length, hdr_len, src_mac, dst_mac);
                if (llc_ret < 0) {
                    if (ndo->ndo_eflag == 0) {
                        ndo->ndo_default_print(ndo, p, hdr_len);
                    }
                    llc_ret = -llc_ret;
                }
                extracted_hdr_len += llc_ret;
            }
            break;
        case 3:
            break;
    }

    var_4 = extracted_hdr_len;
    return var_4;
}
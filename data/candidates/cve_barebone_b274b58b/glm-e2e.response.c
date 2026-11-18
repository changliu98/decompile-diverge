int mfr_print(struct netdissectors *ndo, const uint8_t *p, int length) {
    uint8_t ie_type, ie_len;
    const uint8_t *ptemp;
    uint16_t mfr_len;
    int ret = 0;
    int bytes_consumed = 0;

    // Bounds check
    if (ndo->ndo_snapend - 4 > ndo->ndo_snapend || p > ndo->ndo_snapend - 4) {
        goto trunc;
    }

    // Check for FRF.9 / Control messages
    if ((p[0] & 0xe0) == 0xe0 && p[1] == 0) {
        const char *frf_flags_str = bittok2str(frf_flag_values, "none", p[0] & 0xe0);
        const char *ctrl_msg_str = tok2str(mfr_ctrl_msg_values, "unknown Message (0x%02x)", p[2]);
        
        ndo->ndo_printf_method(ndo, "FRF.16 Control, Flags [%s], %s, length %d\n", 
                               frf_flags_str, ctrl_msg_str, length);
        
        ptemp = p + 3;
        bytes_consumed = 3;
        length -= 3;

        if (ndo->ndo_vflag == 0) {
            return bytes_consumed;
        }

        // Iterate over Information Elements (IEs)
        while (length > 2) {
            if (ndo->ndo_snapend - 2 > ndo->ndo_snapend || ptemp > ndo->ndo_snapend - 2) {
                goto trunc;
            }

            ie_type = ptemp[0];
            ie_len = ptemp[1];

            const char *ie_type_str = tok2str(mfr_ctrl_ie_values, "unknown IE (0x%02x)", ie_type);
            ndo->ndo_printf_method(ndo, "\t\t%s (0x%02x), length %d\n", ie_type_str, ie_type, ie_len);

            if (ie_type == 0 || ie_len <= 2) {
                return bytes_consumed;
            }

            if (ie_len > 0) {
                if (ndo->ndo_snapend - ie_len > ndo->ndo_snapend || ptemp > ndo->ndo_snapend - ie_len) {
                    goto trunc;
                }
            }

            ptemp += 2;
            ie_len -= 2;
            length -= 2;

            // Switch on IE type
            switch (ie_type - 1) {
                case 0: // IE Type 1
                    ndo->ndo_printf_method(ndo, "\t\t  Magic: 0x%08x\n", EXTRACT_32BITS(ptemp));
                    break;
                    
                case 1: // IE Type 2 (String)
                    for (int i = 0; i < ie_len && i < 50; i++) {
                        if (ptemp[i] == 0) break;
                        safeputchar(ndo, ptemp[i]);
                    }
                    break;
                    
                case 2: // IE Type 3
                    if (ie_len == 16) {
                        ts_print(ndo, ptemp);
                    }
                    // Fall-through to default if not 16
                    
                default:
                    if (ndo->ndo_vflag > 1) {
                        print_unknown_data(ndo, ptemp, "\n\t\t", ie_len);
                    }
                    break;
            }

            if (ndo->ndo_vflag > 1) {
                print_unknown_data(ndo, ptemp, "\n\t\t", ie_len);
            }

            length -= ie_len;
            ptemp += ie_len;
        }
        return bytes_consumed;
    } else {
        // Standard Frame Relay
        mfr_len = ((p[0] & 0x1e) << 7) | p[1];

        if ((p[0] & 0xe0) == 0xc0 || (p[0] & 0xe0) == 0x80) {
            const char *frf_flags_str = bittok2str(frf_flag_values, "none", p[0] & 0xe0);
            ndo->ndo_printf_method(ndo, "FRF.16 Fragment, Flags [%s], length %d\n", frf_flags_str, mfr_len);
            bytes_consumed = 2;
            fr_print(ndo, p + bytes_consumed, length - bytes_consumed);
            return bytes_consumed;
        } else {
            const char *frf_flags_str = bittok2str(frf_flag_values, "none", p[0] & 0xe0);
            ndo->ndo_printf_method(ndo, "FRF.16 Unknown, Flags [%s], length %d\n", frf_flags_str, mfr_len);
            print_unknown_data(ndo, p, "\n\t", length);
            return bytes_consumed;
        }
    }

trunc:
    ndo->ndo_printf_method(ndo, "[|mfr]");
    return length;
}
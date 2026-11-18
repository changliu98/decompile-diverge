void eap_print(struct netdissect_options *ndo, const uint8_t *cp, uint32_t length) {
    int i = 0;
    const uint8_t *ep;
    const uint8_t *tptr;
    uint8_t eap_code;
    uint16_t eap_len;
    uint8_t eap_type;

    ep = cp + length;
    tptr = cp;

    // Bounds check
    if (ndo->length - 4 > ndo->length || cp > ndo->length - 4) {
        goto trunc;
    }

    if (ndo->some_field < 1) {
        // Legacy/Short EAP frame format
        ndo->printer_func(ndo, "%s (%u), id %u, len %u\n",
            tok2str(eap_frame_type_values, "unknown", tp[1]),
            tp[1],
            tp[0],
            (tp[2] << 8) | tp[3]);
        return;
    }

    // Standard EAP frame format
    ndo->printer_func(ndo, "%s (%u), id %u, len %u\n",
        tok2str(eap_frame_type_values, "unknown", tp[1]),
        tp[1],
        tp[0],
        __builtin_bswap16(*(uint16_t *)(tp + 2)));

    tptr += 4;
    length -= 4;
    eap_code = tp[1];

    if (eap_code != 0 && eap_code != 2 && eap_code != 4) {
        goto done;
    }

    eap_code = tptr[0];
    eap_len = (tptr[2] << 8) | tptr[3];

    ndo->printer_func(ndo, "\t%s (%u), id %u, len %u\n",
        tok2str(eap_code_values, "unknown", eap_code),
        eap_code,
        tptr[1],
        eap_len);

    if (eap_len > 0) {
        if (ndo->length - eap_len > ndo->length || tptr > ndo->length - eap_len) {
            goto trunc;
        }
    }

    if (eap_code > 2) {
        goto done;
    }

    eap_type = tptr[4];
    ndo->printer_func(ndo, "\t\t%s (%u)",
        tok2str(eap_type_values, "unknown", eap_type),
        eap_type);

    switch (eap_type) {
        case 1:
        case 2:
            if (eap_len > 5) {
                ndo->printer_func(ndo, ", Value: ");
                safeputs(ndo, tptr + 5, eap_len - 5);
            }
            break;

        case 3:
            for (i = 5; i < eap_len; i++) {
                ndo->printer_func(ndo, "\n\t\t%s (%u)",
                    tok2str(eap_type_values, "unknown", tptr[i]),
                    tptr[i]);
            }
            break;

        case 4:
        case 5:
        case 6:
        case 7:
            break;

        case 13:
            ndo->printer_func(ndo, ", Flags %s",
                bittok2str(eap_tls_flags_values, "none", tptr[5]));
            if (tptr[5] & 0x80) {
                ndo->printer_func(ndo, ", len %u",
                    (tptr[6] << 24) | (tptr[7] << 16) | (tptr[8] << 8) | tptr[9]);
            }
            break;

        case 21:
            ndo->printer_func(ndo, ", Version %u", tptr[5] & 0x7);
            break;

        case 43:
            ndo->printer_func(ndo, ", Version %u", tptr[5] & 0x7);
            ndo->printer_func(ndo, ", Flags %s",
                bittok2str(eap_tls_flags_values, "none", tptr[5]));
            if (tptr[5] & 0x80) {
                ndo->printer_func(ndo, ", len %u",
                    (tptr[6] << 24) | (tptr[7] << 16) | (tptr[8] << 8) | tptr[9]);
            }
            break;

        case 18:
        case 23:
            ndo->printer_func(ndo, ",_subtype %s",
                tok2str(eap_aka_subtype_values, "unknown", tptr[5]));
            break;

        case 50:
        case 51:
            break;

        default:
            break;
    }

done:
    return;

trunc:
    ndo->printer_func(ndo, "[|EAP]");
    return;
}
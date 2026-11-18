int rpki_rtr_pdu_print(struct netdissect_options *ndo, const uint8_t *pptr, int indent) {
    const uint8_t *pdu = pptr;
    uint8_t pdu_type = pdu[1];
    uint32_t pdu_len = (pdu[4] << 24) | (pdu[5] << 16) | (pdu[6] << 8) | pdu[7];
    int ret = 0;

    // Length and bounds validation
    if (pdu_len == 0 || ndo->ndo_remaining - pdu_len > ndo->ndo_remaining || pptr > ndo->ndo_remaining - pdu_len) {
        return 1;
    }

    const char *type_str = tok2str(&rpki_rtr_pdu_values, "type %u", pdu_type);
    const char *indent_str = indent_string(indent + 8);
    ndo->ndo_printf(ndo, "%sRPKI-RTR v%u, %s, length %u\n", indent_str, pdu[0], type_str, pdu_len);

    switch (pdu_type) {
        case 1: { // IPv4 Prefix PDU
            const uint8_t *prefix_ptr = pdu + 8;
            const char *ind = indent_string(indent + 2);
            uint16_t flags = (pdu[2] << 8) | pdu[3];
            uint32_t prefix = (prefix_ptr[0] << 24) | (prefix_ptr[1] << 16) | (prefix_ptr[2] << 8) | prefix_ptr[3];
            ndo->ndo_printf(ndo, "%sIPv4 Prefix %s, origin AS %u, flags 0x%04x\n",
                            ind, getname(ndo, pdu + 12), prefix, flags);
            break;
        }
        case 2: { // IPv6 Prefix PDU
            const char *ind = indent_string(indent + 2);
            uint16_t flags = (pdu[2] << 8) | pdu[3];
            ndo->ndo_printf(ndo, "%sIPv6 Prefix %s, origin AS %u, flags 0x%04x\n",
                            ind, getname6(ndo, pdu + 12), 0, flags);
            break;
        }
        case 3: { // Error Report PDU
            const uint8_t *err_pdu = pdu;
            uint32_t encapsulated_pdu_len = (err_pdu[8] << 24) | (err_pdu[9] << 16) | (err_pdu[10] << 8) | err_pdu[11];
            
            if (encapsulated_pdu_len == 0 || ndo->ndo_remaining - encapsulated_pdu_len > ndo->ndo_remaining || pptr > ndo->ndo_remaining - encapsulated_pdu_len) {
                return 1;
            }

            uint32_t rest_len = pdu_len;
            uint16_t err_code = (err_pdu[2] << 8) | err_pdu[3];
            const char *ind = indent_string(indent + 2);
            const char *err_str = tok2str(&rpki_rtr_error_codes, "error %u", err_code);
            ndo->ndo_printf(ndo, "%sError PDU, code %u (%s), length %u\n", ind, err_code, err_str, encapsulated_pdu_len);

            pptr += 12;
            rest_len -= 12;

            if (encapsulated_pdu_len != 0 && encapsulated_pdu_len <= rest_len) {
                const char *ind2 = indent_string(indent + 4);
                ndo->ndo_printf(ndo, "%sEncapsulated PDU:\n", ind2);
                if (rpki_rtr_pdu_print(ndo, pptr, indent + 2) != 0) {
                    return 1;
                }
            }

            pptr += encapsulated_pdu_len;
            rest_len -= encapsulated_pdu_len;

            uint32_t text_len = 0;
            if (rest_len > 4) {
                text_len = (pptr[0] << 24) | (pptr[1] << 16) | (pptr[2] << 8) | pptr[3];
                pptr += 4;
                rest_len -= 4;
            }

            if (text_len == 0 || ndo->ndo_remaining - text_len > ndo->ndo_remaining || pptr > ndo->ndo_remaining - text_len) {
                return 1;
            }

            if (text_len != 0 && text_len <= rest_len) {
                const char *ind3 = indent_string(indent + 2);
                ndo->ndo_printf(ndo, "%sError text: ", ind3);
                if (fn_printn(ndo, pptr, text_len, ndo->ndo_remaining + (size_t)pptr) != 0) {
                    return 1;
                }
            }
            break;
        }
        default:
            ret = 1;
            break;
    }

    if ((ndo->ndo_verbose > 1 || ndo->ndo_verbose == 0) && ret != 0) {
        print_unknown_data(ndo, pptr, "\n\t  ", pdu_len);
    }

    return 0;
}
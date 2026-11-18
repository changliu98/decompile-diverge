void vqp_print(struct netdissect_options *ndo, const uint8_t *bp, uint32_t length) {
    struct vqp_header *hdr = (struct vqp_header *)ndo;
    const uint8_t *cp = bp;
    const uint8_t *snapend = hdr->ndo_snapend;
    int ndo_vflag = hdr->ndo_ndo_print;
    ndo_printer printer = hdr->ndo_print;
    
    uint32_t len = length;
    uint8_t count;
    uint8_t msg_type;
    const char *msg_type_str;
    const char *error_code_str;
    uint8_t error_code;
    uint32_t obj_type;
    uint16_t obj_len;
    const char *obj_type_str;
    const char *ip_str;
    const char *eth_str;
    uint8_t has_more;

    /* Bounds check against snapend */
    if (cp + 8 > snapend || cp > snapend - 8) {
        goto trunc;
    }

    if (cp[0] != 1) {
        printer(ndo, "VQP version %u", cp[0]);
        return;
    }

    if (ndo_vflag < 1) {
        msg_type = cp[0];
        msg_type_str = tok2str(vqp_msg_type_values, "unknown", cp[1]);
        error_code_str = tok2str(vqp_error_code_values, "unknown", cp[2]);
        printer(ndo, "VQPv0-%s %s: %s (error code %u), length %u",
                msg_type_str, error_code_str, error_code_str, cp[2], length);
    } else {
        count = cp[3];
        msg_type = cp[0];
        msg_type_str = tok2str(vqp_msg_type_values, "unknown", cp[1]);
        error_code_str = tok2str(vqp_error_code_values, "unknown", cp[2]);
        error_code = cp[2];
        obj_type = EXTRACT_32BITS(cp + 4);
        printer(ndo, "VQPv1-%s %s: error code %u, length %u, obj-type %u, obj-length %u, obj-count %u",
                msg_type_str, error_code_str, error_code, length, obj_type, 0, count);
    }

    cp += 8;
    len -= 8;

    while (count > 0 && (int)len > 0) {
        if (cp + 6 > snapend || cp > snapend - 6) {
            goto trunc;
        }

        obj_type = EXTRACT_32BITS(cp);
        obj_len = EXTRACT_16BITS(cp + 4);
        cp += 6;
        len -= 6;

        obj_type_str = tok2str(vqp_obj_values, "unknown", obj_type);
        printer(ndo, "\n\tObject-type: %s (0x%x), Object-length: %u",
                obj_type_str, obj_type, obj_len);

        if (obj_type == 0 || obj_len == 0) {
            return;
        }

        if ((int)obj_len <= 0 || (snapend - obj_len) > snapend || cp > (snapend - obj_len)) {
            goto trunc;
        }

        switch (obj_type) {
            case 0x0c01: /* IP Address (0x0c00 + 1) */
                ip_str = ipaddr_string(ndo, cp);
                printer(ndo, ", IP-Address: %s (0x%08x)", ip_str, EXTRACT_32BITS(cp));
                break;
            case 0x0c02: /* String (0x0c00 + 2) */
                safeputs(ndo, cp, obj_len);
                break;
            case 0x0c03: /* Ethernet Address (0x0c00 + 3) */
                eth_str = etheraddr_string(ndo, cp);
                printer(ndo, ", MAC-Address: %s", eth_str);
                break;
            default:
                if (ndo_vflag <= 1) {
                    print_unknown_data(ndo, cp, "\n\t  ", obj_len);
                }
                break;
        }

        cp += obj_len;
        len -= obj_len;
        count--;
    }
    return;

trunc:
    printer(ndo, "[|vqp]");
}
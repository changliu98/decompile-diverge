int isis_print_extd_ip_reach(struct isis_tlv_pt *tlv_pt, const uint8_t *cp, uint32_t op, uint16_t family) {
    uint32_t prefix_len;
    uint8_t prefix[16];
    uint8_t control_byte;
    uint8_t subtlvs_len;
    uint8_t subtlv_type;
    uint8_t subtlv_len;
    char tag_buf[20];
    uint32_t processed = 4;

    if (tlv_pt->len < 4 || cp > tlv_pt->ptr + tlv_pt->len - 4) {
        return 0;
    }

    uint32_t metric = (cp[0] << 24) | (cp[1] << 16) | (cp[2] << 8) | cp[3];
    cp += 4;

    if (family == 2) {
        if (tlv_pt->len < 1 || cp > tlv_pt->ptr + tlv_pt->len - 1) {
            return 0;
        }
        control_byte = *cp++;
        prefix_len = control_byte & 0x3f;
        if (prefix_len > 32) {
            (*tlv_pt->printer)(tlv_pt, "prefix_len %d > 32", prefix_len);
            return 0;
        }
        processed++;
    } else if (family == 10) {
        if (tlv_pt->len < 2 || cp > tlv_pt->ptr + tlv_pt->len - 2) {
            return 0;
        }
        control_byte = *cp++;
        prefix_len = *cp++;
        if (prefix_len > 128) {
            (*tlv_pt->printer)(tlv_pt, "prefix_len %d > 128", prefix_len);
            return 0;
        }
        processed += 2;
    } else {
        return 0;
    }

    uint32_t actual_len = (prefix_len + 7) / 8;
    if (actual_len != 0) {
        if (tlv_pt->len < actual_len || cp > tlv_pt->ptr + tlv_pt->len - actual_len) {
            return 0;
        }
    }

    memset(prefix, 0, 16);
    memcpy(prefix, cp, actual_len);
    cp += actual_len;
    processed += actual_len;

    if (family == 2) {
        (*tlv_pt->printer)(tlv_pt, "%s/%d", ipaddr_string(tlv_pt, prefix), prefix_len);
    } else if (family == 10) {
        (*tlv_pt->printer)(tlv_pt, "%s/%d", ip6addr_string(tlv_pt, prefix), prefix_len);
    }

    (*tlv_pt->printer)(tlv_pt, " metric %d, %s", metric, (control_byte & 0x80) ? "external" : "internal");

    if (family == 2) {
        if (control_byte & 0x40) {
            (*tlv_pt->printer)(tlv_pt, " down");
        }
    } else if (family == 10) {
        (*tlv_pt->printer)(tlv_pt, ", %s%s", (control_byte & 0x40) ? "down" : "up", (control_byte & 0x20) ? " subtlvs present" : "");
    }

    if ((family == 2 && (control_byte & 0x40)) || (family == 10 && (control_byte & 0x20))) {
        if (tlv_pt->len < 1 || cp > tlv_pt->ptr + tlv_pt->len - 1) {
            return 0;
        }
        subtlvs_len = *cp++;
        processed += subtlvs_len + 1;
        (*tlv_pt->printer)(tlv_pt, " sub-TLVs present (%d)", subtlvs_len);

        while (subtlvs_len > 0) {
            if (tlv_pt->len < 2 || cp > tlv_pt->ptr + tlv_pt->len - 2) {
                return 0;
            }
            subtlv_type = *cp++;
            subtlv_len = *cp++;
            snprintf(tag_buf, 20, " subTLV %d len %d", subtlv_type, subtlv_len);
            if (isis_print_ip_reach_subtlv(tlv_pt, cp, subtlv_type, subtlv_len, tag_buf) == 0) {
                return 0;
            }
            cp += subtlv_len;
            subtlvs_len -= subtlv_len + 2;
        }
    }

    return processed;
}
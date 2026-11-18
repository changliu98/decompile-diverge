PJ_STATUS_T get_name_len(int rec_counter, const uint8_t *pkt, const uint8_t *start, const uint8_t *max, int *p_name_len, int *p_total_len) {
    const uint8_t *p;
    uint16_t val16;
    int status;
    int sub_status;
    int sub_name_len;

    if (rec_counter > 10) {
        return PJLIB_UTIL_ESTDPTRINVALID;
    }

    *p_name_len = 0;
    *p_total_len = 0;
    p = start;

    while (*p != 0) {
        if ((*p & 0xc0) == 0xc0) {
            // Pointer handling
            pj_memcpy(&val16, p, 2);
            val16 ^= pj_htons(0xc000);
            val16 = pj_ntohs(val16);

            if (val16 >= (uint16_t)(max - pkt)) {
                return PJLIB_UTIL_ESTDPTRINVALID;
            }

            sub_status = get_name_len(rec_counter + 1, pkt, pkt + val16, max, &sub_name_len, p_total_len);
            if (sub_status != 0) {
                return sub_status;
            }

            *p_name_len += 2;
            *p_total_len += sub_name_len;
            return PJ_SUCCESS;
        } else {
            // Label handling
            uint8_t label_len = *p;

            if (p + label_len > max) {
                return PJLIB_UTIL_ESTDPTRINVALID;
            }

            p += label_len + 1;
            *p_name_len += label_len + 1;

            if (*p == 0) {
                label_len = 0;
            }

            *p_total_len += label_len + 1;

            if (p >= max) {
                return PJLIB_UTIL_ESTDNAMESIZE;
            }
        }
    }

    // Null terminator handling
    p++;
    *p_name_len += 1;

    return PJ_SUCCESS;
}
define PJ_STATUS_CODE_INVALID 0x4E22B

int get_name_len(int level, const uint8_t *start, const uint8_t *end, int *p_len, int *p_count) {
    int status = PJ_STATUS_CODE_INVALID;
    int rec_level = 0;
    int rec_len = 0;
    const uint8_t *p = start;

    // Check recursion depth and bounds
    if (level > 10) {
        return PJ_STATUS_CODE_INVALID;
    }
    if (p >= end) {
        return PJ_STATUS_CODE_INVALID;
    }

    *p_len = 0;
    *p_count = 0;

    while (*p != '\0') {
        if ((*p & PJ_DNS_COMPRESSED_POINTER_MASK) == PJ_DNS_COMPRESSED_POINTER) {
            uint16_t offset;

            // Extract the 16-bit pointer and clear the top 2 bits
            pj_memcpy(&offset, p, 2);
            offset ^= pj_htons(0xC000);
            offset = pj_ntohs(offset);

            // Check if the offset is within bounds
            if (offset >= (end - start)) {
                return PJ_STATUS_CODE_INVALID;
            }

            // Recursively resolve the compressed pointer
            status = get_name_len(level + 1, start, start + offset, &rec_len, &rec_count);
            if (status != 0) {
                return status;
            }

            // Add the 2 bytes used by the pointer itself
            *p_len += 2;
            *p_count += rec_count;
            
            return 0;
        } else {
            int label_len = *p;

            // Check if the label exceeds the bounds
            if (p + label_len + 1 > end) {
                return PJ_STATUS_CODE_INVALID;
            }

            // Advance pointer past the label
            p += label_len + 1;

            // Add the length of the label and the length byte
            *p_len += label_len + 1;

            // If the next byte is not zero, it's another label, so add 1 for the dot
            if (*p != '\0') {
                label_len += 1;
            }
            *p_count += label_len;
        }
    }

    // Handle the null terminator
    p++;
    *p_len += 1;
    
    return 0;
}
const char *sgml__utf8_get_char(const char *str, int *out_char) {
    const char *next;
    int c = (int8_t)str[0];

    if ((c & 0xE0) == 0xC0) {
        if (((int8_t)str[1] & 0xC0) == 0x80) {
            *out_char = ((c & 0x1F) << 6) | ((int8_t)str[1] & 0x3F);
            next = str + 2;
            return next;
        }
    } else if ((c & 0xF0) == 0xE0) {
        if (((int8_t)str[1] & 0xC0) == 0x80 && ((int8_t)str[2] & 0xC0) == 0x80) {
            *out_char = ((c & 0x0F) << 12) | (((int8_t)str[1] & 0x3F) << 6) | ((int8_t)str[2] & 0x3F);
            next = str + 3;
            return next;
        }
    } else if ((c & 0xF8) == 0xF0) {
        if (((int8_t)str[1] & 0xC0) == 0x80 && ((int8_t)str[2] & 0xC0) == 0x80 && ((int8_t)str[3] & 0xC0) == 0x80) {
            *out_char = ((c & 0x07) << 18) | (((int8_t)str[1] & 0x3F) << 12) | (((int8_t)str[2] & 0x3F) << 6) | ((int8_t)str[3] & 0x3F);
            next = str + 4;
            return next;
        }
    } else if ((c & 0xFC) == 0xF8) {
        if (((int8_t)str[1] & 0xC0) == 0x80 && ((int8_t)str[2] & 0xC0) == 0x80 && ((int8_t)str[3] & 0xC0) == 0x80 && ((int8_t)str[4] & 0xC0) == 0x80) {
            *out_char = ((c & 0x03) << 24) | (((int8_t)str[1] & 0x3F) << 18) | (((int8_t)str[2] & 0x3F) << 12) | (((int8_t)str[3] & 0x3F) << 6) | ((int8_t)str[4] & 0x3F);
            next = str + 5;
            return next;
        }
    } else if ((c & 0xFE) == 0xFC) {
        if (((int8_t)str[1] & 0xC0) == 0x80 && ((int8_t)str[2] & 0xC0) == 0x80 && ((int8_t)str[3] & 0xC0) == 0x80 && ((int8_t)str[4] & 0xC0) == 0x80 && ((int8_t)str[5] & 0xC0) == 0x80) {
            *out_char = ((c & 0x01) << 30) | (((int8_t)str[1] & 0x3F) << 24) | (((int8_t)str[2] & 0x3F) << 18) | (((int8_t)str[3] & 0x3F) << 12) | (((int8_t)str[4] & 0x3F) << 6) | ((int8_t)str[5] & 0x3F);
            next = str + 4; // Note: The assembly adds 4 here, which is likely a bug in the original code (should be 6)
            return next;
        }
    }
    
    // Fallback for 1-byte characters or invalid UTF-8 sequences
    *out_char = c;
    next = str + 1;
    return next;
}
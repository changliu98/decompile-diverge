int get_char_utf8(int *out_codepoint, const unsigned char *str) {
    unsigned char c0 = str[0];
    
    // 1-byte sequence (0xxxxxxx)
    if ((c0 & 0x80) == 0) {
        *out_codepoint = c0;
        return c0 != 0 ? 1 : 0;
    }
    
    // Invalid leading byte (10xxxxxx)
    if ((c0 & 0x40) == 0) {
        *out_codepoint = -1;
        return -1;
    }
    
    unsigned char c1 = str[1];
    if ((c1 & 0xC0) != 0x80) {
        *out_codepoint = -1;
        return -1;
    }
    
    // 2-byte sequence (110xxxxx 10xxxxxx)
    if ((c0 & 0x20) == 0) {
        if ((c0 & 0x1E) > 0) { // Overlong check
            *out_codepoint = ((c0 & 0x1F) << 6) | (c1 & 0x3F);
            return 2;
        }
        *out_codepoint = -1;
        return -1;
    }
    
    unsigned char c2 = str[2];
    if ((c2 & 0xC0) != 0x80) {
        *out_codepoint = -1;
        return -1;
    }
    
    // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
    if ((c0 & 0x10) == 0) {
        if (((c0 & 0x0F) | (c1 & 0x20)) > 0) { // Overlong check
            *out_codepoint = ((c0 & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
            return 3;
        }
        *out_codepoint = -1;
        return -1;
    }
    
    unsigned char c3 = str[3];
    if ((c3 & 0xC0) != 0x80) {
        *out_codepoint = -1;
        return -1;
    }
    
    // 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
    if ((c0 & 0x08) == 0) {
        if (((c0 & 0x07) | (c1 & 0x30)) > 0) { // Overlong check
            *out_codepoint = ((c0 & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
            return 4;
        }
        *out_codepoint = -1;
        return -1;
    }
    
    unsigned char c4 = str[4];
    if ((c4 & 0xC0) != 0x80) {
        *out_codepoint = -1;
        return -1;
    }
    
    // 5-byte sequence (111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx)
    if ((c0 & 0x04) == 0) {
        if (((c0 & 0x03) | (c1 & 0x38)) > 0) { // Overlong check
            *out_codepoint = ((c0 & 0x03) << 24) | ((c1 & 0x3F) << 18) | ((c2 & 0x3F) << 12) | ((c3 & 0x3F) << 6) | (c4 & 0x3F);
            return 5;
        }
        *out_codepoint = -1;
        return -1;
    }
    
    unsigned char c5 = str[5];
    if ((c5 & 0xC0) != 0x80) {
        *out_codepoint = -1;
        return -1;
    }
    
    // 6-byte sequence (1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx)
    if ((c0 & 0x02) == 0) {
        if (((c0 & 0x01) | (c1 & 0x3C)) > 0) { // Overlong check
            *out_codepoint = ((c0 & 0x01) << 30) | ((c1 & 0x3F) << 24) | ((c2 & 0x3F) << 18) | ((c3 & 0x3F) << 12) | ((c4 & 0x3F) << 6) | (c5 & 0x3F);
            return 6;
        }
        *out_codepoint = -1;
        return -1;
    }
    
    // Invalid leading byte (1111111x)
    *out_codepoint = -1;
    return -1;
}
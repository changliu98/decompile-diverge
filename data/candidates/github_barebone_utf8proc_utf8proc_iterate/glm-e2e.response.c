ptrdiff_t utf8proc_iterate(const uint8_t *str, ptrdiff_t strlen, int32_t *codepoint) {
    const uint8_t *str_ptr = str;
    ptrdiff_t length = strlen;
    int32_t *cp_ptr = codepoint;
    
    // Default codepoint to -1 (0xFFFFFFFF)
    *cp_ptr = -1;
    
    ptrdiff_t ret;
    
    if (length == 0) {
        ret = 0;
        return ret;
    }
    
    const uint8_t *end = str_ptr + (length < 0 ? 4 : length);
    
    // Read first byte
    uint8_t ch = *str_ptr++;
    
    if (ch < 0x80) {
        // 1-byte sequence
        *cp_ptr = ch;
        ret = 1;
        return ret;
    } else if (ch - 0xc2 > 0x32) {
        // Invalid leading byte
        ret = -3;
        return ret;
    } else if (ch < 0xe0) {
        // 2-byte sequence
        if (str_ptr >= end || (*str_ptr & 0xc0) != 0x80) {
            ret = -3;
            return ret;
        }
        *cp_ptr = ((ch & 0x1f) << 6) | (*str_ptr & 0x3f);
        ret = 2;
        return ret;
    } else if (ch < 0xf0) {
        // 3-byte sequence
        if (str_ptr + 1 >= end || (*str_ptr & 0xc0) != 0x80 || (str_ptr[1] & 0xc0) != 0x80) {
            ret = -3;
            return ret;
        }
        if (ch == 0xed && *str_ptr > 0x9f) {
            // Surrogate pair
            ret = -3;
            return ret;
        }
        ch = ((ch & 0x0f) << 12) | ((*str_ptr & 0x3f) << 6) | (str_ptr[1] & 0x3f);
        if (ch < 0x800) {
            // Overlong sequence
            ret = -3;
            return ret;
        }
        *cp_ptr = ch;
        ret = 3;
        return ret;
    } else {
        // 4-byte sequence
        if (str_ptr + 2 >= end || (*str_ptr & 0xc0) != 0x80 || (str_ptr[1] & 0xc0) != 0x80 || (str_ptr[2] & 0xc0) != 0x80) {
            ret = -3;
            return ret;
        }
        if (ch == 0xf0 && *str_ptr < 0x90) {
            // Overlong sequence
            ret = -3;
            return ret;
        }
        if (ch == 0xf4 && *str_ptr > 0x8f) {
            // Codepoint > U+10FFFF
            ret = -3;
            return ret;
        }
        *cp_ptr = ((ch & 0x07) << 18) | ((*str_ptr & 0x3f) << 12) | ((str_ptr[1] & 0x3f) << 6) | (str_ptr[2] & 0x3f);
        ret = 4;
        return ret;
    }
}
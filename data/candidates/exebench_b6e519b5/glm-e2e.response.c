int u_get(uint32_t *out, const unsigned char *in) {
    unsigned char c = in[0];
    uint32_t cp;

    if (c < 0x80) {
        // 1-byte sequence: 0xxxxxxx
        *out = c;
        return 1;
    } else if (c < 0xC0) {
        // Invalid leading byte (10xxxxxx)
        return 0;
    } else if (c < 0xE0) {
        // 2-byte sequence: 110xxxxx 10xxxxxx
        cp = ((c & 0x1F) << 6) | (in[1] & 0x3F);
        *out = cp;
        // Check for overlong encoding (code point must be >= 0x80)
        return (cp & 0xFFFFFF80) ? 2 : 0;
    } else if (c < 0xF0) {
        // 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx
        cp = ((c & 0x0F) << 12) | ((in[1] & 0x3F) << 6) | (in[2] & 0x3F);
        *out = cp;
        // Check for overlong encoding (code point must be >= 0x800)
        return (cp & 0xFFFFF800) ? 3 : 0;
    } else if (c < 0xF8) {
        // 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        cp = ((c & 0x07) << 18) | ((in[1] & 0x3F) << 12) | 
             ((in[2] & 0x3F) << 6)  |  (in[3] & 0x3F);
        *out = cp;
        // Check for overlong encoding (code point must be >= 0x10000)
        return (cp & 0xFFFF0000) ? 4 : 0;
    } else if (c < 0xFC) {
        // 5-byte sequence: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        cp = ((c & 0x03) << 24) | ((in[1] & 0x3F) << 18) | 
             ((in[2] & 0x3F) << 12) | ((in[3] & 0x3F) << 6) | (in[4] & 0x3F);
        *out = cp;
        // Check for overlong encoding (code point must be >= 0x2000000)
        return (cp & 0xFFE00000) ? 5 : 0;
    } else if (c < 0xFE) {
        // 6-byte sequence: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        cp = ((c & 0x01) << 30) | ((in[1] & 0x3F) << 24) | 
             ((in[2] & 0x3F) << 18) | ((in[3] & 0x3F) << 12) | 
             ((in[4] & 0x3F) << 6)  |  (in[5] & 0x3F);
        *out = cp;
        // Check for overlong encoding (code point must be >= 0x40000000)
        return (cp & 0xFC000000) ? 6 : 0;
    } else {
        // Invalid byte (0xFE or 0xFF)
        return 0;
    }
}
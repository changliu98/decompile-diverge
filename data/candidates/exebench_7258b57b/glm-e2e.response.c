int UnicodeToUtf8(uint32_t unicode, char *out) {
    int len = 0;

    if (unicode <= 0x7f) {
        *out++ = (char)unicode;
        len = 1;
    } else if (unicode <= 0x7ff) {
        *out++ = (char)(0xc0 | (unicode >> 6));
        *out++ = (char)(0x80 | (unicode & 0x3f));
        len = 2;
    } else if (unicode == 0xfeff) {
        // BOM / Skip
    } else if (unicode >= 0xd800 && unicode <= 0xdfff) {
        // Surrogate pairs / Invalid
    } else if (unicode <= 0xffff) {
        *out++ = (char)(0xe0 | (unicode >> 12));
        *out++ = (char)(0x80 | ((unicode >> 6) & 0x3f));
        *out++ = (char)(0x80 | (unicode & 0x3f));
        len = 3;
    } else if (unicode > 0xffff) {
        *out++ = (char)(0xf0 | (unicode >> 18));
        *out++ = (char)(0x80 | ((unicode >> 12) & 0x3f));
        *out++ = (char)(0x80 | ((unicode >> 6) & 0x3f));
        *out++ = (char)(0x80 | (unicode & 0x3f));
        len = 4;
    }

    *out = '\0';
    return len;
}
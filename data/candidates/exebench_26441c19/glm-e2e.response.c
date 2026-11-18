int Utf8ToUnicode(const uint8_t *utf8, uint32_t *unicode, uint32_t *length, uint32_t max_len) {
    uint8_t c = *utf8;

    if ((c & 0xF8) == 0xF0) {
        // 4-byte UTF-8 sequence
        if (max_len < 4 || (utf8[1] & 0xC0) != 0x80 || (utf8[2] & 0xC0) != 0x80 || (utf8[3] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 4;
        *unicode = (c & 0x07);
        *unicode = (*unicode << 6) | (utf8[1] & 0x3F);
        *unicode = (*unicode << 6) | (utf8[2] & 0x3F);
        *unicode = (*unicode << 6) | (utf8[3] & 0x3F);
    } else if ((c & 0xF0) == 0xE0) {
        // 3-byte UTF-8 sequence
        if (max_len < 3 || (utf8[1] & 0xC0) != 0x80 || (utf8[2] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 3;
        *unicode = (c & 0x0F);
        *unicode = (*unicode << 6) | (utf8[1] & 0x3F);
        *unicode = (*unicode << 6) | (utf8[2] & 0x3F);
    } else if ((c & 0xE0) == 0xC0) {
        // 2-byte UTF-8 sequence
        if (max_len < 2 || (utf8[1] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 2;
        *unicode = (c & 0x1F);
        *unicode = (*unicode << 6) | (utf8[1] & 0x3F);
    } else if ((c & 0x80) == 0x00) {
        // 1-byte UTF-8 sequence
        *length = 1;
        *unicode = c;
    } else {
        // Invalid UTF-8 starting byte
        return 1;
    }

    return 0;
}
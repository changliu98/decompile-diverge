int Utf8ToUnicode(const uint8_t **utf8, uint32_t *unicode, uint32_t *length, uint64_t remaining) {
    uint8_t byte = **utf8;

    if ((byte & 0xF8) == 0xF0) {
        // 4-byte sequence
        if (remaining < 4 || ((*utf8)[1] & 0xC0) != 0x80 || ((*utf8)[2] & 0xC0) != 0x80 || ((*utf8)[3] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 4;
        *unicode = (byte & 0x07);
        *unicode = (*unicode << 6) | ((*utf8)[1] & 0x3F);
        *unicode = (*unicode << 6) | ((*utf8)[2] & 0x3F);
        *unicode = (*unicode << 6) | ((*utf8)[3] & 0x3F);
    } else if ((byte & 0xF0) == 0xE0) {
        // 3-byte sequence
        if (remaining < 3 || ((*utf8)[1] & 0xC0) != 0x80 || ((*utf8)[2] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 3;
        *unicode = (byte & 0x0F);
        *unicode = (*unicode << 6) | ((*utf8)[1] & 0x3F);
        *unicode = (*unicode << 6) | ((*utf8)[2] & 0x3F);
    } else if ((byte & 0xE0) == 0xC0) {
        // 2-byte sequence
        if (remaining < 2 || ((*utf8)[1] & 0xC0) != 0x80) {
            return 2;
        }
        *length = 2;
        *unicode = (byte & 0x1F);
        *unicode = (*unicode << 6) | ((*utf8)[1] & 0x3F);
    } else if ((byte & 0x80) == 0x00) {
        // 1-byte sequence
        *length = 1;
        *unicode = byte;
    } else {
        // Invalid byte
        return 1;
    }

    return 0;
}
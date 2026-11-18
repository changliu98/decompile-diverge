int utf8_decode_v2(const char *utf8char, size_t size, size_t *charlen)
{
    if (size == 0 || utf8char[0] == '\0') {
        if (charlen != NULL) {
            *charlen = 0;
        }
        return -1;
    }

    if ((utf8char[0] & 0x80) == 0) {
        if (charlen != NULL) {
            *charlen = 1;
        }
        return (utf8char[0] & 0x7F);
    }

    if ((utf8char[0] & 0xE0) == 0xC0) {
        if (charlen != NULL) {
            *charlen = 2;
        }
        if (size < 2 || utf8char[1] == '\0') {
            return -1;
        }
        return ((utf8char[0] & 0x1F) << 6) | (utf8char[1] & 0x3F);
    }

    if ((utf8char[0] & 0xF0) == 0xE0) {
        if (charlen != NULL) {
            *charlen = 3;
        }
        if (size < 3 || utf8char[1] == '\0' || utf8char[2] == '\0') {
            return -1;
        }
        return ((utf8char[0] & 0x0F) << 12) | ((utf8char[1] & 0x3F) << 6) | (utf8char[2] & 0x3F);
    }

    if ((utf8char[0] & 0xF8) == 0xF0) {
        if (charlen != NULL) {
            *charlen = 4;
        }
        if (size < 4 || utf8char[1] == '\0' || utf8char[2] == '\0' || utf8char[3] == '\0') {
            return -1;
        }
        return ((utf8char[0] & 0x07) << 15) | ((utf8char[1] & 0x3F) << 12) | ((utf8char[2] & 0x3F) << 6) | (utf8char[3] & 0x3F);
    }

    if (charlen != NULL) {
        *charlen = 0;
    }
    return -1;
}
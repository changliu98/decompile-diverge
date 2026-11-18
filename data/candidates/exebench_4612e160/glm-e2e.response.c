int utf8_decode_v2(const char *s, size_t len, size_t *bytes_read) {
    if (len == 0 || s[0] == '\0') {
        if (bytes_read != NULL) {
            *bytes_read = 0;
        }
        return -1;
    }

    if ((s[0] & 0x80) == 0) {
        if (bytes_read != NULL) {
            *bytes_read = 1;
        }
        return s[0] & 0x7F;
    } else if ((s[0] & 0xE0) == 0xC0) {
        if (bytes_read != NULL) {
            *bytes_read = 2;
        }
        if (len < 2 || s[1] == '\0') {
            return -1;
        }
        return ((s[0] & 0x1F) << 6) | (s[1] & 0x3F);
    } else if ((s[0] & 0xF0) == 0xE0) {
        if (bytes_read != NULL) {
            *bytes_read = 3;
        }
        if (len < 3 || s[1] == '\0' || s[2] == '\0') {
            return -1;
        }
        return ((s[0] & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
    } else if ((s[0] & 0xF8) == 0xF0) {
        if (bytes_read != NULL) {
            *bytes_read = 4;
        }
        if (len < 4 || s[1] == '\0' || s[2] == '\0' || s[3] == '\0') {
            return -1;
        }
        return ((s[0] & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
    } else {
        if (bytes_read != NULL) {
            *bytes_read = 0;
        }
        return -1;
    }
}
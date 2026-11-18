static size_t utf8BytesToCodePoint(const char* buf, size_t len, int* cp) {
    if (len) {
        unsigned char byte = buf[0];
        if ((byte & 0x80) == 0) {
            *cp = byte;
            return 1;
        } else if ((byte & 0xE0) == 0xC0) {
            if (len >= 2) {
                *cp = (((unsigned long)(buf[0] & 0x1F)) << 6) |
                       ((unsigned long)(buf[1] & 0x3F));
                return 2;
            }
        } else if ((byte & 0xF0) == 0xE0) {
            if (len >= 3) {
                *cp = (((unsigned long)(buf[0] & 0x0F)) << 12) |
                      (((unsigned long)(buf[1] & 0x3F)) << 6) |
                       ((unsigned long)(buf[2] & 0x3F));
                return 3;
            }
        } else if ((byte & 0xF8) == 0xF0) {
            if (len >= 4) {
                *cp = (((unsigned long)(buf[0] & 0x07)) << 18) |
                      (((unsigned long)(buf[1] & 0x3F)) << 12) |
                      (((unsigned long)(buf[2] & 0x3F)) << 6) |
                       ((unsigned long)(buf[3] & 0x3F));
                return 4;
            }
        }
    }
    return 0;
}
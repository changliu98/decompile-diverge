const unsigned char *utf8_to_ucs4(const unsigned char *str, uint32_t *ucs4) {
    uint32_t code = 0;
    const unsigned char *p = str;
    unsigned char c = *p++;
    int bytes = 0;
    int shift = 0;
    int i = 0;

    if ((c & 0x80) == 0) {
        bytes = 1;
        code = c;
    } else if ((c & 0xE0) == 0xC0) {
        bytes = 2;
        code = c & 0x1F;
    } else if ((c & 0xF0) == 0xE0) {
        bytes = 3;
        code = c & 0x0F;
    } else if ((c & 0xF8) == 0xF0) {
        bytes = 4;
        code = c & 0x07;
    } else if ((c & 0xFC) == 0xF8) {
        bytes = 5;
        code = c & 0x03;
    } else if ((c & 0xFE) == 0xFC) {
        bytes = 6;
        code = c & 0x01;
    } else {
        return NULL;
    }

    shift = (bytes - 1) * 6;
    code <<= shift;

    for (i = 1; i < bytes; i++) {
        shift -= 6;
        c = *p++;
        if ((c & 0xC0) != 0x80) {
            return NULL;
        }
        code |= (c & 0x3F) << shift;
    }

    if (ucs4 != NULL) {
        *ucs4 = code;
    }

    return p;
}
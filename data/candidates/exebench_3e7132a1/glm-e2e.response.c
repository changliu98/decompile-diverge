int _chartorune(uint16_t *rune, const unsigned char *str) {
    unsigned char c1 = str[0];
    int len = 1;

    if (c1 < 0x80) {
        *rune = c1;
        return 1;
    }

    unsigned char c2 = str[1] ^ 0x80;
    if ((c2 & 0xC0) != 0) {
        goto invalid;
    }

    if (c1 < 0xE0) {
        if (c1 < 0xC0) {
            goto invalid;
        }
        long val = (c1 << 6 | c2) & 0x7FF;
        if (val <= 0x7F) {
            goto invalid;
        }
        *rune = (uint16_t)val;
        return 2;
    } else {
        unsigned char c3 = str[2] ^ 0x80;
        if ((c3 & 0xC0) != 0) {
            goto invalid;
        }
        if (c1 >= 0xF0) {
            goto invalid;
        }
        long val = ((c1 << 6 | c2) << 6 | c3) & 0xFFFF;
        if (val <= 0x7FF) {
            goto invalid;
        }
        *rune = (uint16_t)val;
        return 3;
    }

invalid:
    *rune = 0x80;
    return 1;
}
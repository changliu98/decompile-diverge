int get_char_utf8(int *ch, const char *s)
{
    int c1, c2, c3, c4, c5, c6;

    c1 = (unsigned char)s[0];
    if (c1 < 0x80) {
        *ch = c1;
        return c1 ? 1 : 0;
    }
    if (c1 < 0x40) {
        *ch = -1;
        return -1;
    }
    c2 = (unsigned char)s[1];
    if ((c2 & 0xc0) != 0x80) {
        *ch = -1;
        return -1;
    }
    if (c1 < 0x20) {
        if (c1 < 0x1e) {
            *ch = -1;
            return -1;
        }
        *ch = ((c1 & 0x1f) << 6) | (c2 & 0x3f);
        return 2;
    }
    c3 = (unsigned char)s[2];
    if ((c3 & 0xc0) != 0x80) {
        *ch = -1;
        return -1;
    }
    if (c1 < 0x10) {
        if (c1 < 0x0f || (c2 & 0x20)) {
            *ch = -1;
            return -1;
        }
        *ch = ((c1 & 0x0f) << 12) | ((c2 & 0x3f) << 6) | (c3 & 0x3f);
        return 3;
    }
    c4 = (unsigned char)s[3];
    if ((c4 & 0xc0) != 0x80) {
        *ch = -1;
        return -1;
    }
    if (c1 < 0x08) {
        if (c1 < 0x07 || (c2 & 0x30)) {
            *ch = -1;
            return -1;
        }
        *ch = ((c1 & 0x07) << 18) | ((c2 & 0x3f) << 12) |
              ((c3 & 0x3f) << 6) | (c4 & 0x3f);
        return 4;
    }
    c5 = (unsigned char)s[4];
    if ((c5 & 0xc0) != 0x80) {
        *ch = -1;
        return -1;
    }
    if (c1 < 0x04) {
        if (c1 < 0x03 || (c2 & 0x38)) {
            *ch = -1;
            return -1;
        }
        *ch = ((c1 & 0x03) << 24) | ((c2 & 0x3f) << 18) |
              ((c3 & 0x3f) << 12) | ((c4 & 0x3f) << 6) | (c5 & 0x3f);
        return 5;
    }
    c6 = (unsigned char)s[5];
    if ((c6 & 0xc0) != 0x80) {
        *ch = -1;
        return -1;
    }
    if (c1 < 0x02) {
        if (c1 < 0x01 || (c2 & 0x3c)) {
            *ch = -1;
            return -1;
        }
        *ch = ((c1 & 0x01) << 30) | ((c2 & 0x3f) << 24) |
              ((c3 & 0x3f) << 18) | ((c4 & 0x3f) << 12) |
              ((c5 & 0x3f) << 6) | (c6 & 0x3f);
        return 6;
    }
    *ch = -1;
    return -1;
}
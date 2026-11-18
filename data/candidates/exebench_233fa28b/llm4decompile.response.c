size_t utf8BytesToCodePoint(const char *buf, size_t len, int *cp)
{
    if (len == 0) {
        return 0;
    }

    if ((buf[0] & 0x80) == 0) {
        *cp = buf[0];
        return 1;
    }

    if ((buf[0] & 0xE0) == 0xC0) {
        if (len < 2) {
            return 0;
        }
        *cp = ((buf[0] & 0x1F) << 6) | (buf[1] & 0x3F);
        return 2;
    }

    if ((buf[0] & 0xF0) == 0xE0) {
        if (len < 3) {
            return 0;
        }
        *cp = ((buf[0] & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
        return 3;
    }

    if ((buf[0] & 0xF8) == 0xF0) {
        if (len < 4) {
            return 0;
        }
        *cp = ((buf[0] & 0x07) << 18) | ((buf[1] & 0x3F) << 12) | ((buf[2] & 0x3F) << 6) | (buf[3] & 0x3F);
        return 4;
    }

    return 0;
}
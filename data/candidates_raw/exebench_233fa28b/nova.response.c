static size_t func0(const char *s, size_t len, uint32_t *v)
{
    size_t ret;
    uint8_t b;

    if (len == 0)
        return 0;

    b = *s;
    if ((b & 0x80) == 0) {
        *v = b;
        ret = 1;
    } else if ((b & 0xe0) == 0xc0) {
        if (len < 2)
            return 0;
        *v = (b & 0x1f) << 6;
        *v |= (s[1] & 0x3f);
        ret = 2;
    } else if ((b & 0xf0) == 0xe0) {
        if (len < 3)
            return 0;
        *v = (b & 0x0f) << 12;
        *v |= (s[1] & 0x3f) << 6;
        *v |= (s[2] & 0x3f);
        ret = 3;
    } else if ((b & 0xf8) == 0xf0) {
        if (len < 4)
            return 0;
        *v = (b & 0x07) << 18;
        *v |= (s[1] & 0x3f) << 12;
        *v |= (s[2] & 0x3f) << 6;
        *v |= (s[3] & 0x3f);
        ret = 4;
    } else {
        return 0;
    }

    return ret;
}
int _chartorune(unsigned short *rune, char *str)
{
    unsigned char c1; unsigned char c2; unsigned char c3;
    unsigned short u;
    c1 = (unsigned char) *str;
    if (c1 < 0x80) {
        *rune = c1;
        return 1;
    }
    c2 = (unsigned char) *(str + 1) ^ 0x80;
    if (c2 & 0xc0) {
        *rune = 128;
        return 1;
    }
    if (c1 < 0xe0) {
        u = c1 & 0x1f;
        u <<= 6;
        u |= c2 & 0x3f;
        if (u < 0x80) {
            *rune = 128;
            return 1;
        }
        *rune = u;
        return 2;
    }
    c3 = (unsigned char) *(str + 2) ^ 0x80;
    if (c3 & 0xc0) {
        *rune = 128;
        return 1;
    }
    if (c1 >= 0xf0) {
        *rune = 128;
        return 1;
    }
    u = c1 & 0x0f;
    u <<= 6;
    u |= c2 & 0x3f;
    u <<= 6;
    u |= c3 & 0x3f;
    if (u < 0x800) {
        *rune = 128;
        return 1;
    }
    *rune = u;
    return 3;
}
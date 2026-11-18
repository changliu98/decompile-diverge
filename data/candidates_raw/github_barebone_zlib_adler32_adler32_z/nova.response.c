uint64_t func0(uint64_t x, uint8_t *p, size_t len) {
    uint64_t a, b;
    a = x >> 16;
    b = x & 0xffff;
    if (len == 1) {
        a += p[0];
        if (a >= 0xffe1)
            a -= 0xffe1;
        b += p[0];
        if (b >= 0xffe1)
            b -= 0xffe1;
    } else {
        if (p == NULL) {
            a = 1;
        } else {
            while (len--) {
                a += *p++;
                b += a;
            }
            if (a >= 0xffe1)
                a -= 0xffe1;
            b %= 0xffe1;
        }
    }
    return (a << 16) | b;
}
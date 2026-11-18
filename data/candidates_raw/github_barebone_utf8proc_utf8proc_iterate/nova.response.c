static size_t func0(const unsigned char *s, size_t len, int *c)
{
    size_t n;
    int c1;

    *c = -1;
    if (len == 0)
        return 0;

    for (n = 0;; ++n) {
        if (len <= n) {
            *c = c1;
            return n;
        }
        c1 = s[n];
        if (c1 < 0x80) {
            *c = c1;
            return n + 1;
        }
        if (c1 >= 0xC2 && c1 < 0xE0) {
            if (len <= n + 1) {
                *c = c1;
                return n;
            }
            if ((s[n + 1] & 0xC0)!= 0x80) {
                *c = c1;
                return n;
            }
            *c = ((c1 & 0x1F) << 6) | (s[n + 1] & 0x3F);
            return n + 2;
        }
        if (c1 >= 0xE1 && c1 < 0xF0) {
            if (len <= n + 2) {
                *c = c1;
                return n;
            }
            if ((s[n + 1] & 0xC0)!= 0x80 || (s[n + 2] & 0xC0)!= 0x80) {
                *c = c1;
                return n;
            }
            *c = ((c1 & 0x0F) << 12) | ((s[n + 1] & 0x3F) << 6) | (s[n + 2] & 0x3F);
            return n + 3;
        }
        if (c1 >= 0xF1 && c1 < 0xF5) {
            if (len <= n + 3) {
                *c = c1;
                return n;
            }
            if ((s[n + 1] & 0xC0)!= 0x
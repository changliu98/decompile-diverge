void grad1(int c, float *p) {
    int sign;
    int exp;
    float frac;

    sign = (c >> 15) & 0x1;
    exp = (c >> 7) & 0x7f;
    frac = c & 0x7f;

    *p = (sign? -1 : 1) * (exp + 64) * (1 + frac);
}
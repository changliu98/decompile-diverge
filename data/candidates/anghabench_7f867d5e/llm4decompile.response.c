unsigned char gfmul(unsigned char a, unsigned char b) {
    unsigned char result = 0;
    while (b != 0) {
        if (b & 1) {
            result ^= a;
        }
        a <<= 1;
        if (a & 0x80) {
            a ^= 0x1d;
        }
        b >>= 1;
    }
    return result;
}
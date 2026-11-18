int mul_poly(int a, int b, int c) {
    int result = 0;
    while (a != 0) {
        if (a & 1) {
            result ^= b;
        }
        a >>= 1;
        b <<= 1;
        if (b & 0x10000) {
            b ^= c;
        }
    }
    return result;
}
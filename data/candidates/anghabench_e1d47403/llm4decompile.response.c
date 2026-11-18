word16 mul_poly(word16 a, word16 b, word16 poly)
{
    unsigned int acc = a;
    unsigned int res = 0;
    while (acc != 0) {
        if (acc & 1) {
            res ^= b;
        }
        acc >>= 1;
        b <<= 1;
        if (b & 0x10000) {
            b ^= poly;
        }
    }
    return res;
}
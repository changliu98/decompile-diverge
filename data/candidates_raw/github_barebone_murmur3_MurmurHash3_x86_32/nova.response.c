void func0(uint32_t *seed, uint32_t n, uint32_t m, uint32_t *result) {
    uint32_t *s = seed;
    uint32_t i = n / 4;
    uint32_t j = m;
    uint32_t t = 0x9e3779b9;
    uint32_t a = 0x12345671;
    uint32_t b = 0x23456712;

    while (1) {
        uint32_t k = s[i];
        k *= t;
        k = ROT(k, 13);
        k *= a;
        k = ROT(k, 17);
        k *= b;
        j ^= k;
        j = ROT(j, 15);
        j *= t;
        j = ROT(j, 27);
        j *= a;
        j = ROT(j, 17);
        j *= b;
        j = j ^ (j >> 15);
        j *= 0x80000005;
        j = j ^ (j >> 16);
        j *= 0x80000005;
        j = j ^ (j >> 16);
        *result = j;
        return;
    }
}
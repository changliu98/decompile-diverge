uint64_t xorshf96(uint64_t *x, uint64_t *y, uint64_t *z) {
    uint64_t tmp;

    *x ^= *x << 16;
    *x ^= *x >> 5;
    *x ^= *x << 1;

    tmp = *x;
    *x = *y;
    *y = *z;
    *z = tmp ^ *x ^ *y;

    return *z;
}
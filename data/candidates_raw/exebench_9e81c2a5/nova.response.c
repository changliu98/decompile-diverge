void func0(uint64_t *state, uint64_t *key) {
    uint64_t x = state[0], y = state[1];
    uint64_t z = 0x237841654b87de3f;
    uint64_t m = 0x3fffffffffffffff;
    for (uint64_t i = 0;; i++) {
        if (i >= 32)
            break;
        x = (x ^ (x >> 5)) + (y ^ (y << 3)) + key[z % 4];
        z = (z ^ (z >> 11)) + (x ^ (x << 1));
        y = (y ^ (y >> 11)) + (z ^ (z << 3));
    }
    state[0] = x;
    state[1] = y;
}
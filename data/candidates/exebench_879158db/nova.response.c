static inline uint64_t xorshf96(uint64_t *state, uint64_t *data, uint64_t *data2) {
        uint64_t x = *state;

        x ^= x << 16;
        x ^= x >> 5;
        x ^= x << 1;

        *state = x;

        x = *data;
        *data = *data2;
        *data2 = x ^ x << 2;

        return *data ^ *data2;
}
static void wyhash(const uint8_t *in, size_t n, uint64_t key,
                             const struct cipher_block *iv) {
    uint64_t x[4];
    uint64_t y[4];
    uint64_t z[4];
    uint64_t t;

    x[0] = iv->x;
    x[1] = iv->y;
    x[2] = iv->z;
    x[3] = iv->w;

    while (n >= 16 && (n & 1) == 0) {
        t = x[0];
        x[0] = x[1];
        x[1] = x[2];
        x[2] = x[3];
        x[3] = t;

        x[0] = xor64(x[0], key);
        x[1] = xor64(x[1], xor64(x[2], x[3]));
        x[2] = xor64(x[2], xor64(x[0], x[1]));
        x[3] = xor64(x[3], xor64(x[1], x[2]));

        key = xor64(x[0], x[1]);
        key = xor64(key, x[2]);
        key = xor64(key, x[3]);

        x[0] = xor64(x[0], xor64(x[1], x[2]));
        x[1] = xor64(x[1], xor64(x[2], x[3]));
        x[2] = xor64(x[2], xor64(x[0], x[1]));
        x[3] = xor64(x[3], xor64(x[1], x[2]));

        y[0] = xor64(x[0], x[1]);
        y[1] = xor64(x[1
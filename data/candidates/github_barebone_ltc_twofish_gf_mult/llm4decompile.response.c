extern uint8_t gf_mult(uint8_t a, uint8_t b, uint8_t p) {
    uint8_t result;
    uint8_t B[2];
    uint8_t P[2];

    P[1] = p;
    B[1] = b;
    B[0] = 0;
    P[0] = 0;

    result = 0;

    for (uint8_t i = 0; i < 8; i++) {
        B[1] = (B[1] << 1) ^ ((B[1] >> 7) * P[1]);
    }

    for (uint8_t i = 0; i < 8; i++) {
        result ^= B[(a >> i) & 1];
    }

    return result;
}
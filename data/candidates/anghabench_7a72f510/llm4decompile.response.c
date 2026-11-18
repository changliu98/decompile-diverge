extern uint32_t gf_poly_mul2(uint32_t x) {
    uint32_t x0 = x & 0x7f7f7f7f;
    uint32_t x1 = (x & 0x80808080) >> 7;
    return (x0 << 1) ^ (x1 * 0x1b);
}
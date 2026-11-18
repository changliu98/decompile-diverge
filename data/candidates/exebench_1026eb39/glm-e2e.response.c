void ut32_unpack(const uint8_t *in, uint32_t *out) {
    uint32_t u = in[3];
    u = (u << 8) + in[2];
    u = (u << 8) + in[1];
    u = (u << 8) + in[0];
    *out = u;
}
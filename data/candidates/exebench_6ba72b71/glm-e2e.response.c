void measure(uint64_t *val, uint32_t *out1, uint32_t *out2, uint32_t *out3, uint32_t *out4) {
    *val = 0xf780;
    *out1 = (uint32_t)*val;
    *out2 = (uint32_t)((double)*val * 0.0001);
    *out3 = (uint32_t)((double)*val * 0.001);
    *out4 = (uint32_t)((double)*val * 0.01);
}
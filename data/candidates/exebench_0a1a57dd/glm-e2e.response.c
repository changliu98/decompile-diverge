void htonf(float *f) {
    uint32_t val = *(uint32_t *)f;
    *(uint32_t *)f = htonl(val);
}
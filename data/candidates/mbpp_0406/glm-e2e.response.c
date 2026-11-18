const char *func0(uint32_t n) {
    uint32_t x = n;
    x ^= x >> 1;
    x ^= x >> 2;
    x ^= x >> 4;
    x ^= x >> 8;
    x ^= x >> 16;
    
    if ((x & 1) != 0) {
        return "True";
    } else {
        return "False";
    }
}
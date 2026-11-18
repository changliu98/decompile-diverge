static inline void func0(const char *data, uint64_t *num) {
    uint64_t n = 0;
    uint8_t index = 0;
    n = data[index++];
    n = (n << 8) + data[index++];
    n = (n << 8) + data[index++];
    n = (n << 8) + data[index++];
    n = (n << 8) + data[index++];
    *num = n;
}
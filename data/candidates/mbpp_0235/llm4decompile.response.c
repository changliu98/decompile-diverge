uint64_t func0(uint64_t n) {
    uint64_t temp = n;
    uint64_t res = 0;
    int count = 0;
    while (temp > 0) {
        if (count % 2 == 1) {
            res |= (1 << count);
        }
        count++;
        temp >>= 1;
    }
    return res | n;
}
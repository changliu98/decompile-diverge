uint64_t t_add(uint64_t a, uint64_t b, int *flag) {
    if (*flag != 0) {
        uint64_t sum = a + b;
        uint64_t max_val = (a > b) ? a : b;
        *flag = (sum >= max_val);
    }

    if (*flag != 0) {
        return a + b;
    } else {
        return 0;
    }
}
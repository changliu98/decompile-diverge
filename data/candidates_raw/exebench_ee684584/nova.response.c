int func0(double *num, double val, size_t size) {
    size_t i = 0;

    for (i = 0; i < size; i++) {
        if (num[i] > val) {
            num[i] = val;
        }
    }

    return 0;
}
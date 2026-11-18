bool mmeq(const float *a, const float *b, unsigned long n, unsigned long m) {
    for (unsigned long i = 0; i < n * m; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
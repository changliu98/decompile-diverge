int ilog2(unsigned long n) {
    int i = 0;
    while ((1UL << i) < n) {
        i++;
    }
    return i;
}
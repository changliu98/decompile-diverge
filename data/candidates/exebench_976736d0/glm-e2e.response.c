unsigned long long div10quickm(unsigned long long *n) {
    unsigned long long x = *n;
    unsigned long long q = (x >> 1) + (x >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 3;
    unsigned long long r = x - (((q << 2) + q) << 1);
    *n = q + (r >> 9);
    return x - (((*n << 1) << 2) + *n);
}
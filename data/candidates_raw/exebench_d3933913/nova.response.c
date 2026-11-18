double func0(unsigned long long *x) {
    unsigned long long z;
    double y;

    *x ^= 0xabcdef012345678;
    z = *x / 16807ull;
    *x = *x * 16807ull - z * 127773ull;
    if (*x < 0)
        *x += 2147483647;
    y = (double)(*x) / 2147483647.0;
    *x ^= 0xabcdef012345678;
    return y;
}
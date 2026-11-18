long xdl_bogosqrt(long n) {
    long x = 1;
    while (n > 0) {
        x <<= 1;
        n >>= 2;
    }
    return x;
}
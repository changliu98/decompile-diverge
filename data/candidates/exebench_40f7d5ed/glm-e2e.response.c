double ran0bis(long *idum) {
    long k = *idum / 0x1f31d;
    *idum = 0x41a7 * (*idum - k * 0x1f31d) - 0xb14 * k;
    if (*idum < 0) {
        *idum += 0x7fffffff;
    }
    return (double)*idum * 4.6566128752457969e-10; // 1 / 2147483648.0
}
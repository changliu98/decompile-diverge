double ran0(long *idum) {
    long k;
    double ans;

    *idum ^= 0x75bd924;
    k = *idum / 0x1f31d;
    *idum = 0x41a7 * (*idum - k * 0x1f31d) - 0xb14 * k;
    if (*idum < 0) {
        *idum += 0x7fffffff;
    }
    ans = (double)(*idum) * 4.656612875245796e-10; // 1 / 2147483647.0
    *idum ^= 0x75bd924;
    
    return ans;
}
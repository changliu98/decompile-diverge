double randum(long long *state) {
    long long A = 0x60d; // 1549
    long long B = 0x196; // 406
    long long s = *state;

    // Extract the three "digits" (base 4096, 4096, 256)
    long long d0 = s & 0xfff;
    long long d1 = (s >> 12) & 0xfff;
    long long d2 = (s >> 24) & 0xff;

    // First multiplication step
    long long p = A * d0;
    long long r0 = p & 0xfff;
    p >>= 12;

    // Second multiplication step
    p += A * d1 + B * d0;
    long long r1 = p & 0xfff;
    p >>= 12;

    // Third multiplication step
    p += A * d2 + B * d1;
    long long r2 = p & 0xff;

    // Recombine and store the new state
    *state = (r2 << 24) | (r1 << 12) | r0;

    // Normalize to a double between 0.0 and 1.0
    // The constants at 0x2008 and 0x2010 are 1.0 / 256.0 and 1.0 / 4096.0 respectively
    return (double)r2 * (1.0 / 256.0) + 
           (double)r1 * (1.0 / 4096.0) * (1.0 / 256.0) + 
           (double)r0 * (1.0 / 4096.0) * (1.0 / 256.0);
}
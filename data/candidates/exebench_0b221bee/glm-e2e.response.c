double frexp(double x, int *exp) {
    int e = 0;
    double factor = 1.0;

    // If x is negative, make it positive and set factor to -1.0
    if (0.0 > x) {
        uint64_t bits;
        __builtin_memcpy(&bits, &x, sizeof(bits));
        bits ^= 0x8000000000000000ULL; // Clear the sign bit
        __builtin_memcpy(&x, &bits, sizeof(bits));
        factor = -1.0;
    }

    // If x is 0.0 or NaN, skip the normalization loops
    if (x != 0.0) {
        // Scale down if x >= 1.0
        if (x >= 1.0) {
            do {
                e += 1;
                x *= 0.5;
            } while (x >= 1.0);
        } 
        // Scale up if x < 0.5
        else if (0.5 > x) {
            do {
                e -= 1;
                x *= 2.0;
            } while (0.5 > x);
        }
    }

    *exp = e;
    return x * factor;
}
double ran1(int64_t *idum) {
    int32_t j;
    int64_t k;
    double temp;

    // Initialization block
    if (*idum > 0 || iy != 0) {
        // Skip initialization
    } else {
        // Ensure idum is not 0 and take its absolute value
        if (-(*idum) < 1) {
            *idum = 1;
        } else {
            *idum = -(*idum);
        }

        // Initialize the shuffling table
        for (j = 39; j >= 0; j--) {
            k = *idum / 127773;
            *idum = 16807 * (*idum - k * 127773) - 2836 * k;
            if (*idum < 0) {
                *idum += 2147483647;
            }
            if (j < 32) {
                iv[j] = *idum;
            }
        }
        iy = iv[0];
    }

    // Main random number generation loop
    k = *idum / 127773;
    *idum = 16807 * (*idum - k * 127773) - 2836 * k;
    if (*idum < 0) {
        *idum += 2147483647;
    }

    // Pick a random index from the shuffling table
    j = iy / 67108864;  // Equivalent to iy >> 26
    iy = iv[j];
    iv[j] = *idum;

    // Scale the output to the range [0, 1)
    temp = (double)iy * 4.656612875245797e-10; // 1.0 / 2147483647.0
    if (temp > 0.99999988) {
        temp = 0.99999988;
    }

    return temp;
}
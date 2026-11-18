float ran1(int64_t *idum) {
    int32_t j;
    int64_t k;
    float temp;

    // Initialization or re-seeding block
    if (*idum <= 0 || iy == 0) {
        if (-(*idum) < 1) {
            *idum = 1;
        } else {
            *idum = -(*idum);
        }

        // Warm up the shuffling array
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

    // Main random number generation
    k = *idum / 127773;
    *idum = 16807 * (*idum - k * 127773) - 2836 * k;
    if (*idum < 0) {
        *idum += 2147483647;
    }

    // Bays-Durham shuffle
    j = iy / 67108864;          // Equivalent to iy >> 26
    iy = iv[j];
    iv[j] = *idum;

    // Scale to float [0, 1)
    temp = (float)(iy * 4.656612875245797e-10); // 1.0 / 2147483647.0
    
    // Bounds check to prevent returning exactly 1.0
    if (temp > 0.99999988f) {
        return 0.99999988f;
    } else {
        return temp;
    }
}
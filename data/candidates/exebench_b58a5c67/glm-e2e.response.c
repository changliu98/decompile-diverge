void r2d(double *r, double *d, int *dd, double *mm, char *sign, int *m, double *s) {
    // Constants loaded from memory
    const float RAD_TO_DEG = 57.295776f; // 0xe20(%rip)
    const double DEG_IN_CIRCLE = 360.0;   // 0x2008(%rip)
    const double DEG_HALF_CIRCLE = 180.0; // 0x2010(%rip)
    const double SEC_PER_MIN = 60.0;      // 0x2018(%rip)
    const double HALF_MIN = 30.0;         // 0x2020(%rip)

    char neg_sign = '-';
    char pos_sign = '+';

    // Calculate total degrees from radians
    float total_degrees = ((float)(*r) / (double)RAD_TO_DEG) / DEG_IN_CIRCLE;

    // Normalize degrees to the range (0, 180]
    while ((double)total_degrees > DEG_HALF_CIRCLE) {
        total_degrees = (float)((double)total_degrees - DEG_HALF_CIRCLE);
    }

    // Extract integer degrees
    *dd = (int)total_degrees;

    // Calculate minutes
    double minutes = (double)(total_degrees - (float)(*dd)) * SEC_PER_MIN;
    *mm = minutes + HALF_MIN;

    // Adjust for overflow in minutes
    if (*mm >= SEC_PER_MIN) {
        *mm -= SEC_PER_MIN;
        *dd += 1;
    }

    // Normalize degrees to [0, 24)
    if (*dd >= 24) {
        *dd -= 24;
    }

    // Determine sign and absolute value of the second coordinate (d)
    if (*d > 0.0) {
        *sign = neg_sign;
        // Flip the sign bit of the double
        long long bits = *(long long *)d;
        bits ^= 0x8000000000000000LL;
        *d = *(double *)&bits;
    } else {
        *sign = pos_sign;
    }

    // Process the second coordinate (d)
    float d_degrees = (float)(*d) / (double)RAD_TO_DEG;
    *m = (int)d_degrees;

    // Calculate seconds
    *s = (double)(d_degrees - (float)(*m)) * SEC_PER_MIN;
}
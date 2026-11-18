double GO_frexp(double x, int *exp) {
    int e = 0;
    double sign = 1.0;

    // If x is negative, make it positive and record the sign
    if (x < 0.0) {
        x = -x;
        sign = -1.0;
    }

    // If x is 0.0 or NaN, skip the normalization loops
    if (x != 0.0) {
        // Scale down if x >= 1.0
        while (x >= 1.0) {
            e += 1;
            x *= 0.5;
        }

        // Scale up if x < 0.5
        while (x < 0.5) {
            e -= 1;
            x *= 2.0;
        }
    }

    // Store the exponent and restore the sign to the mantissa
    *exp = e;
    return x * sign;
}
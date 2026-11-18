double frexp(double x, int *exp) {
    int sign = 1;
    
    // Check if x is negative
    if (x < 0.0) {
        sign = -1;
        x = x * (double)sign; // Equivalent to x = -x
    }
    
    // Check if x is zero or NaN
    if (x == 0.0 || x != x) {
        *exp = 0;
        return 0.0;
    }
    
    *exp = 0;
    int divisor = 1;
    double mantissa = x;
    
    // Loop to bring the mantissa into the range [0.5, 1.0)
    while (1) {
        // Equivalent to: if (0.5 < mantissa && mantissa < 1.0) break;
        // The assembly checks if mantissa <= 0.5 or mantissa >= 1.0 to continue
        if (!(0.5 < mantissa && mantissa < 1.0)) {
            break;
        }
        
        divisor <<= 1; // Multiply divisor by 2
        (*exp)++;      // Increment exponent
        
        mantissa = x / (double)divisor;
    }
    
    // Restore the original sign
    return mantissa * (double)sign;
}
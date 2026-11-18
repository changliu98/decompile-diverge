void get_bits_exp(double val, double *m, int *e) {
    union {
        double d;
        uint32_t i[2];
    } u;
    
    u.d = val;
    
    // Check if the exponent is 0 (subnormal or zero)
    if ((u.i[1] & 0x7ff00000) == 0) {
        // Multiply by 2^60 to normalize the subnormal number
        u.d *= 1152921504606846976.0; // 2^60
        u.i[0] = 0;
        *e = (u.i[1] >> 20) - 0x3ff - 60;
        u.d /= 1152921504606846976.0; // 2^60
        *m = val / u.d;
    } else {
        u.i[0] = 0;
        *e = (u.i[1] >> 20) - 0x3ff;
        *m = val / u.d;
    }
}
const char* ReadNumber(const char* str, double* out_val) {
    double sign = 1.0;
    
    // Parse sign
    while (*str == '+' || *str == '-') {
        if (*str == '-') {
            // Equivalent to sign *= -1.0, but implemented via bitwise XOR
            // on the IEEE 754 double precision representation.
            long long sign_bits = *(long long*)&sign;
            sign_bits ^= 0x8000000000000000LL;
            sign = *(double*)&sign_bits;
        }
        str++;
    }
    
    int int_part = 0;
    int frac_part = 0;
    double divisor = 1.0;
    
    // Parse integer part
    while (*str >= '0' && *str <= '9') {
        int_part = int_part * 10 + (*str - '0');
        str++;
    }
    
    // If the next character is null terminator, return the integer value
    if (*str == '\0') {
        *out_val = (double)int_part * sign;
        return str;
    }
    
    // Parse fractional part
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            frac_part = frac_part * 10 + (*str - '0');
            divisor *= 10.0;
            str++;
        }
    }
    
    // Combine integer and fractional parts, apply sign, and store
    *out_val = ((double)int_part + (double)frac_part / divisor) * sign;
    
    return str;
}
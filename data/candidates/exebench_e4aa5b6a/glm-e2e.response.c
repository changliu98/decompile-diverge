int util_read_dec(const char *str, int *out_val) {
    int is_negative = 0;
    int length = 0;
    long long val = 0;

    *out_val = 0;

    // Check for negative sign
    if (*str == '-') {
        is_negative = 1;
        str++;
        length++;
    }

    // Parse digits
    while (*str != '\0') {
        int digit = *str - '0';
        if (digit < 0 || digit > 9) {
            break;
        }
        
        val = val * 10 + digit;
        
        // Check for 32-bit signed integer overflow
        if (val > 0x7fffffff) {
            break;
        }
        
        str++;
        length++;
        *out_val = (int)val;
    }

    // Apply negative sign if applicable
    if (is_negative) {
        // If the only character parsed was '-', return 0
        if (length == 1) {
            return 0;
        }
        *out_val = -*out_val;
    }

    return length;
}
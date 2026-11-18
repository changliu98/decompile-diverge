int utoa(char *buf, unsigned int value, int base) {
    char buffer[32];
    char *pos = buffer + sizeof(buffer) - 1;
    char *out = buf;
    
    const char hex_lower[] = "0123456789abcdef";
    const char hex_upper[] = "0123456789ABCDEF";
    const char *digits = hex_lower;
    int base_val = 0;
    int len;

    switch (base) {
        case 8:
            base_val = 8;
            break;
        case 10:
            base_val = 10;
            break;
        case 16:
            base_val = 16;
            digits = hex_lower;
            break;
        case 32: // Base 32 is handled as an alias for uppercase base 16
            base_val = 16;
            digits = hex_upper;
            break;
        default:
            return -1;
    }

    do {
        int rem = value % base_val;
        if (base_val == 8 || base_val == 16) {
            *--pos = digits[rem & (base_val - 1)];
        } else { // base_val == 10
            *--pos = (char)(rem + '0');
        }
        value /= base_val;
    } while (value != 0);

    pos++;
    
    while (pos < buffer + sizeof(buffer)) {
        *out++ = *pos++;
    }
    
    *out = '\0';
    len = out - buf;
    
    return len;
}
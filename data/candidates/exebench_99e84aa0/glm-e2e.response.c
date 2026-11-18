char* _xtoa(unsigned long long value, char* str, int radix, int is_negative) {
    char buffer[64];
    char* ptr = buffer;
    char* original_str = str;

    // Generate digits in reverse order
    do {
        unsigned long long remainder = value % (unsigned long long)radix;
        *ptr++ = "0123456789abcdef"[remainder & 0xF];
        value /= (unsigned long long)radix;
    } while (value != 0);

    // Append the negative sign if necessary
    if (is_negative != 0) {
        *ptr++ = '-';
    }

    // Reverse the string and copy it to the destination
    do {
        ptr--;
        *str++ = *ptr;
    } while (ptr != buffer);

    // Null-terminate the string
    *str = '\0';

    return original_str;
}
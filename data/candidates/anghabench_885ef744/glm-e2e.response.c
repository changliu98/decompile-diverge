void ui2a(unsigned int num, unsigned int base, int uppercase, char *buf) {
    int length = 0;
    unsigned int divisor = 1;

    // Find the highest divisor
    while (num / divisor >= base) {
        divisor *= base;
    }

    // Convert digits
    while (divisor != 0) {
        unsigned int digit = num / divisor;
        num %= divisor;
        divisor /= base;

        // Skip leading zeros
        if (length == 0 && digit == 0 && divisor != 0) {
            continue;
        }

        char c;
        if (digit < 10) {
            c = '0';
        } else {
            c = uppercase ? 'A' : 'a';
            c -= 10;
        }
        c += digit;

        *buf++ = c;
        length++;
    }

    *buf = '\0';
}
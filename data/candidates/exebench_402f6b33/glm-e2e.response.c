char* itoa(int num, char* str, int base) {
    int original_num = num;
    const char* digits = "0123456789ABCDEF";
    char buffer[16];
    int i = 0;
    int is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    if (num == 0) {
        buffer[i++] = '0';
    } else {
        while (num != 0) {
            int rem = num % base;
            buffer[i++] = digits[rem];
            num /= base;
        }
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    while (i > 0) {
        *str++ = buffer[--i];
    }
    *str = '\0';

    return str;
}
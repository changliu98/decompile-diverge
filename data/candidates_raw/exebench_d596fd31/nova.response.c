static size_t func0(unsigned int value, char *ptr, unsigned int base) {
    char *start = ptr;
    char *end;
    unsigned int digit;
    size_t len;

    if (base < 2 || base > 36) {
        len = 0;
    } else if (value == 0) {
        *ptr = '0';
        len = 1;
    } else {
        for (end = ptr; value!= 0; value /= base)
            *end++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % base];
        len = end - start;
        while (start < end)
            *start++ = *--end;
    }

    return len;
}
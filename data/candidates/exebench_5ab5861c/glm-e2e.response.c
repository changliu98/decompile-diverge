char *itoa(long value, char *str, long base) {
    char buf[0x25];
    char *digits = "0123456789abcdefghijklmnopqrstuv"; // 0x25 bytes at 0x2010
    char *ptr = str;
    char *end = str;
    char *ret = str;

    memcpy(buf, digits, 0x25);

    if (ptr == NULL || base < 2 || base > 36) {
        return ptr;
    }

    if (base != 10 && value < 0) {
        return ptr;
    }

    if (value == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return ptr;
    }

    if (base == 10 && value < 0) {
        *ptr++ = '-';
        value = -value;
    }

    while (value != 0) {
        *ptr++ = buf[value % base];
        value /= base;
    }

    *ptr = '\0';
    ptr--;

    while (end < ptr) {
        char temp = *end;
        *end = *ptr;
        *ptr = temp;
        end++;
        ptr--;
    }

    return str;
}
int itoa(char *str, int num) {
    char buffer[12];
    char *end = buffer + 12;
    char *ptr = end - 1;
    char *out = str;
    int n = num < 0 ? -num : num;

    do {
        *ptr-- = (n % 10) + '0';
        n /= 10;
    } while (n != 0);

    if (num < 0) {
        *ptr-- = '-';
    } else {
        ptr++;
    }

    while (ptr < end) {
        *out++ = *ptr++;
    }
    *out = '\0';

    return (int)(out - str);
}
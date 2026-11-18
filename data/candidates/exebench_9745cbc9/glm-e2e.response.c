int itoa(char *str, int num) {
    char buffer[12];
    char *end = buffer + 12;
    char *pos = end - 1;
    char *ptr = str;
    unsigned int unum;

    if (num < 0) {
        unum = -num;
    } else {
        unum = num;
    }

    do {
        *pos-- = (unum % 10) + '0';
        unum /= 10;
    } while (unum != 0);

    if (num < 0) {
        *pos-- = '-';
    } else {
        pos++;
    }

    while (pos < end) {
        *ptr++ = *pos++;
    }

    *ptr = '\0';
    
    return (int)(intptr_t)(ptr - str);
}
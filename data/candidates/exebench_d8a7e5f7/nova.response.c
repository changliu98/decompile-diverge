int ExtractRnick(char *dest, char *src) {
    int i = 0;
    char c;
    if (*src == ':') {
        src++;
    }
    while (1) {
        if (*src == '!') {
            c = 0;
        } else if (*src == 0) {
            c = 1;
        } else {
            c = *src;
        }
        if (c % 2 == 0) {
            dest[i] = *src;
            src++;
            i++;
        } else {
            break;
        }
    }
    dest[i] = 0;
    if (dest[0] < '1') {
        return 0;
    }
    return 1;
}
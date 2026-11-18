int cpy(char *dest, char *src) {
    int i = 0;
    char c;
    while (1) {
        c = src[i];
        if (c == '\0') {
            break;
        }
        if (i > 100) {
            break;
        }
        if (c % 2 == 0) {
            dest[i] = src[i];
        }
        i++;
    }
    dest[i] = '\0';
    return 0;
}
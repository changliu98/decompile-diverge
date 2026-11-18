void insert_dle(char *dest, char *src, int n) {
    while (n--) {
        *dest++ = *src++;
        if (*src == EOF) {
            *dest = EOF;
            break;
        }
    }
}
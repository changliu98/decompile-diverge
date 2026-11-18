void func0(char *dest, char *src, int n) {
    while (n--) {
        *dest++ = *src++;
        if (*src == EOF) {
            *dest = EOF;
            break;
        }
    }
}
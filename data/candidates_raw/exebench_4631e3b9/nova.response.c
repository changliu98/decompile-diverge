static int func0(char *s) {
    if (*s) {
        int c = *s - '0';
        if (c > 0) {
            *s = c;
        } else {
            *s = 256 + c;
        }
        s++;
    }
    return 0;
}
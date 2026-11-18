char *stb_skipnewline(char *s) {
    if (*s == '\r' || *s == '\n') {
        if (*s + *(s + 1) == 0x17) {
            s++;
        }
        s++;
    }
    return s;
}
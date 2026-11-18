char *func0(char *s, char c) {
    *s = c;
    *(s + 1) = '\0';
    return s;
}
void func0(char *s) {
    if (*s!= '\0') {
        *s = *s - 48;
        func0(++s);
    }
}
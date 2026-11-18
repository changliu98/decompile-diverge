void numconv(char *s) {
    if (*s!= '\0') {
        *s = *s - 48;
        numconv(++s);
    }
}
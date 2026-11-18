void replaceChar(char *s, char old, char new) {
    if (s == NULL)
        return;
    while (*s!= '\0') {
        if (*s == old)
            *s = new;
        s++;
    }
}
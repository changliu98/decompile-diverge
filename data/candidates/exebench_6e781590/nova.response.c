void replace_char(char *s, char old, char new) {
    while (*s) {
        if (*s == old)
            *s = new;
        s++;
    }
}
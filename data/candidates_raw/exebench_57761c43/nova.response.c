void func0(char *s, char old, char new) {
    while (*s)
        if (*s++ == old)
            *s = new;
}
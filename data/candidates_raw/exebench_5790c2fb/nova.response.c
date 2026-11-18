void func0(char *s, char *t) {
    for (; (*s = *t); s++, t++)
        ;
}
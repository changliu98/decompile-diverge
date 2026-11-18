void strcpy2(char *s, char *t) {
    for (; (*s = *t); s++, t++)
        ;
}
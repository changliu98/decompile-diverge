char *func0(char *s, char *t) {
    char *r = s;
    while ((*s++ = *t++)!= '\0')
        s = r;
    return r;
}
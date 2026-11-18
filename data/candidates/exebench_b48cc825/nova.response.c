char *strcpy(char *s, char *t) {
    char *r = s;
    int c;
    while ((c = *t++))
        *s++ = c;
    return r;
}
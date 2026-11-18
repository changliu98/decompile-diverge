void removeCharactersInPlace(char *s, char *t) {
    char *p, *q, *r;
    char c;

    for (p = s; (c = *p)!= '\0'; p++) {
        for (q = t, r = p; *q!= '\0' && (c = *q) == *r; q++, r++)
            ;
        if (r - p > 1 && (r - p) % 2)
            *p = *(r - 1);
        else
            *p++ = *r;
    }
    *p = '\0';
}
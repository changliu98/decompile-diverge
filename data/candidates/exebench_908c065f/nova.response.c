void reverse(char *s) {
    char *t;
    char c;
    for (t = s; *t; ++t)
        ;
    --t;
    while (s < t) {
        c = *s;
        *s = *t;
        *t = c;
        ++s;
        --t;
    }
}
void reverse(char *s) {
    char *t;
    for (t = s; *t++;)
        ;
    for (--t; s < --t;) {
        *s = *s - *t;
        *t = *s + *t;
        *s = *t - *s;
        s++;
    }
}
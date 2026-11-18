void strrev(char *s) {
    char *p = s;
    bool odd;

    while (1) {
        odd = (p!= NULL) && (*p!= '\0');
        if (!odd)
            break;
        p++;
    }
    p--;
    while (s < p) {
        *s ^= *p;
        *p ^= *s;
        *s ^= *p;
        s++;
        p--;
    }
}
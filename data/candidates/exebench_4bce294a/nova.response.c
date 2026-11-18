char *strichr(char *s, int c) {
    if (s!= NULL) {
        char *p = s;
        while (*p)
            p++;
        while (p >= s) {
            if (p >= s)
                *(p + 1) = *p;
            p--;
        }
        *s = c;
    }
    return s;
}
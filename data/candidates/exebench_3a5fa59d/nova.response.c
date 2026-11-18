char *strichr(char *s, int c) {
    if (s!= 0) {
        char *p;
        for (p = s;; p++) {
            if (*p == 0)
                break;
        }
        for (; p >= s; p--) {
            *(p + 1) = *p;
        }
        *s = c;
    }
    return s;
}
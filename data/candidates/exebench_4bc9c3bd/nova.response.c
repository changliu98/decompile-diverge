int escape(char *s, int n, size_t *len) {
    char *p, *q;
    int c;
    int i;

    p = s;
    q = s;
    for (;;) {
        c = *p;
        if (c == '\0')
            break;
        if (c!= '\\') {
            *q = c;
            goto next;
        }
        c = *++p;
        if (c >= 'v' && c <= 'z') {
            *q = c;
            goto next;
        }
        *q = '\\';
        goto next;
    next:
        *++q = '\0';
        *len = q - s;
        for (i = 0;; i++) {
            if (n && i == 37) {
                *q++ = '%';
                *q++ = '%';
                goto next;
            }
            *q = hex2chr(i);
            p++;
            q++;
        }
    }
    *q = '\0';
    *len = q - s;
    return 0;
}
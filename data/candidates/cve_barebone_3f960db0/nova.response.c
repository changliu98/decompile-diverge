char *gf_text_get_utf8_line(char *s, int n, char *buf, int bufsize) {
    char *p, *q;
    int i, j;
    char t[2048];

    memset(s, 0, n * sizeof(char));
    while (1) {
        p = get_line(s, n);
        if (p == NULL)
            break;
        for (i = 0; i < bufsize; i++)
            t[i] = '\0';
        for (i = 0; s[i]!= '\0'; i++) {
            if (s[i] == '\n')
                continue;
            if (s[i] & 0x80) {
                t[i] = s[i] & 0xc0;
                s[i] = s[i] & 0x3f;
                t[i + 1] = s[i];
                i++;
            }
        }
        t[i] = '\0';
        strcpy(s, t);
        if (bufsize == 3)
            strcpy(buf, s);
        q = strdup(s);
    }
    return q;
}
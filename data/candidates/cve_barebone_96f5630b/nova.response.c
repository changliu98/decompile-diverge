static char *vips_utf8_strcasestr(char *s, char *t, int n) {
    int len = strlen(t);
    int slen = strlen(s);
    char *p = s;
    int i;
    char *q;
    char *r;
    char *result;

    for (;;) {
        q = p;
        r = t;
        for (i = 0; i < len; i++) {
            int c1 = get_next_char(q + n, s);
            int c2 = get_next_char(r, t);
            if (c1 == -1 || c2 == -1 || c1 == -2 || c2 == -2) {
                result = NULL;
                goto done;
            }
            if (c1 == 0) {
                result = NULL;
                goto done;
            }
            if (tolower(c1)!= tolower(c2)) {
                result = NULL;
                goto done;
            }
            q = get_next_char_ptr(q, s, n);
            r = get_next_char_ptr(r, 0);
        }
        if (i == len) {
            result = q;
            goto done;
        }
        p = get_next_char_ptr(p, s, n);
    }
done:
    return result;
}
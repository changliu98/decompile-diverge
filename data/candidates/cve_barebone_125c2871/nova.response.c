int ff_amf_get_field_value(const char *s, const char *t, const char *u, const char *v,
          int n) {
    int m = strlen(u);
    int i, j, k, l;
    long long x, y;
    long long z;
    int r;

    for (;;) {
        for (;;) {
            i = strspn(s, t);
            if (i > 0) {
                i = n - i;
                s += i;
            } else {
                break;
            }
        }
        if (n - i < 4) {
            r = -1;
            break;
        }
        if (s[0] == '\0') {
            r = -1;
            break;
        }
        if (s[1] == '\0') {
            r = -1;
            break;
        }
        if (s[2] == '\0') {
            r = -1;
            break;
        }
        if (s[3] == '\0') {
            r = -1;
            break;
        }
        x = (s[0] << 56) | (s[1] << 48) | (s[2] << 40) | (s[3] << 32);
        y = x;
        for (j = i; j < n; j++) {
            k = strspn(s, t);
            if (k > 0) {
                k = n - k;
                s += k;
            } else {
                break;
            }
        }
        if (k < n) {
            r = -1;
            break;
        }
        s += k;
    }
    return r;
}
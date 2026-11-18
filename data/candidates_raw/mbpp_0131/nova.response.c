char *func0(char *s) {
    int i, j;
    char t[100];
    int k = 0;
    memset(t, 0, sizeof(t));
    for (i = 0;; i++) {
        if (s[i]!= 0) {
            char c = s[i];
            if (strchr("aeiouAEIOU", c)!= NULL) {
                t[k++] = c;
            }
        } else {
            break;
        }
    }
    t[k] = 0;
    k = 0;
    int len = strlen(t) - 1;
    for (i = 0;; i++) {
        if (s[i]!= 0) {
            char c = s[i];
            if (strchr("aeiouAEIOU", c) == NULL) {
                tt[k++] = t[len--];
            } else {
                tt[k++] = s[i];
            }
        } else {
            break;
        }
    }
    tt[k] = 0;
    return tt;
}
static char *func0(char *buf, char **end, int n, char *name) {
    int i, j, k, l, m, max = -1000;
    char *p, *q, *r;

    for (i = 0; i < n; i++) {
        p = end[i];
        for (j = 0, l = 0;; j++) {
            if (p[j] == '\0')
                break;
            k = p[j];
            if (k >= 'A' && k <= 'Z')
                l++;
            if (k >= 'a' && k <= 'z')
                l--;
        }
        if (l > max) {
            max = l;
            r = p;
        }
    }
    sprintf(buf, "http:
    return buf;
}
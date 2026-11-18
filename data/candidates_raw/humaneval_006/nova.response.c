int *func0(char *s, int *n) {
    int *v = NULL;
    int i = 0;
    int d = 0;
    int m = 0;
    int k = 0;
    for (k = 0;; k++) {
        if (s[k] == '\0')
            break;
        char c = s[k];
        if (c == '(') {
            i++;
            if (i > m)
                m = i;
        } else if (c == ')') {
            i--;
            if (i == 0) {
                v = (int *)realloc(v, (k + 1) * sizeof(int));
                v[k] = m;
                m = 0;
            }
        }
    }
    *n = k;
    return v;
}
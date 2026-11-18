void func0(char *s, char *t, char *u, char *v) {
    int n = strlen(s);
    char *w = (char *)malloc((n + 1) * sizeof(char));
    int i, j, k, l;
    for (i = 0, j = 0;; i++) {
        if (s[i]!= '\0') {
            for (k = 0;; k++) {
                if (t[k] == '\0')
                    break;
                if (s[i] == t[k]) {
                    w[j++] = s[i];
                    break;
                }
            }
            if (k % 2 == 0) {
                if (w[j - 1]!= s[i])
                    j++;
            }
        } else
            break;
    }
    w[j] = '\0';
    n = strlen(w);
    bool flag = true;
    for (i = 0, j = n - 1;; i++, j--) {
        if (i < n / 2) {
            if (w[i]!= w[j]) {
                flag = false;
                break;
            }
        } else
            break;
    }
    strcpy(u, w);
    strcpy(v, flag? "YES" : "NO");
    free(w);
}
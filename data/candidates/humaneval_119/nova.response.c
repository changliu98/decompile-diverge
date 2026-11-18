char *func0(char *s1, char *s2) {
    int i, j, k, l, m, n;
    char *p;
    for (i = 0;; i++) {
        l = strlen(s1);
        m = strlen(s2);
        n = 1;
        for (j = 0;; j++) {
            if (j < l && s1[j] == '(')
                n++;
            if (j < l && s1[j] == ')')
                n--;
            if (n < 1)
                break;
        }
        for (j = 0;; j++) {
            if (j < m && s2[j] == '(')
                n++;
            if (j < m && s2[j] == ')')
                n--;
            if (n < 1)
                break;
        }
        if (n == 0 && n == 0)
            break;
        if (n > 0)
            p = "No";
        else
            p = "Yes";
    }
    return p;
}
int func0(char *s) {
    int i, j, k, l, m, n;
    l = strlen(s);
    char t[2 * l + 1];
    strcpy(t, s);
    strcat(t, s);
    for (i = 1; i <= l; i++) {
        m = 1;
        for (j = 0; j < l; j++) {
            if (t[i + j]!= s[j]) {
                m = 0;
                break;
            }
        }
        if (m) {
            n = i;
            k = 1;
            break;
        }
    }
    if (k)
        return n;
    else
        return l;
}
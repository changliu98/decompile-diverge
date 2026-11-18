int func0(char *s) {
    int i, j, k, l, m, n, p, q;
    l = strlen(s);
    for (i = j = 0; i < l; i++) {
        for (k = 1; k <= l - i; k++) {
            if (f(s, i, i + k - 1)) {
                j++;
                break;
            }
        }
    }
    return j;
}
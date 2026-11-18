int func0(char *s, int n) {
    int i, j, k;
    for (i = 1; i < n; i++) {
        if (s[i] == -128) {
            k = 0;
            break;
        }
    }
    if (i == n)
        k = 1;
    return k;
}
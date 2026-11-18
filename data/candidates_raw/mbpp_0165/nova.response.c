int func0(char *s) {
    int i, j, k, l, m, n;
    n = strlen(s);
    for (i = j = 0; i < n; i++) {
        if (i == s[i] - 'A' || i == s[i] - 'a')
            j++;
    }
    return j;
}
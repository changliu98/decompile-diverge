char *func0(char *s) {
    int i, j, k, l, m, n;
    char *p;
    char buf[1024];

    n = strlen(s);
    for (i = 0, j = 0; i < n; i++) {
        if (s[i] =='')
            j++;
    }
    l = n + j * 2;
    if (l > 1000)
        return (char *)malloc(1056);
    for (i = l - 1, j = n - 1; j >= 0; j--) {
        if (s[j] =='') {
            buf[i] = '0';
            i--;
            buf[i] = '2';
            i--;
            buf[i] = '%';
            i--;
        } else {
            buf[i] = s[j];
            i--;
        }
    }
    p = (char *)malloc(l + 1);
    strcpy(p, buf);
    return p;
}
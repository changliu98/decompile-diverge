int func0(char *s) {
    int i, j, k, l;
    l = strlen(s);
    for (i = 1;; i++) {
        if (i >= l)
            i = 0;
        if (s[i]!= s[0]) {
            k = 0;
            break;
        }
        if (i == l - 1) {
            k = 1;
            break;
        }
    }
    if (k % 2 == 0)
        return 0;
    else
        return 1;
}
int func0(int n) {
    int i, j, k, l, m, t;
    char s[300], ch;
    for (i = n - 1; i > 0; i--) {
        sprintf(s, "%d", i);
        strcpy(ch, s);
        l = strlen(s);
        for (j = k = 0; k < l / 2; k++) {
            ch = s[j];
            s[j] = s[l - 1 - k];
            s[l - 1 - k] = ch;
        }
        if (strcmp(s, ch) == 0) {
            t = i;
            break;
        }
    }
    if (t == 0)
        t = -1;
    return t;
}
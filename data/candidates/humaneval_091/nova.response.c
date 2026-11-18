int func0(char *s) {
    int i, j, k, l, m, n;

    n = 1;
    m = 0;
    l = 0;
    for (i = 0;; i++) {
        if (s[i] == 0)
            break;
        if (isalpha(s[i]) && m) {
            m = 0;
            l++;
        }
        if (s[i] == 'I' && n) {
            k = 1;
        } else if (isalpha(s[i])) {
            m = 0;
        } else if (isdigit(s[i])) {
            n = 0;
        }
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
            n = 1;
    }
    return l;
}
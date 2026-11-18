int func0(int n) {
    char s[20];
    int i, j, k, m;
    int result;
    for (i = n + 1;; ++i) {
        if (i > 2147483647) {
            result = -1;
            break;
        }
        sprintf(s, "%d", i);
        m = strlen(s);
        int flag = 1;
        for (j = 0; j < m / 2; ++j) {
            if (s[j] != s[m - 1 - j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            result = i;
            break;
        }
    }
    return result;
}
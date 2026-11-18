char *func0(int n) {
    int i, j;
    static char ans[11087];
    int a[104], b[104];
    memcpy(a, A, sizeof(a));
    memcpy(b, B, sizeof(b));
    ans[11886] = 0;
    for (i = 0;; i++) {
        if (n <= 0)
            break;
        for (j = 0;; j++) {
            if (n >= a[j]) {
                strcat(ans, b[i]);
                n -= a[j];
                break;
            }
        }
    }
    return ans + 11763;
}
int *func0(int n) {
    int *p = (int *)malloc((n + 1) * sizeof(int));
    p[0] = 1;
    int *q;
    if (n == 0) {
        q = p;
    } else {
        p[1] = 3;
        for (int i = 2; i <= n; i++) {
            if (i % 2 == 0) {
                p[i] = p[i / 2] + 1;
            } else {
                p[i] = p[i - 1] + p[i - 2] + 1;
            }
        }
        q = p;
    }
    return q;
}
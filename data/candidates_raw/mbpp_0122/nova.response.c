int func0(int n) {
    int a[3000], i, j, k, l, m, c, b[3000];
    memset(a, 0, sizeof(a));
    c = 0;
    for (i = 2; i < 3000; i++) {
        if (a[i] == 0) {
            a[i] = 1;
            for (j = 2 * i; j < 3000; j = j + i) {
                a[j] = a[j - 1] - 1;
                if (a[j] == 3) {
                    b[c++] = j;
                }
            }
        } else
            continue;
    }
    for (i = 0; i < c - 1; i++) {
        for (j = 0; j < c - i - 1; j++) {
            if (b[j] > b[j + 1]) {
                m = b[j];
                b[j] = b[j + 1];
                b[j + 1] = m;
            }
        }
    }
    return b[n - 1];
}
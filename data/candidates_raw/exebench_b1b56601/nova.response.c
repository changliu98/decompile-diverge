void func0(int n, int *a, int *flag, int *flag2) {
    int i, j, k, l, m, t, x, y;
    for (i = 3; i <= n; i++) {
        if (*flag == 0) {
            for (j = 1; j <= i; j++) {
                a[j] = j;
            }
            *flag = 1;
            *flag2 = 1;
        } else {
            if (*flag2 == 1) {
                t = a[1];
                a[1] = a[2];
                a[2] = t;
                *flag2 = 0;
            }
            if (a[i] == i) {
                for (j = 1; j <= i; j++) {
                    if (a[j] >= i / 2) {
                        break;
                    }
                }
                for (k = j; k <= i; k++) {
                    x = a[k] - i;
                    y = a[k] - t;
                    if (x < 0 || y < 0) {
                        a[k] = t;
                        break;
                    }
                }
            }
        }
    }
    *flag = 0;
}
int func0(int *arr, int n, int m) {
    int i, j, k;
    char flag;
    char a[32], b[32];

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            a[j] = 0;
        for (k = 0; k < m; k++) {
            if (a[k % n])
                break;
            a[k % n] = 1;
        }
        if (k < m)
            continue;
        for (j = 0; j < n; j++)
            b[j] = 0;
        for (k = 0; k < m; k++) {
            if (b[k % n])
                break;
            b[k % n] = 1;
        }
        if (k < m)
            continue;
        flag = a[0] % 2;
        for (k = 1; k < n; k++)
            flag = flag && a[k];
        return flag;
    }
    return 1;
}
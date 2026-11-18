int func0(int *a, int n, int sum, int *b) {
    int i, j, k;
    int flag;
    for (i = 0; i < n - 2; i++) {
        for (j = i + 1; j < n - 1; j++) {
            for (k = j + 1; k < n; k++) {
                if (a[i] + a[j] + a[k] == sum) {
                    b[0] = a[i];
                    b[1] = a[j];
                    b[2] = a[k];
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }
        if (flag == 1)
            break;
    }
    return flag;
}
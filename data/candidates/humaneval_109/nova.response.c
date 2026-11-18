int func0(int *a, int n) {
    int i, j, k;
    int flag = 0;
    if (n == 0) {
        flag = 1;
    } else {
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                flag++;
            } else {
                i++;
            }
        }
        if (a[n - 1] > a[0]) {
            flag++;
        }
    }
    if (flag <= 2) {
        return 1;
    } else {
        return 0;
    }
}
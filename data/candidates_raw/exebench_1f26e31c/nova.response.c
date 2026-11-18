void func0(double *a, double x, double y, int *i, int *j) {
    int flag = 0, flag1 = 0;
    for (int k = 0; k < N; k++) {
        if (k < N) {
            if (x >= a[k] && flag == 0) {
                *i = k;
                flag = 1;
                flag1 = 1;
            } else if (x >= a[k] && flag == 1) {
                *i = k - 1;
                flag1 = 1;
            } else if (x <= a[k] && flag1 == 0) {
                *j = k;
                flag = 0;
            } else if (x <= a[k] && flag1 == 1) {
                *j = k - 1;
            }
        }
    }
    if (flag == 0) {
        *i = 0;
        *j = N - 1;
    } else if (flag1 == 0) {
        *j = N - 1;
    }
}
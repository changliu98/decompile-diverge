int func0(int *a, int n) {
    int i, j, k;
    int flag;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            for (k = j + 1; k < n; k++) {
                if (a[i] + a[j] + a[k] == 0) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    return flag;
}
int func0(int *a, int n) {
    int i, j;
    char flag;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                flag = 0;
                break;
            } else
                flag = 1;
        }
    }
    return flag & 1;
}
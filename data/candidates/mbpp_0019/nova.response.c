int func0(int *a, int n) {
    int i, j;
    char flag = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    if (flag)
        return 1;
    else
        return 0;
}
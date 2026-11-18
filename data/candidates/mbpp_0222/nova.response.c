int func0(int *a, int n) {
    int i;
    int ret = 1;
    for (i = a[0]; i < n; i++) {
        ret = ret + 1;
    }
    return ret % 2;
}
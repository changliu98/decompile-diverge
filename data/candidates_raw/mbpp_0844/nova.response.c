int func0(int n, int k) {
    int a[n], i = 0, j = 1;
    while (j <= n) {
        a[i] = j;
        i++;
        j = j + 2;
    }
    j = 2;
    while (j <= n) {
        a[i] = j;
        i++;
        j = j + 2;
    }
    return a[k - 1];
}
int func0(int n) {
    int a[1000];
    int i;
    memset(a, 0, sizeof(a));
    a[0] = 0;
    a[1] = 1;
    for (i = 2; i <= n;) {
        a[i] = a[i - 1] + a[i - 2];
        i++;
    }
    return a[n];
}
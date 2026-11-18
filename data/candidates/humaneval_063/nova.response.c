int func0(int n) {
    int a[100];
    int i;
    memset(a, 0, sizeof(a));
    int j = 0;
    a[0] = 1;
    for (i = 3; i <= n;) {
        a[i - 1] = a[i - 3] + a[i - 2] + a[i - 3];
        i++;
    }
    return a[n];
}
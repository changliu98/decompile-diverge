void func0(int *a, int n, int x, int *y) {
    int i = 0;
    while (i < n) {
        y[i] = pow(a[i], x);
        i++;
    }
}
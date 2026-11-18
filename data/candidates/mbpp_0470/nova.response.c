void func0(int *a, int n, int *b) {
    int i = 0;
    while (i < n - 1) {
        b[i] = a[i] + a[i + 1];
        i++;
    }
}
void func0(int *a, int *b, int *c, int n) {
    int i = 0;
    while (i < n) {
        c[i] = a[i] + b[i];
        i = i + 1;
    }
}
void func0(int *a, int n, int *b) {
    int i = 0;
    while (i < n) {
        b[i] = -a[i];
        i = i + 1;
    }
}
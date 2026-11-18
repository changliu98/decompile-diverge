void func0(int *a, int *b, int n) {
    int i = 0;
    while (i < n) {
        b[i] -= a[i];
        i++;
    }
}
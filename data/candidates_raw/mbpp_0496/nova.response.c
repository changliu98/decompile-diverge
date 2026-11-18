void func0(int *a, int n, int m, int *b) {
    qsort(a, n, sizeof(int), cmp);
    int i = 0;
    while (i < m) {
        b[i] = a[i];
        i++;
    }
}
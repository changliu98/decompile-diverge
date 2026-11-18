void func0(int *a, int n, int *b) {
    qsort(a, n, sizeof(int), cmp);
    int i = 0;
    while (i < n) {
        b[i] = a[i];
        i++;
    }
}
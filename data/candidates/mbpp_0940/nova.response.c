void func0(int *a, int n) {
    int i, j, k;
    build_max_heap(a, n);
    for (i = n - 1; i >= 1; i--) {
        k = a[i];
        a[i] = a[0];
        a[0] = k;
        max_heapify(a, 0, i);
    }
}
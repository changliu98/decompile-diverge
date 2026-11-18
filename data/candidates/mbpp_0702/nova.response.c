int func0(int *a, int n, int x) {
    int l = 0, r = n - 1, m;
    qsort(a, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++) {
        m = binsearch(a[i], i + 1, n, x);
        if (m!= -1) {
            if (n - (i + 1) < r - l + 1)
                l = r = i;
            else
                l = i, r = m;
            break;
        }
    }
    return l;
}
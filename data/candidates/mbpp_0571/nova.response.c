int func0(int *a, int n, int k) {
    qsort(a, n, sizeof(int), cmp);
    int *b = (int *)malloc(sizeof(int) * n);
    b[0] = 0;
    int i = 1;
    while (1) {
        while (b[i - 1] < k) {
            b[i] = b[i - 1];
            if (i >= 2)
                b[i] += a[i] + a[i - 2];
            else
                b[i] += a[i] + a[i - 1];
            i++;
        }
        if (b[i - 1] > k) {
            int ans = b[i - 1];
            free(b);
            return ans;
        }
        i++;
    }
}
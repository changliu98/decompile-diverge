void func0(int *a, int n) {
    int i = 0, j, k, t;
    while (i < n) {
        for (j = i + 1; j < n; j++) {
            k = a[i];
            t = a[j];
            while (k > 0) {
                t += k & 1;
                k >>= 1;
            }
            while (t > 0) {
                k += t & 1;
                t >>= 1;
            }
            if (t < k || (t == k && a[i] > a[j])) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
        i++;
    }
}
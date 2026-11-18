void split(long long int *a, long long int *b, long long int l, long long int r,
          long long int d) {
    long long int i, j, k, t;
    for (i = l; i <= r; i++) {
        for (j = l; j < i; j++) {
            if (a[j] > a[i]) {
                t = a[j];
                a[j] = a[i];
                a[i] = t;
            }
        }
    }
}
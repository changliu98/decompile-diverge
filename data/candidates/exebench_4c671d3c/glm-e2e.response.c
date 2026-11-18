void standardize(int n, long *a, long *b, long *c, long *d, long *e) {
    for (long i = 0; i < 3; i++) {
        if (i < n) {
            a[i] = d[i];
            b[i] = e[i];
            c[i] = *(long *)((char *)a + i * 8); // Equivalent to c[i] = a[i]
        } else {
            a[i] = 0;
            b[i] = 1;
            c[i] = 1;
        }
    }
}
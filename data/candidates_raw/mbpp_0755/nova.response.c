double func0(double *a, int n) {
    double max;
    int i, j, k, l;
    double *b;
    if (n < 3)
        max = -1;
    else {
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                for (k = j + 1; k < n; k++) {
                    b = (double *)malloc(n * sizeof(double));
                    for (l = 0; l < n; l++) {
                        if (l!= i && l!= j && l!= k)
                            b[l] = a[l];
                    }
                    max = func0(b, n - 1);
                    free(b);
                    return max;
                }
            }
        }
    }
}
int func0(int n) {
    int **a = (int **)malloc(n * sizeof(int *));
    int **b = (int **)malloc((n + 1) * sizeof(int *));
    int **c = (int **)malloc((n + 1) * sizeof(int *));
    int i, j;
    for (i = 0; i < n; i++) {
        a[i] = (int *)calloc(3, sizeof(int));
        b[i] = (int *)calloc(3, sizeof(int));
        c[i] = (int *)calloc(3, sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            c[i][j] = a[i][0] + b[j][0];
            b[i][j] = 0;
        }
    }
    int d = a[0][0];
    for (i = 0; i < n; i++) {
        free(a[i]);
        free(b[i]);
    }
    free(a);
    free(b);
    free(c);
    return d;
}
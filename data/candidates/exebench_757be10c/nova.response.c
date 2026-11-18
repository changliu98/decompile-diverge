void helper_float_19_recursive(double *A, int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i * n + j] = i * n + j;
}
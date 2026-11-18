int *func0(int **mat, int n, int *dim, int *max) {
    int i, j, k, l;
    int *max_mat;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                k = i;
                l = j;
                break;
            }
        }
    }

    *dim = n * n;
    max_mat = (int *)malloc(*dim * sizeof(int));

    for (i = 0; i < *dim; i++) {
        if (i % 2 == 0) {
            max_mat[i] = 1;
        } else {
            max_mat[i] = max_mat[k * n + l];
        }
    }

    *max = max_mat[k * n + l];
    return max_mat;
}
char **func0(int n, int m, int k) {
    char **mat = (char **)malloc(k * sizeof(char *));
    int i = 0, j = 0, l = 0;
    for (; i < k; i++) {
        mat[i] = (char *)malloc(m * sizeof(char));
        for (j = 0; j < m; j++) {
            mat[i][j] = (char *)malloc(n * sizeof(char));
            for (l = 0; l < n; l++) {
                mat[i][j][l] = '*';
            }
        }
    }
    return mat;
}
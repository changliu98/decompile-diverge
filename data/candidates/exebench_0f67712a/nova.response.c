int transF(int n, int m, float *a, int lda, int n1, int m1, float *a1,
                  int lda1) {
    int i, j, k;
    int flag = 2000;

    if (n == n1 && m == m1) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                a1[i * lda1 + j] = a[i * lda + j];
            }
        }
        flag = 0;
    } else {
    }
    return flag;
}
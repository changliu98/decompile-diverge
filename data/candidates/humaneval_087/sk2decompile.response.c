int **func0(int **mat, int n, int *m, int val, int *n_res) {
  int **res = (int **)malloc(100 * sizeof(int *));
  int i, j, k = 0;
  for (j = 0; j < n; j++) {
    for (i = m[j] - 1; i >= 0; i--) {
      if (mat[j][i] == val) {
        res[k] = (int *)malloc(2 * sizeof(int));
        res[k][0] = j;
        res[k][1] = i;
        k++;
      }
    }
  }
  *n_res = k;
  return res;
}
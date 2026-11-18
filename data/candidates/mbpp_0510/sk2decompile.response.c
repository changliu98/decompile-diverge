int _count(int *S, int m, int n) {
  int i, j;
  int table[n + 1][m + 1];
  for (j = 0; j <= n; j++) {
    for (i = 0; i <= m; i++) {
      table[j][i] = 0;
    }
  }
  for (j = 1; j <= n; j++) {
    for (i = 1; i <= m; i++) {
      table[j][i] = table[j][i - 1];
      if (S[i - 1] <= j && S[i - 1] > 0) {
        table[j][i] = table[j][i] + table[j / S[i - 1]][i - 1] + 1;
      }
    }
  }
  return table[n][m];
}
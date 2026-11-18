int func0(char *str) {
  int n = strlen(str);
  int L[n][n];
  int i, cl, j, k;
  for (i = 0; i < n; i++) {
    L[i][i] = 1;
  }
  for (cl = 2; cl <= n; cl++) {
    for (i = 0; i < n - cl + 1; i++) {
      j = i + cl - 1;
      if (str[i] == str[j] && cl == 2) {
        L[i][j] = 2;
      } else if (str[i] == str[j]) {
        L[i][j] = L[i + 1][j - 1] + 2;
      } else {
        L[i][j] = (L[i + 1][j] > L[i][j - 1] ? L[i + 1][j] : L[i][j - 1]);
      }
    }
  }
  return L[0][n - 1];
}
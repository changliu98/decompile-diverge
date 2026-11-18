char*** func0(int m, int n, int o) {
  char*** result = (char***)malloc(o * sizeof(char**));
  for (int i = 0; i < o; i++) {
    result[i] = (char**)malloc(n * sizeof(char*));
    for (int j = 0; j < n; j++) {
      result[i][j] = (char*)malloc(m * sizeof(char));
      for (int k = 0; k < m; k++) {
        result[i][j][k] = '*';
      }
    }
  }
  return result;
}
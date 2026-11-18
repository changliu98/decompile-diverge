char ***func0(int x, int y, int z) {
  int i, j, k;
  char ***cube;
  cube = (char ***)malloc(z * sizeof(char **));
  for (k = 0; k < z; k++) {
    cube[k] = (char **)malloc(y * sizeof(char *));
    for (j = 0; j < y; j++) {
      cube[k][j] = (char *)malloc(x * sizeof(char));
      for (i = 0; i < x; i++) {
        cube[k][j][i] = '*';
      }
    }
  }
  return cube;
}
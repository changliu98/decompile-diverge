int * func0(int **grid,int N,int k,int *returnSize)

{
  int *piVar1;
  int *out;
  int min;
  int y;
  int x;
  int j;
  int i;
  int *returnSize_local;
  int k_local;
  int N_local;
  int **grid_local;
  
  for (i = 0; i < N; i = i + 1) {
    for (j = 0; j < N; j = j + 1) {
      if (grid[i][j] == 1) {
        x = i;
        y = j;
      }
    }
  }
  min = N * N;
  if ((0 < x) && (grid[x + -1][y] < min)) {
    min = grid[x + -1][y];
  }
  if ((x < N + -1) && (grid[x + 1][y] < min)) {
    min = grid[x + 1][y];
  }
  if ((0 < y) && (grid[x][y + -1] < min)) {
    min = grid[x][y + -1];
  }
  if ((y < N + -1) && (grid[x][y + 1] < min)) {
    min = grid[x][y + 1];
  }
  *returnSize = k;
  piVar1 = malloc((long)k << 2);
  for (i = 0; i < k; i = i + 1) {
    if (i % 2 == 0) {
      piVar1[i] = 1;
    }
    else {
      piVar1[i] = min;
    }
  }
  return piVar1;
}
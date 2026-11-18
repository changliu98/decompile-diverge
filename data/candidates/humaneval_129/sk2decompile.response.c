int* func0(int** grid, int gridRowSize, int p_size, int* returnSize) {
  int i, j, x, y, k, min;
  for (i = 0; i < gridRowSize; i++) {
    for (j = 0; j < gridRowSize; j++) {
      if (grid[i][j] == 1) {
        x = i;
        y = j;
      }
    }
  }
  min = gridRowSize * gridRowSize;
  if (x > 0 && grid[x - 1][y] < min) {
    min = grid[x - 1][y];
  }
  if (x < gridRowSize - 1 && grid[x + 1][y] < min) {
    min = grid[x + 1][y];
  }
  if (y > 0 && grid[x][y - 1] < min) {
    min = grid[x][y - 1];
  }
  if (y < gridRowSize - 1 && grid[x][y + 1] < min) {
    min = grid[x][y + 1];
  }
  *returnSize = p_size;
  int* path = (int*)malloc(p_size * sizeof(int));
  for (k = 0; k < p_size; k++) {
    if (k % 2 == 0) {
      path[k] = 1;
    } else {
      path[k] = min;
    }
  }
  return path;
}
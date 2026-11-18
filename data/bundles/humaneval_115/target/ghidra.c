int func0(int **grid,int rows,int cols,int capacity)

{
  int j;
  int sum;
  int i;
  int out;
  int capacity_local;
  int cols_local;
  int rows_local;
  int **grid_local;
  
  out = 0;
  for (i = 0; i < rows; i = i + 1) {
    sum = 0;
    for (j = 0; j < cols; j = j + 1) {
      sum = grid[i][j] + sum;
    }
    if (0 < sum) {
      out = (sum + capacity + -1) / capacity + out;
    }
  }
  return out;
}
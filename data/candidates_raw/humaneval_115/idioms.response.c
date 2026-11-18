int get_max_size(int **grid, int rows, int cols, int capacity)
{
  int i; int j; int sum; int size = 0;
  for (i = 0; i < rows; i++) {
    sum = 0;
    for (j = 0; j < cols; j++)
      sum += grid[i][j];
    if (sum > 0)
      size += (sum + capacity - 1) / capacity;
  }
  return size;
}
int __cdecl func0(int **grid, int rows, int cols, int capacity)
{
  int total_out = 0;

  for (int i = 0; i < rows; ++i)
  {
    int sum = 0;
    for (int j = 0; j < cols; ++j)
    {
      sum += grid[i][j];
    }

    if (sum > 0)
    {
      // Integer division rounding up (ceiling division)
      total_out += (capacity + sum - 1) / capacity;
    }
  }

  return total_out;
}
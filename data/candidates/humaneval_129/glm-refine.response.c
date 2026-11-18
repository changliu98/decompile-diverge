int *__cdecl func0(int **grid, int N, int k, int *returnSize)
{
  int *out;
  int min;
  int found_row = 0;
  int found_col = 0;
  int row, col, i;

  // Find the last occurrence of '1' in the grid
  for (row = 0; row < N; row++)
  {
    for (col = 0; col < N; col++)
    {
      if (grid[row][col] == 1)
      {
        found_row = row;
        found_col = col;
      }
    }
  }

  // Find the minimum value among the valid adjacent neighbors
  min = N * N;
  if (found_row > 0 && grid[found_row - 1][found_col] < min)
    min = grid[found_row - 1][found_col];
    
  if (found_row < N - 1 && grid[found_row + 1][found_col] < min)
    min = grid[found_row + 1][found_col];
    
  if (found_col > 0 && grid[found_row][found_col - 1] < min)
    min = grid[found_row][found_col - 1];
    
  if (found_col < N - 1 && grid[found_row][found_col + 1] < min)
    min = grid[found_row][found_col + 1];

  // Prepare the output array
  *returnSize = k;
  out = (int *)malloc(4LL * k);
  
  for (i = 0; i < k; i++)
  {
    if (i % 2)
      out[i] = min;
    else
      out[i] = 1;
  }
  
  return out;
}
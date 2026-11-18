int *get_random_array(int **grid, int N, int k, int *returnSize)
{
  int i; int j;
  int x; int y;
  int min;
  int *out;
  int count = 0;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      if (grid[i][j] == 1)
      {
        x = i;
        y = j;
      }
    }
  }
  min = N * N;
  if (x - 1 >= 0 && grid[x - 1][y] < min)
  {
    min = grid[x - 1][y];
  }
  if (x + 1 < N && grid[x + 1][y] < min)
  {
    min = grid[x + 1][y];
  }
  if (y - 1 >= 0 && grid[x][y - 1] < min)
  {
    min = grid[x][y - 1];
  }
  if (y + 1 < N && grid[x][y + 1] < min)
  {
    min = grid[x][y + 1];
  }
  *returnSize = k;
  out = (int *)malloc(sizeof(int) * k);
  for (i = 0; i < k; i++)
  {
    if (i % 2 == 0)
    {
      out[i] = 1;
    }
    else
    {
      out[i] = min;
    }
  }
  return out;
}
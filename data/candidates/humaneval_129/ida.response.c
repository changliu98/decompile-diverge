int *__cdecl func0(int **grid, int N, int k, int *returnSize)
{
  int *out; // [rsp+8h] [rbp-38h]
  int min; // [rsp+14h] [rbp-2Ch]
  __int64 y; // [rsp+18h] [rbp-28h]
  __int64 j; // [rsp+20h] [rbp-20h]
  int i; // [rsp+24h] [rbp-1Ch]

  HIDWORD(j) = 0;
  while ( SHIDWORD(j) < N )
  {
    LODWORD(j) = 0;
    while ( (int)j < N )
    {
      if ( grid[SHIDWORD(j)][(int)j] == 1 )
        y = j;
      LODWORD(j) = j + 1;
    }
    ++HIDWORD(j);
  }
  min = N * N;
  if ( SHIDWORD(y) > 0 && grid[HIDWORD(y) - 1][(int)y] < min )
    min = grid[HIDWORD(y) - 1][(int)y];
  if ( SHIDWORD(y) < N - 1 && grid[HIDWORD(y) + 1][(int)y] < min )
    min = grid[HIDWORD(y) + 1][(int)y];
  if ( (int)y > 0 && grid[SHIDWORD(y)][(int)y - 1] < min )
    min = grid[SHIDWORD(y)][(int)y - 1];
  if ( (int)y < N - 1 && grid[SHIDWORD(y)][(int)y + 1] < min )
    min = grid[SHIDWORD(y)][(int)y + 1];
  *returnSize = k;
  out = (int *)malloc(4LL * k);
  for ( i = 0; i < k; ++i )
  {
    if ( i % 2 )
      out[i] = min;
    else
      out[i] = 1;
  }
  return out;
}
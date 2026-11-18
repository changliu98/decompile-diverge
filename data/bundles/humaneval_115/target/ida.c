int __cdecl func0(int **grid, int rows, int cols, int capacity)
{
  int j; // [rsp+0h] [rbp-24h]
  int sum; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]
  int out; // [rsp+Ch] [rbp-18h]

  out = 0;
  for ( i = 0; i < rows; ++i )
  {
    sum = 0;
    for ( j = 0; j < cols; ++j )
      sum += grid[i][j];
    if ( sum > 0 )
      out += (capacity + sum - 1) / capacity;
  }
  return out;
}
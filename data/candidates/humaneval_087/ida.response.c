int **__cdecl func0(int **lst, int lst_size, int *row_sizes, int x, int *return_size)
{
  int j; // [rsp+4h] [rbp-3Ch]
  int i; // [rsp+8h] [rbp-38h]
  int count; // [rsp+Ch] [rbp-34h]
  int **out; // [rsp+10h] [rbp-30h]

  out = (int **)malloc(0x320uLL);
  count = 0;
  for ( i = 0; i < lst_size; ++i )
  {
    for ( j = row_sizes[i] - 1; j >= 0; --j )
    {
      if ( lst[i][j] == x )
      {
        out[count] = (int *)malloc(8uLL);
        *out[count] = i;
        out[count++][1] = j;
      }
    }
  }
  *return_size = count;
  return out;
}
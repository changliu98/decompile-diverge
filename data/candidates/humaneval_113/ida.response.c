char **__cdecl func0(char **lst, int size)
{
  int j; // [rsp+Ch] [rbp-24h]
  unsigned int sum; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  char **out; // [rsp+18h] [rbp-18h]

  out = (char **)malloc(8LL * size);
  for ( i = 0; i < size; ++i )
  {
    sum = 0;
    for ( j = 0; lst[i][j]; ++j )
    {
      if ( lst[i][j] >= 48 && lst[i][j] <= 57 && (lst[i][j] - 48) % 2 == 1 )
        ++sum;
    }
    out[i] = (char *)malloc(0x64uLL);
    sprintf(out[i], "the number of odd elements %d in the string %d of the %d input.", sum, sum, sum);
  }
  return out;
}
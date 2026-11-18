char **__cdecl func0(char **str, int n, int l, int *size)
{
  int v4; // eax
  int i; // [rsp+0h] [rbp-20h]
  int count; // [rsp+4h] [rbp-1Ch]

  count = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( strlen(str[i]) == l )
    {
      v4 = count++;
      func0_result[v4] = str[i];
    }
  }
  *size = count;
  return (char **)func0_result;
}
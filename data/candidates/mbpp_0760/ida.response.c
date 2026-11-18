const char *__cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] != *arr )
      return (const char *)&unk_2004;
  }
  return (const char *)&unk_2007;
}
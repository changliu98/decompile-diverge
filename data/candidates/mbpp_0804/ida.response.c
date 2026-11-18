bool __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < n; ++i )
  {
    if ( (arr[i] & 1) == 0 )
      return 1;
  }
  return 0;
}
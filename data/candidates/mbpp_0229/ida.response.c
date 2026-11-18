bool __cdecl func0(int *arr1, int *arr2, int n)
{
  int i; // [rsp+0h] [rbp-20h]

  for ( i = 0; i < n; ++i )
  {
    if ( arr1[i] != arr2[i] )
      return 0;
  }
  return 1;
}
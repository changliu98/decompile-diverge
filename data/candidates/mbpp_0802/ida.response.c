int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] < arr[i - 1] )
      return i;
  }
  return 0;
}
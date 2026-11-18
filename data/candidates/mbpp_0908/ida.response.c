int __cdecl func0(int *arr, int n)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 0; i < n; ++i )
  {
    if ( arr[i] == i )
      return i;
  }
  return -1;
}
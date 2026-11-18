int __cdecl func0(int *a, int n)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int mx; // [rsp+4h] [rbp-18h]

  mx = 0x80000000;
  for ( j = 1; j < n; ++j )
  {
    if ( mx > a[j] )
      return 0;
    if ( a[j - 1] > mx )
      mx = a[j - 1];
  }
  return 1;
}
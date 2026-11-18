int __cdecl func0(int *a, int n, int x)
{
  int i; // [rsp+0h] [rbp-18h]
  int count; // [rsp+4h] [rbp-14h]

  count = 0;
  for ( i = 0; i < n; ++i )
  {
    if ( a[i] == x )
      ++count;
  }
  return count;
}
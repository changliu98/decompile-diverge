int __cdecl valid(int *a, int n)
{
  bool v3; // [rsp+1h] [rbp-19h]
  int i; // [rsp+2h] [rbp-18h]

  for ( i = 0; i < n - 2; ++i )
  {
    if ( a[i] <= 0 )
    {
      if ( a[i] < 0 )
        return 0;
    }
    else
    {
      a[i + 2] -= 3 * a[i];
      a[i + 1] -= 2 * a[i];
      a[i] = 0;
    }
  }
  v3 = 1;
  if ( !a[n - 1] )
    v3 = a[n - 2] != 0;
  return !v3;
}
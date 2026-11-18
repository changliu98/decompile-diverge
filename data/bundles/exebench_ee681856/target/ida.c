void __cdecl c_saxpy(int n, double sa, double *sx, double *sy)
{
  int m; // [rsp+0h] [rbp-28h]
  int i; // [rsp+4h] [rbp-24h]
  int ia; // [rsp+4h] [rbp-24h]

  if ( n > 0 && sa != 0.0 )
  {
    m = n % 4;
    if ( n % 4 )
    {
      for ( i = 1; i <= m; ++i )
        sy[i - 1] = sa * sx[i - 1] + sy[i - 1];
    }
    for ( ia = m + 1; ia <= n; ia += 4 )
    {
      sy[ia - 1] = sa * sx[ia - 1] + sy[ia - 1];
      sy[ia] = sa * sx[ia] + sy[ia];
      sy[ia + 1] = sa * sx[ia + 1] + sy[ia + 1];
      sy[ia + 2] = sa * sx[ia + 2] + sy[ia + 2];
    }
  }
}
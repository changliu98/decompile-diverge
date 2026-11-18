void __cdecl nexper(int n, int *a, int *mtc, int *even)
{
  int m; // [rsp+8h] [rbp-4Ch]
  int i1; // [rsp+Ch] [rbp-48h]
  int l; // [rsp+10h] [rbp-44h]
  int iab; // [rsp+14h] [rbp-40h]
  int iaa; // [rsp+14h] [rbp-40h]
  int j2; // [rsp+18h] [rbp-3Ch]
  int j1; // [rsp+1Ch] [rbp-38h]
  int j; // [rsp+24h] [rbp-30h]
  int ja; // [rsp+24h] [rbp-30h]
  int i; // [rsp+28h] [rbp-2Ch]
  int ia; // [rsp+28h] [rbp-2Ch]
  int ib; // [rsp+28h] [rbp-2Ch]
  int d; // [rsp+2Ch] [rbp-28h]
  int s; // [rsp+30h] [rbp-24h]

  if ( *mtc )
  {
    if ( *even == 1 )
    {
      iab = a[1];
      a[1] = a[2];
      a[2] = iab;
      *even = 0;
      if ( a[n] == 1 && a[1] == n % 2 + 2 )
      {
        if ( n > 3 )
        {
          for ( ia = 1; ia <= n - 3; ++ia )
          {
            if ( a[ia + 1] != a[ia] + 1 )
              return;
          }
          *mtc = 0;
        }
        else
        {
          *mtc = 0;
        }
      }
    }
    else
    {
      s = 0;
      for ( i1 = 2; ; ++i1 )
      {
        if ( i1 > n )
        {
          *mtc = 0;
          return;
        }
        iaa = a[i1];
        ib = i1 - 1;
        j = 1;
        d = 0;
        while ( j <= ib )
        {
          if ( a[j] > iaa )
            ++d;
          ++j;
        }
        s += d;
        if ( d != s % 2 * ib )
          break;
      }
      m = (n + 1) * ((s + 1) % 2);
      for ( ja = 1; ja <= ib; ++ja )
      {
        j1 = a[ja] - iaa;
        j2 = a[ja] - m;
        if ( j1 >= 0 && j2 < 0 || j1 < 0 && j2 >= 0 )
        {
          m = a[ja];
          l = ja;
        }
      }
      a[l] = iaa;
      a[i1] = m;
      *even = 1;
    }
  }
  else
  {
    for ( i = 1; i <= n; ++i )
      a[i] = i;
    *mtc = 1;
    *even = 1;
  }
}
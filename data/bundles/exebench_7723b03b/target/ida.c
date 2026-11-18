void __cdecl sort(char *a)
{
  bool v1; // [rsp+1h] [rbp-15h]
  int k; // [rsp+2h] [rbp-14h]
  int j; // [rsp+6h] [rbp-10h]
  int i; // [rsp+Ah] [rbp-Ch]

  for ( i = 0; a[i + 1]; ++i )
  {
    k = a[i + 1];
    for ( j = i; ; --j )
    {
      v1 = 0;
      if ( a[j] > k )
        v1 = j > 0;
      if ( !v1 )
        break;
      a[j + 1] = a[j];
    }
    a[j + 1] = k;
  }
}
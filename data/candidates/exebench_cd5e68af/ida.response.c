void __cdecl merge(int *a, int *b, int *c)
{
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // ecx
  int v11; // edx
  int v12; // ecx
  bool v13; // [rsp+1h] [rbp-25h]
  int k; // [rsp+2h] [rbp-24h]
  int j; // [rsp+6h] [rbp-20h]
  int i; // [rsp+Ah] [rbp-1Ch]

  i = 0;
  j = 0;
  for ( k = 0; ; ++k )
  {
    v13 = 0;
    if ( i < 6 )
      v13 = j < 6;
    if ( !v13 )
      break;
    if ( a[i] >= b[j] )
    {
      v6 = j++;
      v4 = b[v6];
    }
    else
    {
      v3 = i++;
      v4 = a[v3];
    }
    v5 = k;
    c[v5] = v4;
  }
  while ( i < 6 )
  {
    v7 = i++;
    v8 = a[v7];
    v9 = k++;
    c[v9] = v8;
  }
  while ( j < 6 )
  {
    v10 = j++;
    v11 = b[v10];
    v12 = k++;
    c[v12] = v11;
  }
}
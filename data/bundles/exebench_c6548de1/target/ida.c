void __cdecl swap(int *a)
{
  int maxn; // [rsp+4h] [rbp-18h]
  int i; // [rsp+8h] [rbp-14h]
  int ia; // [rsp+8h] [rbp-14h]
  int minn; // [rsp+10h] [rbp-Ch]

  minn = 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( a[i] < *a )
      minn = i;
  }
  maxn = 0;
  for ( ia = 0; ia < 10; ++ia )
  {
    if ( a[ia] > *a )
      maxn = ia;
  }
  *a += a[minn];
  a[minn] = *a - a[minn];
  *a -= a[minn];
  a[9] += a[maxn];
  a[maxn] = a[9] - a[maxn];
  a[9] -= a[maxn];
}
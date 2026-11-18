int __cdecl func0(int *a, int n, int m)
{
  int maxx; // [rsp+4h] [rbp-1Ch]
  int result; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int ia; // [rsp+Ch] [rbp-14h]

  for ( i = 0; i < n; ++i )
    a[i] = (a[i] % m != 0) + a[i] / m;
  result = -1;
  maxx = -1;
  for ( ia = n - 1; ia >= 0; --ia )
  {
    if ( maxx < a[ia] )
    {
      maxx = a[ia];
      result = ia;
    }
  }
  return result + 1;
}
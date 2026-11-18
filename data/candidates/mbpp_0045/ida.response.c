int __cdecl func0(int *l, int size)
{
  int i; // [rsp+4h] [rbp-1Ch]
  int gcd; // [rsp+8h] [rbp-18h]

  gcd = find_gcd(*l, l[1]);
  for ( i = 2; i < size; ++i )
    gcd = find_gcd(gcd, l[i]);
  return gcd;
}
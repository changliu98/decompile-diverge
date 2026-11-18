int __cdecl func0(int m, int n)
{
  unsigned __int64 na; // [rsp+4h] [rbp-8h]

  HIDWORD(na) = m;
  LODWORD(na) = n;
  if ( n < m )
    na = __PAIR64__(n, m);
  return (3 * HIDWORD(na) - (int)na + 1) * ((int)na + 1) * (int)na / 6;
}
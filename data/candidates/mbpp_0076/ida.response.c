int __cdecl func0(int m, int n)
{
  unsigned __int64 na; // [rsp+8h] [rbp-8h]

  HIDWORD(na) = m;
  LODWORD(na) = n;
  if ( n < m )
    na = __PAIR64__(n, m);
  return (HIDWORD(na) + 1) * HIDWORD(na) * ((int)na - HIDWORD(na)) / 2
       + (2 * HIDWORD(na) + 1) * (HIDWORD(na) + 1) * HIDWORD(na) / 6;
}
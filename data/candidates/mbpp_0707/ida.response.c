int __cdecl func0(int n)
{
  int cnt; // [rsp+4h] [rbp-Ch]
  int powerOf2; // [rsp+8h] [rbp-8h]
  int na; // [rsp+Ch] [rbp-4h]

  na = n + 1;
  powerOf2 = 2;
  cnt = (n + 1) / 2;
  while ( powerOf2 <= na )
  {
    cnt += powerOf2 * (na / powerOf2 / 2);
    if ( ((na / powerOf2) & 1) != 0 )
      cnt += na % powerOf2;
    powerOf2 *= 2;
  }
  return cnt;
}
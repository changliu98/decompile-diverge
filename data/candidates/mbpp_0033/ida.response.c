int __cdecl func0(int N)
{
  int i; // [rsp+0h] [rbp-18h]
  int c; // [rsp+4h] [rbp-14h]
  int cnt; // [rsp+Ch] [rbp-Ch]
  int B_Number; // [rsp+10h] [rbp-8h]

  B_Number = 0;
  cnt = 0;
  while ( N )
  {
    c = 1;
    for ( i = 0; i < cnt; ++i )
      c *= 10;
    B_Number += c * (N % 2);
    N /= 2;
    ++cnt;
  }
  return B_Number;
}
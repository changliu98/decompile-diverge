__int64 __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-1Ch]
  __int64 bfact; // [rsp+4h] [rbp-18h]
  __int64 fact; // [rsp+Ch] [rbp-10h]

  fact = 1LL;
  bfact = 1LL;
  for ( i = 1; i <= n; ++i )
  {
    fact *= i;
    bfact *= fact;
  }
  return bfact;
}
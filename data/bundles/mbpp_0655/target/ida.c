int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-Ch]
  int sm; // [rsp+4h] [rbp-8h]

  sm = 0;
  for ( i = 1; i <= n; ++i )
    sm += i * i * i * i * i;
  return sm;
}
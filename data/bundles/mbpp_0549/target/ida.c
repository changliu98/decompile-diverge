int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-10h]
  int sm; // [rsp+4h] [rbp-Ch]

  sm = 0;
  for ( i = 1; i <= n; ++i )
    sm += (2 * i - 1) * (2 * i - 1) * (2 * i - 1) * (2 * i - 1) * (2 * i - 1);
  return sm;
}
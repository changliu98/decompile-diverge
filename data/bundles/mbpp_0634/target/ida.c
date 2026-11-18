int __cdecl func0(int n)
{
  int i; // [rsp+4h] [rbp-Ch]
  int sum; // [rsp+8h] [rbp-8h]

  sum = 0;
  for ( i = 1; i <= n; ++i )
    sum += 2 * i * 2 * i * 2 * i * 2 * i;
  return sum;
}
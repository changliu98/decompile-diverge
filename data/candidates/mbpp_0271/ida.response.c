long __cdecl func0(int n)
{
  int i; // [rsp+4h] [rbp-14h]
  long sum; // [rsp+8h] [rbp-10h]

  sum = 0LL;
  for ( i = 1; i <= n; ++i )
    sum += 2 * i * 2 * i * 2 * i * 2 * i * 2 * i;
  return sum;
}
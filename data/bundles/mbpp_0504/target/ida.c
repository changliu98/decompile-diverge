int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-Ch]
  int sum; // [rsp+4h] [rbp-8h]

  sum = 0;
  for ( i = 1; i <= n; ++i )
    sum += i * i * i;
  return sum;
}
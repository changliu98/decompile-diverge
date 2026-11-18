int __cdecl func0(int n)
{
  int sum; // [rsp+4h] [rbp-Ch]
  int i; // [rsp+8h] [rbp-8h]

  i = 1;
  sum = 0;
  while ( n / i > 0 )
  {
    sum += n / i;
    i *= 2;
  }
  return sum;
}
int __cdecl func0(int num)
{
  int i; // [rsp+0h] [rbp-Ch]
  int sum; // [rsp+4h] [rbp-8h]

  sum = 0;
  for ( i = 2; i * i <= num; ++i )
  {
    while ( !(num % i) )
    {
      sum += i;
      num /= i;
    }
  }
  return sum + num;
}
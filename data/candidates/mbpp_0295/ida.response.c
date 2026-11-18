int __cdecl func0(int number)
{
  int i; // [rsp+0h] [rbp-Ch]
  int sum; // [rsp+4h] [rbp-8h]

  sum = 1;
  for ( i = 2; i < number; ++i )
  {
    if ( !(number % i) )
      sum += i;
  }
  return sum;
}
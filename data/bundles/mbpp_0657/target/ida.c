int __cdecl func0(int n)
{
  int i; // [rsp+4h] [rbp-Ch]
  int fact; // [rsp+8h] [rbp-8h]

  fact = 1;
  for ( i = 2; i <= n; ++i )
  {
    for ( fact *= i; !(fact % 10); fact /= 10 )
      ;
  }
  while ( fact >= 10 )
    fact /= 10;
  return (int)floor((double)fact);
}
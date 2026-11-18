int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-14h]
  int isPrime; // [rsp+4h] [rbp-10h]
  int num; // [rsp+8h] [rbp-Ch]
  int ctr; // [rsp+Ch] [rbp-8h]

  ctr = 0;
  for ( num = 0; num < n; ++num )
  {
    if ( num > 1 )
    {
      isPrime = 1;
      for ( i = 2; i < num; ++i )
      {
        if ( !(num % i) )
        {
          isPrime = 0;
          break;
        }
      }
      if ( isPrime )
        ++ctr;
    }
  }
  return ctr;
}
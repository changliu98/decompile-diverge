int __cdecl func0(int n)
{
  int i; // [rsp+4h] [rbp-Ch]
  int result; // [rsp+8h] [rbp-8h]

  result = 0;
  for ( i = 2; i <= (int)sqrt((double)n); ++i )
  {
    if ( !(n % i) )
      result = 1;
  }
  return result;
}
int __cdecl func0(int x)
{
  int fact; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  fact = 1;
  for ( i = 1; i < x; ++i )
  {
    fact *= i;
    if ( !(fact % x) )
      return i;
  }
  return i - 1;
}
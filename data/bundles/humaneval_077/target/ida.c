int __cdecl func0(int a)
{
  int i; // [rsp+14h] [rbp-Ch]

  for ( i = 0; i * i * i <= abs(a); ++i )
  {
    if ( i * i * i == abs(a) )
      return 1;
  }
  return 0;
}
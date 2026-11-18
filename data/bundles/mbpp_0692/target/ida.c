int __cdecl func0(int N)
{
  int i; // [rsp+0h] [rbp-10h]
  int fac; // [rsp+4h] [rbp-Ch]

  if ( N >= 10 )
    return 0;
  fac = 1;
  for ( i = 1; i <= N; ++i )
    fac = i * fac % 100;
  return fac;
}
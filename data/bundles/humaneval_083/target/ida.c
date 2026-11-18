int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-10h]
  int out; // [rsp+4h] [rbp-Ch]

  if ( n < 1 )
    return 0;
  if ( n == 1 )
    return 1;
  out = 18;
  for ( i = 2; i < n; ++i )
    out *= 10;
  return out;
}
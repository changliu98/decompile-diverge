int __cdecl func0(int n)
{
  int i; // [rsp+0h] [rbp-18h]
  int c; // [rsp+4h] [rbp-14h]
  int b; // [rsp+8h] [rbp-10h]
  int a; // [rsp+Ch] [rbp-Ch]

  if ( n <= 2 )
    return n;
  a = 1;
  b = 2;
  for ( i = 3; i <= n; ++i )
  {
    c = a + 2 * b;
    a = b;
    b = c;
  }
  return b;
}
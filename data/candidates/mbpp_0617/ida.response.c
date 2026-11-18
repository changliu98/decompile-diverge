int __cdecl func0(int a, int b, int d)
{
  int v4; // [rsp+0h] [rbp-1Ch]
  int v5; // [rsp+4h] [rbp-18h]

  if ( a >= b )
    v5 = b;
  else
    v5 = a;
  if ( a <= b )
    v4 = b;
  else
    v4 = a;
  if ( d >= v4 )
    return (v4 + d - 1) / v4;
  if ( !d )
    return 0;
  if ( d == v5 )
    return 1;
  return 2;
}
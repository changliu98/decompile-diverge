int __cdecl func0(int a, int b)
{
  int v3; // [rsp+4h] [rbp-1Ch]
  int v4; // [rsp+8h] [rbp-18h]

  if ( a >= b )
    v4 = b;
  else
    v4 = a;
  if ( a <= b )
    v3 = b;
  else
    v3 = a;
  if ( !v4 )
    return v3;
  if ( v4 == 1 )
    return 1;
  return func0(v4, v3 % v4);
}
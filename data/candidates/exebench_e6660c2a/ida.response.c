void __cdecl foo(int *x, int y, int z)
{
  int v3; // ecx
  int v4; // eax
  int d; // [rsp+4h] [rbp-1Ch]
  int c; // [rsp+8h] [rbp-18h]
  int b; // [rsp+Ch] [rbp-14h]

  c = *x;
  d = x[1];
  for ( b = 0; b < 1; ++b )
  {
    v3 = 0;
    if ( d )
      v3 = 2;
    v4 = 0;
    if ( c )
      v4 = 2;
    x[b + 2] = (z != 0) | v3 | (y != 0) | (1 >> b != 0) | v4;
  }
}
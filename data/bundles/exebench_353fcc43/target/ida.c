void __cdecl copy_poly(int *dst, int *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 20; ++i )
    dst[i] = src[i];
}
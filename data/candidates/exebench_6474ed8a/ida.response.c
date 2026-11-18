int __cdecl gen256(unsigned __int8 *dst, unsigned int prim_poly)
{
  __int16 v; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]

  if ( (prim_poly & 0x100) == 0 )
    return -1;
  *dst = 0;
  dst[1] = 1;
  v = 1;
  for ( i = 2; i < 256; ++i )
  {
    v *= 2;
    if ( (v & 0x100) != 0 )
      v = (unsigned __int8)v ^ (unsigned __int8)prim_poly;
    dst[i] = v;
  }
  return 0;
}
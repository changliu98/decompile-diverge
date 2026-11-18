uint32_t __cdecl par_msquares_argb(const par_byte *pdata, int bpp)
{
  int j; // [rsp+0h] [rbp-1Ch]
  int color; // [rsp+4h] [rbp-18h]

  color = 0;
  if ( bpp == 4 )
    return pdata[2] | (pdata[1] << 8) | (*pdata << 16) | (pdata[3] << 24);
  for ( j = 0; j < bpp; ++j )
    color = (color << 8) | pdata[j];
  return color;
}
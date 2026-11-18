float __cdecl KBND_REPLICATE(const float *img, int w, int h, int x, int y, float bnd_const)
{
  int ya; // [rsp+4h] [rbp-18h]
  int xa; // [rsp+8h] [rbp-14h]

  xa = x;
  ya = y;
  if ( x < 0 )
    xa = 0;
  if ( xa >= w )
    xa = w - 1;
  if ( y < 0 )
    ya = 0;
  if ( ya >= h )
    ya = h - 1;
  return img[xa + w * ya];
}
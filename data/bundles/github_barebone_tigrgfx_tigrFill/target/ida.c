void __cdecl tigrFill(Tigr *bmp, int x, int y, int w, int h, TPixel color)
{
  int i; // [rsp+0h] [rbp-30h]
  int dt; // [rsp+4h] [rbp-2Ch]
  TPixel *td; // [rsp+8h] [rbp-28h]
  int ha; // [rsp+10h] [rbp-20h]
  int wa; // [rsp+14h] [rbp-1Ch]
  int ya; // [rsp+18h] [rbp-18h]
  int xa; // [rsp+1Ch] [rbp-14h]

  xa = x;
  ya = y;
  wa = w;
  ha = h;
  if ( x < 0 )
  {
    wa = w + x;
    xa = 0;
  }
  if ( y < 0 )
  {
    ha = h + y;
    ya = 0;
  }
  if ( wa + xa > bmp->w )
    wa = bmp->w - xa;
  if ( ha + ya > bmp->h )
    ha = bmp->h - ya;
  if ( wa > 0 && ha > 0 )
  {
    td = &bmp->pix[xa + bmp->w * ya];
    dt = bmp->w;
    do
    {
      for ( i = 0; i < wa; ++i )
        td[i] = color;
      td += dt;
      --ha;
    }
    while ( ha );
  }
}
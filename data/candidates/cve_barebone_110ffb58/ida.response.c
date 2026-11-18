void __cdecl gdImageFillToBorder(gdImagePtr im, int x, int y, int border, int color)
{
  int c_0; // [rsp+Ch] [rbp-34h]
  int c; // [rsp+10h] [rbp-30h]
  int restoreAlphaBleding; // [rsp+14h] [rbp-2Ch]
  int i; // [rsp+18h] [rbp-28h]
  int ia; // [rsp+18h] [rbp-28h]
  int ib; // [rsp+18h] [rbp-28h]
  int ic; // [rsp+18h] [rbp-28h]
  int rightLimit; // [rsp+1Ch] [rbp-24h]
  int leftLimit; // [rsp+20h] [rbp-20h]
  int lastBorder; // [rsp+24h] [rbp-1Ch]
  int lastBordera; // [rsp+24h] [rbp-1Ch]
  int ya; // [rsp+30h] [rbp-10h]
  int xa; // [rsp+34h] [rbp-Ch]

  xa = x;
  ya = y;
  if ( border >= 0 )
  {
    leftLimit = -1;
    restoreAlphaBleding = im->alphaBlendingFlag;
    im->alphaBlendingFlag = 0;
    if ( x < im->sx )
    {
      if ( x < 0 )
        xa = 0;
    }
    else
    {
      xa = im->sx - 1;
    }
    if ( y < im->sy )
    {
      if ( y < 0 )
        ya = 0;
    }
    else
    {
      ya = im->sy - 1;
    }
    for ( i = xa; i >= 0 && gdImageGetPixel(im, i, ya) != border; --i )
    {
      gdImageSetPixel(im, i, ya, color);
      leftLimit = i;
    }
    if ( leftLimit == -1 )
    {
      im->alphaBlendingFlag = restoreAlphaBleding;
    }
    else
    {
      rightLimit = xa;
      for ( ia = xa + 1; ia < im->sx && gdImageGetPixel(im, ia, ya) != border; ++ia )
      {
        gdImageSetPixel(im, ia, ya, color);
        rightLimit = ia;
      }
      if ( ya > 0 )
      {
        lastBorder = 1;
        for ( ib = leftLimit; ib <= rightLimit; ++ib )
        {
          c = gdImageGetPixel(im, ib, ya - 1);
          if ( lastBorder )
          {
            if ( c != border && c != color )
            {
              gdImageFillToBorder(im, ib, ya - 1, border, color);
              lastBorder = 0;
            }
          }
          else if ( c == border || c == color )
          {
            lastBorder = 1;
          }
        }
      }
      if ( ya < im->sy - 1 )
      {
        lastBordera = 1;
        for ( ic = leftLimit; ic <= rightLimit; ++ic )
        {
          c_0 = gdImageGetPixel(im, ic, ya + 1);
          if ( lastBordera )
          {
            if ( c_0 != border && c_0 != color )
            {
              gdImageFillToBorder(im, ic, ya + 1, border, color);
              lastBordera = 0;
            }
          }
          else if ( c_0 == border || c_0 == color )
          {
            lastBordera = 1;
          }
        }
      }
      im->alphaBlendingFlag = restoreAlphaBleding;
    }
  }
}
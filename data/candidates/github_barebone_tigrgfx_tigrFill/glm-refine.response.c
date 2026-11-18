void __cdecl tigrFill(Tigr *bmp, int x, int y, int w, int h, TPixel color)
{
  // Clip the fill rectangle to the bitmap's positive bounds
  if (x < 0)
  {
    w += x;
    x = 0;
  }
  if (y < 0)
  {
    h += y;
    y = 0;
  }

  // Clip the fill rectangle to the bitmap's maximum dimensions
  if (x + w > bmp->w)
    w = bmp->w - x;
  if (y + h > bmp->h)
    h = bmp->h - y;

  // If the clipped rectangle is valid, fill it
  if (w > 0 && h > 0)
  {
    TPixel *row = &bmp->pix[x + bmp->w * y];
    
    do
    {
      // Fill the current row
      for (int i = 0; i < w; ++i)
        row[i] = color;
        
      // Advance to the next row
      row += bmp->w;
      --h;
    }
    while (h);
  }
}
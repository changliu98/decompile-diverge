int clip(int x1, int y1, int x2, int y2, int *x, int *y, int *w, int *h, int *sx, int *sy, int dx, int dy)
{
  if ( *x < x1 )
  {
    *w -= (x1 - *x);
    *sx += (x1 - *x)*dx;
    *x = x1;
  }
  if ( *w > (x2 - *x + 1))
    *w = (x2 - *x + 1);
  if ( *y < y1 )
  {
    *h -= (y1 - *y);
    *sy += (y1 - *y)*dy;
    *y = y1;
  }
  if ( *h > (y2 - *y + 1))
    *h = (y2 - *y + 1);
  if ( *w < 0 )
    return 0;
  if ( *h < 0 )
    return 0;
  return 1;
}
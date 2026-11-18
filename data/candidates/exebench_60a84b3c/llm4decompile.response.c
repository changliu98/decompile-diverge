char sraClipRect2(int *x1, int *y1, int *x2, int *y2,
                  int xc1, int yc1, int xc2, int yc2)
{
  char ret;


  if(*x1 < xc1)
    *x1 = xc1;
  if(*y1 < yc1)
    *y1 = yc1;
  if(*x1 >= xc2)
    *x1 = xc2 - 1;
  if(*y1 >= yc2)
    *y1 = yc2 - 1;


  if(*x2 <= xc1)
    *x2 = xc1 + 1;
  if(*y2 <= yc1)
    *y2 = yc1 + 1;
  if(*x2 > xc2)
    *x2 = xc2;
  if(*y2 > yc2)
    *y2 = yc2;

  ret = *x1 < *x2 && *y1 < *y2;
  return(ret);
}
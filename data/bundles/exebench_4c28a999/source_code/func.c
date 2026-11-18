
void fb_hFixCoordsOrder(int *x1, int *y1, int *x2, int *y2)
{
 if (*x2 < *x1)
  ((*x1) ^= (*x2), (*x2) ^= (*x1), (*x1) ^= (*x2));

 if (*y2 < *y1)
  ((*y1) ^= (*y2), (*y2) ^= (*y1), (*y1) ^= (*y2));
}

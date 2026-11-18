void rgb2cmy(double r, double g, double b, double *c, double *m, double *y, double *k)
{
  double min;
  *c = 1 - r;
  *m = 1 - g;
  *y = 1 - b;
  if (*m < *c)
    min = *m;
  else
    min = *c;
  *k = min;
  if (*k < *y)
    min = *k;
  else
    min = *y;
  *k = min;
  *c -= *k;
  *m -= *k;
  *y -= *k;
}
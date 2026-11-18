void rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
  double vmin; double vmax; double delta;
  double hval = 0.0;
  double sval = 0.0;
  if (b < g)
    vmin = b;
  else
    vmin = g;
  if (vmin < r)
    vmin = r;
  if (r < g)
    vmax = r;
  else
    vmax = g;
  if (g < b)
    vmax = b;
  else
    vmax = g;
  if (vmax > 0.0)
    sval = (vmax - vmin)/vmax;
  if (sval > 0.0)
  {
    double rc = (vmax - r)/(vmax - vmin);
    double gc = (vmax - g)/(vmax - vmin);
    double bc = (vmax - b)/(vmax - vmin);
    if (r == vmax)
      hval = bc - gc;
    else if (g == vmax)
      hval = rc + 2 - bc;
    else if (b == vmax)
      hval = gc + 4 - rc;
    hval = hval * 60.0;
    if (hval < 0.0)
      hval = hval + 360.0;
  }
  *h = hval/360.0;
  *v = vmax;
  *s = sval;
}
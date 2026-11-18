int shape_tria3(double *srgb, double *lab)
{
  double r = srgb[0];
  double g = srgb[1];
  double b = srgb[2];
  double l = 0.0;
  double a = 0.0;
  double b = 0.0;
  if (r > g && r > b)
  {
    l = 116 * f(r) - 16;
    a = 500 * (f(r) - f(g));
    b = 200 * (f(r) - f(b));
  }
  else if (g > r && g > b)
  {
    l = 116 * f(g) - 16;
    a = 500 * (f(r) - f(g));
    b = 200 * (f(g) - f(b));
  }
  else
  {
    l = 116 * f(b) - 16;
    a = 500 * (f(r) - f(g));
    b = 200 * (f(g) - f(b));
  }
  lab[0] = l;
  lab[1] = a;
  lab[2] = b;
  return 0;
}
double func0(double x)
{
  double g; double g1;
  if (x == 0.)
    return (0.);
  g = x / 2.;
  g1 = g + 1.;
  while (g != g1) {
    g1 = g;
    g = (g + x / g) / 2.;
  }
  return (g);
}
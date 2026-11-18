void __cdecl func0(int r, int g, int b, double *h, double *s, double *v)
{
  double rd = (double)r / 255.0;
  double gd = (double)g / 255.0;
  double bd = (double)b / 255.0;

  double mx = fmax(rd, fmax(gd, bd));
  double mn = fmin(rd, fmin(gd, bd));
  double df = mx - mn;

  *h = 0.0;
  if (df > 0.0)
  {
    if (mx == rd)
    {
      *h = fmod((gd - bd) / df * 60.0 + 360.0, 360.0);
    }
    else if (mx == gd)
    {
      *h = fmod((bd - rd) / df * 60.0 + 120.0, 360.0);
    }
    else if (mx == bd)
    {
      *h = fmod((rd - gd) / df * 60.0 + 240.0, 360.0);
    }
  }

  *s = (mx == 0.0) ? 0.0 : (df / mx * 100.0);
  *v = 100.0 * mx;
}
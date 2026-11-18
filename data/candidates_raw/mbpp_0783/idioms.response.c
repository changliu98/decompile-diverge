void rgb2hsv(int r, int g, int b, double *h, double *s, double *v)
{
  double rd = r / 255.0;
  double gd = g / 255.0;
  double bd = b / 255.0;
  double mx = fmax(fmax(rd, gd), bd);
  double mn = fmin(fmin(rd, gd), bd);
  double df = mx - mn;
  *h = 0;
  if (df > 0) {
    if (mx == rd)
      *h = fmod((gd - bd) / df * 60 + 360, 360);
    else if (mx == gd)
      *h = fmod((bd - rd) / df * 60 + 120, 360);
    else if (mx == bd)
      *h = fmod((rd - gd) / df * 60 + 240, 360);
  }
  if (mx == 0)
    *s = 0;
  else
    *s = (df / mx) * 100;
  *v = mx * 100;
}
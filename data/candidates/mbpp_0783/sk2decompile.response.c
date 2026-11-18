void _rgb2hsi(int r, int g, int b, double *h, double *s, double *i) {
  double rr, gg, bb, cmax, cmin, delta;
  rr = r / 255.0;
  gg = g / 255.0;
  bb = b / 255.0;
  cmax = (((rr) > (((gg) > (bb) ? (gg) : (bb))))
              ? (rr)
              : (((gg) > (bb) ? (gg) : (bb))));
  cmin = (((rr) < (((gg) < (bb) ? (gg) : (bb))))
              ? (rr)
              : (((gg) < (bb) ? (gg) : (bb))));
  delta = cmax - cmin;
  *h = 0.0;
  if (delta > 0.0) {
    if (cmax == rr)
      *h = fmod((gg - bb) / delta * 60.0 + 360.0, 360.0);
    else if (cmax == gg)
      *h = fmod((bb - rr) / delta * 60.0 + 120.0, 360.0);
    else if (cmax == bb)
      *h = fmod((rr - gg) / delta * 60.0 + 240.0, 360.0);
  }
  if (cmax == 0.0)
    *s = 0.0;
  else
    *s = delta / cmax * 100.0;
  *i = cmax * 100.0;
}
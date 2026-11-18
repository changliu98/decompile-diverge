void rahms(double ra, int *h, int *m, float *s)
{
  double d;
  if (ra < 0.0)
    ra += 360.0;
  if (ra > 360.0)
    ra -= 360.0;
  d = ra / 15.0;
  *h = (int) d;
  d = (d - (double)(*h)) * 60.0;
  *m = (int) d;
  d = (d - (double)(*m)) * 60.0;
  *s = (float) d;
}
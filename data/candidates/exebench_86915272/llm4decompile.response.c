void rahms(double ra, int *h, int *m, float *s)
{
 double temp;

 if (ra < 0.0)
  ra += 24.0;
 if (ra > 24.0)
  ra -= 24.0;

 temp = ra / 15.0;
 *h = (int)temp;
 temp -= *h;
 temp *= 60.0;
 *m = (int)temp;
 temp -= *m;
 temp *= 60.0;
 *s = (float)temp;
}
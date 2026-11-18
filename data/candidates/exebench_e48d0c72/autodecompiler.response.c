static int setLoopIters(double tmin, double tscale, double threshold_hi, unsigned *nloop)
{
 double time_min = tmin * tscale * (double) *nloop;

 if (time_min > threshold_hi) {
  *nloop = (unsigned) ((double) *nloop * threshold_hi / time_min);
  if (*nloop < 2)
   *nloop = 2;
 } else
  return 0;

 return 0;
}
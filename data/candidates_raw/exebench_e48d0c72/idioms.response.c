int adjust_loop(double tMin, double tScale, double threshold_hi, int *NLOOP)
{
  double timeMin;
  timeMin = tMin * tScale * *NLOOP;
  if (timeMin > threshold_hi) {
    *NLOOP = (int)(threshold_hi * *NLOOP / timeMin);
    if (*NLOOP < 2)
      *NLOOP = 2;
  }
  return 0;
}
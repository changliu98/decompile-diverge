void rahms(double ra, int *hr, int *min, float *sec) {
  double ra1, ra2;
  ra1 = ra;
  if (ra1 < 0.0) ra1 += 360.0;
  if (ra1 > 360.0) ra1 -= 360.0;
  ra1 /= 15.0;
  *hr = (int)ra1;
  ra2 = (ra1 - (double)(*hr)) * 60.0;
  *min = (int)ra2;
  *sec = (ra2 - (double)(*min)) * 60.0;
}
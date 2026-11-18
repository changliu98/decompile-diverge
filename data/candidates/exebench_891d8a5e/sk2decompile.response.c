void decdms(double ddeg, int *d, int *m, float *s) {
  double f;
  *d = (int)ddeg;
  f = ddeg - *d;
  if (f < 0) f = -f;
  f *= 60;
  *m = (int)f;
  f -= *m;
  f *= 60;
  *s = (float)f;
}
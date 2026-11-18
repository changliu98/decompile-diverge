void r2d(double *ra, double *dec, int *hr, double *min, char *sign, int *deg,
         double *sec) {
  float f;
  f = *ra / 0.017453292 / 15.0;
  while (f > 24.0) f -= 24.0;
  *hr = (int)f;
  *min = (f - (float)*hr) * 60.0;
  *min += 0.000001;
  if (*min >= 60.0) {
    *min -= 60.0;
    *hr += 1;
  }
  if (*hr >= 24) *hr -= 24;
  if (*dec < 0.0) {
    *sign = '-';
    *dec = -(*dec);
  } else
    *sign = '+';
  f = *dec / 0.017453292;
  *deg = (int)f;
  *sec = (f - (float)*deg) * 60.0;
}
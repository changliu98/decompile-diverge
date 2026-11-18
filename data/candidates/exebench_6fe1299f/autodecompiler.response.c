void
quant_u(float *ival, int *iindex, float imin, float imax, int nlev)
{
  float range;
  float step;
  float upper;
  int j;

  float *fval = (float *) ival;
  int *findex = (int *) iindex;

  range = imax - imin;
  step = range / (nlev - 1);
  upper = imin + step / 2.0;
  j = nlev - 1;

  for (;;) {
    if (*fval < upper) break;
    upper += step;
    if (++j >= nlev) break;
  }

  *fval = imin + step * j;
  *findex = j;
}
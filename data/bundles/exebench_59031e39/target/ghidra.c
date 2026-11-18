double my_modf(double x0,double *iptr)

{
  double ret;
  double i2;
  double f;
  double x;
  long l;
  int i;
  double *iptr_local;
  double x0_local;
  double local_10;
  
  f = DAT_00102010;
  i = 0;
  for (x = x0; (i < 100 &&
               ((l = (long)x, DAT_00102010 + x < (double)l || ((double)l < x - DAT_00102010))));
      x = DAT_00102020 * x) {
    f = DAT_00102018 * f;
    i = i + 1;
  }
  if (i == 100) {
    *iptr = 0.0;
    local_10 = 0.0;
  }
  else if (i == 0) {
    *iptr = (double)l;
    local_10 = x - *iptr;
  }
  else {
    iptr_local = iptr;
    x0_local = x0;
    local_10 = my_modf(-(double)l * f + x0,&i2);
    *iptr_local = (double)l * f + i2;
  }
  return local_10;
}
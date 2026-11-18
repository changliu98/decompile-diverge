float spline_cubic_val(int n,float *t,float tval,float *y,float *ypp)

{
  float fVar1;
  float fVar2;
  float yval;
  int ival;
  int i;
  float h;
  float dt;
  float *ypp_local;
  float *y_local;
  float tval_local;
  float *t_local;
  int n_local;
  
  ival = n + -2;
  i = 0;
  do {
    if (n + -1 <= i) {
LAB_00101257:
      fVar1 = tval - t[ival];
      fVar2 = t[ival + 1] - t[ival];
      return (float)((double)fVar1 *
                     ((double)fVar1 *
                      ((double)ypp[ival] * DAT_00102008 +
                      (double)fVar1 *
                      ((double)(ypp[ival + 1] - ypp[ival]) / (DAT_00102010 * (double)fVar2))) +
                     -((double)ypp[ival + 1] / DAT_00102010 + (double)ypp[ival] / DAT_00102018) *
                     (double)fVar2 + (double)((y[ival + 1] - y[ival]) / fVar2)) + (double)y[ival]);
    }
    if (tval < t[i + 1]) {
      ival = i;
      goto LAB_00101257;
    }
    i = i + 1;
  } while( true );
}
void GetLims(double *t, double t1, double t2, int N, int *i1, int *i2)
{
 int i;
 double t_i;
 int flag1 = 0, flag2 = 0;

 if (N == 0) {
  *i1 = 0;
  *i2 = -1;
  return;
 }

 for (i = 0; i < N; i++) {
  t_i = t[i];
  if ((t_i >= t2) & (flag1 == 0)) {
   *i1 = 0;
   *i2 = -1;
   flag1 = 1;
   flag2 = 1;
   continue;
  }
  if ((t_i >= t1) & (flag1 == 0)) {
   *i1 = i;
   flag1 = 1;
   continue;
  }
  if ((t_i >= t2) & (flag2 == 0)) {
   *i2 = i - 1;
   flag2 = 1;
   continue;
  }
 }
 if (flag1 == 0) {
  *i1 = 0;
  *i2 = -1;
  return;
 }
 if (flag2 == 0) {
  *i2 = N - 1;
  return;
 }
}
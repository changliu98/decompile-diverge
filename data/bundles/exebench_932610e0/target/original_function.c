double randlc(double *x, double *a)
{
# 21 "c_randi8.c"
  long long Lx, La;
  double randlc;
  const long long i246m1 = 0x00003FFFFFFFFFFF;
  const double d2m46 = 1.4210854715202003e-14;

  Lx = *x;
  La = *a;

  Lx = (Lx*La)&i246m1;
  randlc = d2m46*(double)Lx;
  *x = (double)(Lx);
  return randlc;
}
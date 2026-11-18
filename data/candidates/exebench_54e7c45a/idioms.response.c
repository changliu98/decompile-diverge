int matMultMV(double *a, double *b, double *r)
{
  double r1 = a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];
  double r2 = a[4]*b[0]+a[5]*b[1]+a[6]*b[2]+a[7]*b[3];
  double r3 = a[8]*b[0]+a[9]*b[1]+a[10]*b[2]+a[11]*b[3];
  double r4 = a[12]*b[0]+a[13]*b[1]+a[14]*b[2]+a[15]*b[3];
  r[0]=r1;
  r[1]=r2;
  r[2]=r3;
  r[3]=r4;
  return 0;
}
int matMultMV(double *m,double *v,double *r2)
{
  double r[4];
  r[0]=m[0]*v[0]+m[1]*v[1]+m[2]*v[2]+m[3]*v[3];
  r[1]=m[4]*v[0]+m[5]*v[1]+m[6]*v[2]+m[7]*v[3];
  r[2]=m[8]*v[0]+m[9]*v[1]+m[10]*v[2]+m[11]*v[3];
  r[3]=m[12]*v[0]+m[13]*v[1]+m[14]*v[2]+m[15]*v[3];

  r2[0]=r[0]; r2[1]=r[1]; r2[2]=r[2]; r2[3]=r[3];

  return 0;
}
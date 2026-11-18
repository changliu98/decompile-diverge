double Mat_doubleSwap(double *d)
{
  double tmp;
  char *c = (char *)&tmp;
  char *cd = (char *)d;
  c[0]=cd[7];
  c[1]=cd[6];
  c[2]=cd[5];
  c[3]=cd[4];
  c[4]=cd[3];
  c[5]=cd[2];
  c[6]=cd[1];
  c[7]=cd[0];
  return *d = tmp;
}
void poly_mul1(double *u1,double *u2,int p1,int p2,double *u3,int *p3)

{
  double dVar1;
  double u1i;
  int i3;
  int i2;
  int i1;
  int i;
  int *p3_local;
  double *u3_local;
  int p2_local;
  int p1_local;
  double *u2_local;
  double *u1_local;
  
  *p3 = p1 + p2;
  for (i = 0; i < 0x11; i = i + 1) {
    u3[i] = 0.0;
  }
  for (i1 = 0; i1 <= p1; i1 = i1 + 1) {
    dVar1 = u1[i1];
    for (i2 = 0; i2 <= p2; i2 = i2 + 1) {
      u3[i1 + i2] = dVar1 * u2[i2] + u3[i1 + i2];
    }
  }
  return;
}
void MultMat(double *a,double *b,double *c)

{
  int j;
  int i;
  double *c_local;
  double *b_local;
  double *a_local;
  
  for (i = 0; i < 3; i = i + 1) {
    for (j = 0; j < 3; j = j + 1) {
      c[i * 3 + j] = a[i * 3 + 2] * b[j + 6] + a[i * 3] * b[j] + a[i * 3 + 1] * b[j + 3];
    }
  }
  return;
}
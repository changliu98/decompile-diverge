void mult(double *a, double *b, double *c)
{
  int i = 0; int j = 0;
  for (i = 0; i < 4; i++) {
    c[i] = a[0]*b[0];
    c[i] += a[1]*b[1];
    c[i] += a[2]*b[2];
    c[i] += a[3]*b[3];
  }
}
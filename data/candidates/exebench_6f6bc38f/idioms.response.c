void geom_matmat2d(double *a, double *b, double *c)
{
  c[0] = a[0]*b[0] + a[2]*b[1];
  c[1] = a[1]*b[0] + a[3]*b[1];
  c[2] = a[0]*b[2] + a[2]*b[3];
  c[3] = a[1]*b[2] + a[3]*b[3];
}
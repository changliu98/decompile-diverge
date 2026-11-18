void matmul(double *a, double *b, double *c, double alpha, double beta)
{
  c[0] = c[0]*beta + a[0]*b[0] + a[1]*b[1] + a[2]*b[2] + a[3]*b[3]*alpha;
  c[1] = c[1]*beta + a[4]*b[0] + a[5]*b[1] + a[6]*b[2] + a[7]*b[3]*alpha;
  c[2] = c[2]*beta + a[8]*b[0] + a[9]*b[1] + a[10]*b[2] + a[11]*b[3]*alpha;
  c[3] = c[3]*beta + a[12]*b[0] + a[13]*b[1] + a[14]*b[2] + a[15]*b[3]*alpha;
}
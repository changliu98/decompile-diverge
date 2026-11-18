void matmul(double *a, double *b, double *c, double alpha, double beta)
{
  c[0] = beta * c[0] + alpha * (a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12]);
  c[1] = beta * c[1] + alpha * (a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13]);
  c[2] = beta * c[2] + alpha * (a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14]);
  c[3] = beta * c[3] + alpha * (a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15]);
  c[4] = beta * c[4] + alpha * (a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12]);
  c[5] = beta * c[5] + alpha * (a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13]);
  c[6] = beta * c[6] + alpha * (a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14]);
  c[7] = beta * c[7] + alpha * (a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15]);
  c[8] = beta * c[8] + alpha * (a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12]);
  c[9] = beta * c[9] + alpha * (a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13]);
  c[10] = beta * c[10] + alpha * (a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14]);
  c[11] = beta * c[11] + alpha * (a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15]);
  c[12] = beta * c[12] + alpha * (a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12]);
  c[13] = beta * c[13] + alpha * (a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13]);
  c[14] = beta * c[14] + alpha * (a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14]);
  c[15] = beta * c[15] + alpha * (a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]);
}
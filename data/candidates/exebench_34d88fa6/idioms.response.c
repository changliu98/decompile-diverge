void mlMatrixMultVectorTo(float a[16], float b[3], float r[3])
{
  r[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12];
  r[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13];
  r[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14];
}
void quat_mul(float *a, float *b)
{
  float a0 = a[0]; float a1 = a[1]; float a2 = a[2]; float a3 = a[3];
  float b0 = b[0]; float b1 = b[1]; float b2 = b[2]; float b3 = b[3];
  a[0] = a0 * b0 - a1 * b1 - a2 * b2 - a3 * b3;
  a[1] = a0 * b1 + a1 * b0 + a2 * b3 - a3 * b2;
  a[2] = a0 * b2 - a1 * b3 + a2 * b0 + a3 * b1;
  a[3] = a0 * b3 + a1 * b2 - a2 * b1 + a3 * b0;
}
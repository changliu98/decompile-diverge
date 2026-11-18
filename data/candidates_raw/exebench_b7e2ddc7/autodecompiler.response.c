void transpose3f(float *a, float *b)
{
  a[0] = b[0];
  a[1] = b[4];
  a[2] = b[8];
  a[4] = b[1];
  a[5] = b[5];
  a[6] = b[9];
  a[8] = b[2];
  a[9] = b[6];
  a[10] = b[10];
}
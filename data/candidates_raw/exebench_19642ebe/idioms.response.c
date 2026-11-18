void matmul(float a[16], float b[16], float c[16])
{
  int i; int j;
  for (i = 0; i < 16; i += 4)
    for (j = 0; j < 4; j++)
      c[i + j] = a[0 + j] * b[i + 0] + a[4 + j] * b[i + 1] +
        a[8 + j] * b[i + 2] + a[12 + j] * b[i + 3];
}
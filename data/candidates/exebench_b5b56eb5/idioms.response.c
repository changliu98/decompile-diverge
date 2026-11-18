void mlPointSubTo(float a[3], float b[3], float c[3])
{
  unsigned int i;
  for (i = 0; i < 3; i++)
    c[i] = a[i] - b[i];
}
void mlPointAddTo(float a[3], float b[3], float result[3])
{
  unsigned int i;
  for (i = 0; i < 3; i++)
    result[i] = a[i] + b[i];
}
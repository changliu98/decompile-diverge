static _Bool array_eq(float *a, float *b, unsigned long rows, unsigned long cols)
{
  int i;
  for (i = 0; i < rows * cols; i++)
    if (a[i] != b[i])
      return 0;
  return 1;
}
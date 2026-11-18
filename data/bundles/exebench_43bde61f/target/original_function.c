void
mlPointAddTo(const float *a, const float *b, float *result)
{
 unsigned int i;

 for(i = 0; i < 3; i++)
  result[i] = a[i] + b[i];
}
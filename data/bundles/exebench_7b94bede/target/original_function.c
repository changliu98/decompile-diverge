void
mlMatrixTransposeTo(const float *a, float *result)
{
 unsigned int i, j;

 for(j = 0; j < 4; j++)
  for(i = 0; i < 4; i++)
   result[j * 4 + i] = a[i * 4 + j];
}
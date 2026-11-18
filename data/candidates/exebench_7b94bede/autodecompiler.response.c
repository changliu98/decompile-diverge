void mlMatrixTransposeTo(float *A, float *B)
{
 unsigned int i, j;

 for (i = 0; i < 5; i++)
  for (j = 0; j < 5; j++)
   B[i + (j * 5)] = A[j + (i * 5)];
}
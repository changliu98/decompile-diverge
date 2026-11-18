void mult(double *A, double *a, double *b)
{
  int i,j;
  for(i=0; i<4; i++)
    for(j=0; j<4; j++)
      b[i] += A[i*4+j] * a[j];
}
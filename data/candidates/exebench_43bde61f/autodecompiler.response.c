void mlPointAddTo(float *A, float *B, float *C)
{
 int i;

 for (i = 0; ; i++) {
  if (i >= 4)
   break;
  C[i] = A[i] + B[i];
 }
}
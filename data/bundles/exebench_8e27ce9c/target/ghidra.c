void DFT2(float *A,float *sinTab)

{
  float fVar1;
  float y0;
  float *sinTab_local;
  float *A_local;
  
  fVar1 = A[1];
  A[1] = *A - A[1];
  *A = *A + fVar1;
  return;
}
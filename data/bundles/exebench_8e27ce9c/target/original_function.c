void DFT2(float *A, const float *sinTab)
{
 float y0 = A[0] + A[1];
 A[1] = A[0] - A[1];
 A[0] = y0;
}
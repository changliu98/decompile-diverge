void __cdecl DFT2(float *A, const float *sinTab)
{
  float y0; // [rsp+0h] [rbp-14h]

  y0 = *A + A[1];
  A[1] = *A - A[1];
  *A = y0;
}
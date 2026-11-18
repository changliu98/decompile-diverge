void __cdecl DFT2(float *A, const float *sinTab)
{
  float real = A[0];
  float imag = A[1];

  A[0] = real + imag;
  A[1] = real - imag;
}
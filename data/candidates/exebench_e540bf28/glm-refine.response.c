void __cdecl rfft1pt(float *ioptr)
{
  float real = ioptr[0];
  float imag = ioptr[1];

  ioptr[0] = real + imag;
  ioptr[1] = real - imag;
}
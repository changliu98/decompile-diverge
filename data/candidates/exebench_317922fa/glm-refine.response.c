void __cdecl fft2pt(float *ioptr)
{
  // Extract the two complex numbers
  // c0 = (ioptr[0], ioptr[1])
  // c1 = (ioptr[2], ioptr[3])
  float f0r = ioptr[0];
  float f0i = ioptr[1];
  float f1r = ioptr[2];
  float f1i = ioptr[3];

  // Compute the 2-point FFT
  // X0 = c0 + c1
  ioptr[0] = f0r + f1r;
  ioptr[1] = f0i + f1i;

  // X1 = c0 - c1
  ioptr[2] = f0r - f1r;
  ioptr[3] = f0i - f1i;
}
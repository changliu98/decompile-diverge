void fft2pt(float *ioptr)
{
  float f0r; float f0i; float f1r; float f1i; float f1ra;
  f0r = ioptr[0];
  f0i = ioptr[1];
  f1r = ioptr[2];
  f1i = ioptr[3];
  f1ra = f0r - f1r;
  ioptr[0] = f0r + f1r;
  ioptr[1] = f0i + f1i;
  ioptr[2] = f1ra;
  ioptr[3] = f0i - f1i;
}
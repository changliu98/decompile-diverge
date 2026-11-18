void ifft2d(float *ioptr, float scale)
{
  float t0i;
  float f0r; float f0i;
  float f1r; float f1i;
  t0i = ioptr[1];
  f1r = 2.0 * ioptr[2];
  f1i = 2.0 * ioptr[3];
  f0r = ioptr[0] + t0i;
  f0i = ioptr[0] - t0i;
  ioptr[0] = scale * (f0r + f1r);
  ioptr[1] = scale * (f0i - f1i);
  ioptr[2] = scale * (f0r - f1r);
  ioptr[3] = scale * (f0i + f1i);
}
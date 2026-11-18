void rifft2pt(float *ioptr, float scale)
{
  float t0i = ioptr[1];
  float f1r = 2 * ioptr[2];
  float f1i = 2 * ioptr[3];
  float f0r = ioptr[0] + t0i;
  float f0i = ioptr[0] - t0i;
  ioptr[0] = scale * (f0r + f1r);
  ioptr[1] = scale * (f0i - f1i);
  ioptr[2] = scale * (f0r - f1r);
  ioptr[3] = scale * (f0i + f1i);
}
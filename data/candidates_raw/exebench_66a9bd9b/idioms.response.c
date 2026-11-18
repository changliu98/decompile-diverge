void ifft1d(float *ioptr)
{
  float t1r; float t1i; float t0r; float t0i;
  float f1r; float f1i; float f2r; float f2i; float f3r; float f3i;
  float f1ra; float f1ia; float f2ra; float f2ia;
  f1r = ioptr[4];
  f1i = ioptr[5];
  f2r = ioptr[2];
  f2i = ioptr[3];
  f3r = ioptr[6];
  f3i = ioptr[7];
  t0r = ioptr[0] + f1r;
  t0i = ioptr[1] + f1i;
  f1ra = ioptr[0] - f1r;
  f1ia = ioptr[1] - f1i;
  t1r = f2r - f3r;
  t1i = f2i - f3i;
  f2ra = f2r + f3r;
  f2ia = f2i + f3i;
  ioptr[0] = t0r + f2ra;
  ioptr[1] = t0i + f2ia;
  ioptr[2] = t1i + f1ra;
  ioptr[3] = -t1r + f1ia;
  ioptr[4] = t0r - f2ra;
  ioptr[5] = t0i - f2ia;
  ioptr[6] = t1i - f1ra;
  ioptr[7] = t1r + f1ia;
}
void fft2pt(float *ioptr)

{
  float fVar1;
  float fVar2;
  float t0i;
  float t0r;
  float f1i;
  float f1r;
  float f0i;
  float f0r;
  float *ioptr_local;
  
  fVar1 = *ioptr;
  fVar2 = ioptr[1];
  *ioptr = fVar1 + ioptr[2];
  ioptr[1] = fVar2 + ioptr[3];
  ioptr[2] = fVar1 - ioptr[2];
  ioptr[3] = fVar2 - ioptr[3];
  return;
}
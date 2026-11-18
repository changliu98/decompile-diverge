void ifft2pt(float *ioptr,float scale)

{
  float fVar1;
  float fVar2;
  float t0i;
  float t0r;
  float f1i;
  float f1r;
  float f0i;
  float f0r;
  float scale_local;
  float *ioptr_local;
  
  fVar1 = *ioptr;
  fVar2 = ioptr[1];
  *ioptr = scale * (fVar1 + ioptr[2]);
  ioptr[1] = scale * (fVar2 + ioptr[3]);
  ioptr[2] = scale * (fVar1 - ioptr[2]);
  ioptr[3] = scale * (fVar2 - ioptr[3]);
  return;
}
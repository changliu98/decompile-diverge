void rifft1pt(float *ioptr,float scale)

{
  float fVar1;
  float t0i;
  float t0r;
  float f0i;
  float f0r;
  float scale_local;
  float *ioptr_local;
  
  fVar1 = *ioptr;
  *ioptr = scale * (fVar1 + ioptr[1]);
  ioptr[1] = scale * (fVar1 - ioptr[1]);
  return;
}
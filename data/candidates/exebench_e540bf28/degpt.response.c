void rfft1pt(float *ioptr)

{
  float fVar1;
  float t0i;
  float t0r;
  float f0i;
  float f0r;
  float *ioptr_local;
  
  fVar1 = *ioptr;
  *ioptr = fVar1 + ioptr[1];
  ioptr[1] = fVar1 - ioptr[1];
  return;
}
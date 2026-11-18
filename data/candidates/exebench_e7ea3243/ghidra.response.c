void rifft2pt(float *ioptr,float scale)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float Two;
  float t0i;
  float t0r;
  float f1i;
  float f1r;
  float f0i;
  float f0r;
  float scale_local;
  float *ioptr_local;
  
  fVar1 = DAT_00102020 * ioptr[2];
  fVar2 = DAT_00102020 * ioptr[3];
  fVar3 = *ioptr + ioptr[1];
  fVar4 = *ioptr - ioptr[1];
  *ioptr = scale * (fVar3 + fVar1);
  ioptr[1] = scale * (fVar4 - fVar2);
  ioptr[2] = scale * (fVar3 - fVar1);
  ioptr[3] = scale * (fVar4 + fVar2);
  return;
}
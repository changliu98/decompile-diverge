void fft4pt(float *ioptr)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float t1i;
  float t1r;
  float t0i;
  float t0r;
  float f3i;
  float f3r;
  float f2i;
  float f2r;
  float f1i;
  float f1r;
  float f0i;
  float f0r;
  float *ioptr_local;
  
  fVar1 = *ioptr + ioptr[4];
  fVar2 = ioptr[1] + ioptr[5];
  fVar3 = *ioptr - ioptr[4];
  fVar4 = ioptr[1] - ioptr[5];
  fVar5 = ioptr[2] - ioptr[6];
  fVar6 = ioptr[3] - ioptr[7];
  fVar7 = ioptr[2] + ioptr[6];
  fVar8 = ioptr[3] + ioptr[7];
  *ioptr = fVar1 + fVar7;
  ioptr[1] = fVar2 + fVar8;
  ioptr[2] = fVar3 + fVar6;
  ioptr[3] = fVar4 - fVar5;
  ioptr[4] = fVar1 - fVar7;
  ioptr[5] = fVar2 - fVar8;
  ioptr[6] = fVar3 - fVar6;
  ioptr[7] = fVar4 + fVar5;
  return;
}
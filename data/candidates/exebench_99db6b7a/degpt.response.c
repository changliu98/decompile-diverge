void ifft4pt(float *ioptr,float scale)

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
  float scale_local;
  float *ioptr_local;
  
  fVar1 = *ioptr + ioptr[4];
  fVar2 = ioptr[1] + ioptr[5];
  fVar3 = *ioptr - ioptr[4];
  fVar4 = ioptr[1] - ioptr[5];
  fVar5 = ioptr[2] - ioptr[6];
  fVar6 = ioptr[3] - ioptr[7];
  fVar7 = ioptr[2] + ioptr[6];
  fVar8 = ioptr[3] + ioptr[7];
  *ioptr = scale * (fVar1 + fVar7);
  ioptr[1] = scale * (fVar2 + fVar8);
  ioptr[2] = scale * (fVar3 - fVar6);
  ioptr[3] = scale * (fVar4 + fVar5);
  ioptr[4] = scale * (fVar1 - fVar7);
  ioptr[5] = scale * (fVar2 - fVar8);
  ioptr[6] = scale * (fVar3 + fVar6);
  ioptr[7] = scale * (fVar4 - fVar5);
  return;
}
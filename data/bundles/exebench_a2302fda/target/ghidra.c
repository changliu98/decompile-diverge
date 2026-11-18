void mdct_butterfly_8(float *x)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float r3;
  float r2;
  float r1;
  float r0;
  float *x_local;
  
  fVar1 = x[6];
  fVar2 = x[6];
  fVar3 = x[4];
  fVar4 = *x;
  x[6] = fVar1 + x[2] + x[4] + *x;
  x[4] = (fVar1 + x[2]) - (x[4] + *x);
  fVar1 = x[3];
  *x = (fVar2 - x[2]) + (x[5] - x[1]);
  x[2] = (fVar2 - x[2]) - (x[5] - x[1]);
  fVar2 = x[1];
  fVar5 = x[7];
  fVar6 = x[3];
  x[3] = (x[7] - fVar1) + (fVar3 - fVar4);
  x[1] = (x[7] - fVar1) - (fVar3 - fVar4);
  x[7] = fVar5 + fVar6 + x[5] + fVar2;
  x[5] = (fVar5 + fVar6) - (x[5] + fVar2);
  return;
}
void cftf040(float *a)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float x3i;
  float x3r;
  float x2i;
  float x2r;
  float x1i;
  float x1r;
  float x0i;
  float x0r;
  float *a_local;
  
  fVar1 = *a;
  fVar2 = a[1];
  fVar3 = *a;
  fVar4 = a[4];
  fVar5 = a[1];
  fVar6 = a[5];
  fVar7 = a[2];
  fVar8 = a[3];
  fVar9 = a[2];
  fVar10 = a[6];
  fVar11 = a[3];
  *a = fVar1 + a[4] + fVar7 + a[6];
  a[1] = fVar2 + a[5] + fVar8 + a[7];
  a[2] = (fVar3 - fVar4) - (fVar11 - a[7]);
  a[3] = (fVar5 - fVar6) + (fVar9 - fVar10);
  a[4] = (fVar1 + a[4]) - (fVar7 + a[6]);
  a[5] = (fVar2 + a[5]) - (fVar8 + a[7]);
  a[6] = (fVar3 - fVar4) + (fVar11 - a[7]);
  a[7] = (fVar5 - fVar6) - (fVar9 - fVar10);
  return;
}
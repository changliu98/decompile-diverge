void OsdGetBoxSplineWeights(float v,float w,float *wP)

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
  int i;
  float w4;
  float w3;
  float w2;
  float v4;
  float v3;
  float v2;
  float u4;
  float u3;
  float u2;
  float u;
  float *wP_local;
  float w_local;
  float v_local;
  
  fVar1 = (DAT_0010203c - v) - w;
  fVar2 = fVar1 * fVar1;
  fVar3 = fVar1 * fVar2;
  fVar4 = fVar1 * fVar3;
  fVar5 = v * v;
  fVar6 = v * fVar5;
  fVar7 = v * fVar6;
  fVar8 = w * w;
  fVar9 = w * fVar8;
  fVar10 = w * fVar9;
  *wP = DAT_00102038 * fVar3 * v + fVar4;
  wP[1] = DAT_00102038 * fVar3 * w + fVar4;
  wP[8] = DAT_00102038 * fVar9 * fVar1 + fVar10;
  wP[0xb] = DAT_00102038 * fVar9 * v + fVar10;
  wP[9] = DAT_00102038 * fVar6 * w + fVar7;
  wP[5] = DAT_00102038 * fVar6 * fVar1 + fVar7;
  wP[2] = DAT_00102028 * fVar5 * fVar1 * w +
          DAT_00102028 * fVar6 * fVar1 +
          DAT_00102038 * fVar6 * w +
          DAT_00102020 * fVar2 * fVar5 +
          DAT_00102028 * fVar2 * v * w + DAT_00102028 * fVar3 * v + DAT_00102038 * fVar3 * w + fVar4
          + fVar7;
  wP[4] = DAT_00102028 * fVar2 * v * w +
          DAT_00102028 * fVar3 * w +
          DAT_00102038 * fVar3 * v +
          DAT_00102020 * fVar8 * fVar2 +
          DAT_00102028 * fVar8 * fVar1 * v +
          DAT_00102028 * fVar9 * fVar1 + DAT_00102038 * fVar9 * v + fVar10 + fVar4;
  wP[10] = DAT_00102028 * fVar9 * fVar1 * v +
           DAT_00102028 * fVar9 * v +
           DAT_00102038 * fVar9 * fVar1 +
           DAT_00102020 * fVar5 * fVar8 +
           DAT_00102028 * fVar5 * w * fVar1 +
           DAT_00102028 * fVar6 * w + DAT_00102038 * fVar6 * fVar1 + fVar7 + fVar10;
  wP[3] = DAT_00102020 * fVar5 * fVar8 +
          DAT_00102024 * fVar2 * v * w +
          fVar4 * DAT_00102028 +
          DAT_0010202c * w * fVar3 +
          DAT_0010202c * fVar8 * fVar2 +
          DAT_00102030 * fVar8 * v * fVar1 +
          DAT_00102034 * fVar9 * fVar1 +
          DAT_00102028 * fVar9 * v +
          DAT_0010202c * v * fVar3 +
          DAT_0010202c * fVar5 * fVar2 +
          DAT_00102030 * fVar5 * w * fVar1 +
          DAT_00102034 * fVar6 * fVar1 + DAT_00102028 * fVar6 * w + fVar7 + fVar10;
  wP[6] = DAT_00102020 * fVar8 * fVar2 +
          DAT_00102024 * fVar5 * w * fVar1 +
          fVar7 * DAT_00102028 +
          DAT_0010202c * fVar1 * fVar6 +
          DAT_0010202c * fVar2 * fVar5 +
          DAT_00102030 * fVar2 * v * w +
          DAT_00102034 * fVar3 * v +
          DAT_00102028 * fVar3 * w +
          DAT_0010202c * w * fVar6 +
          DAT_0010202c * fVar8 * fVar5 +
          DAT_00102030 * fVar8 * fVar1 * v +
          DAT_00102034 * fVar9 * v + DAT_00102028 * fVar9 * fVar1 + fVar10 + fVar4;
  wP[7] = DAT_00102020 * fVar2 * fVar5 +
          DAT_00102024 * fVar8 * fVar1 * v +
          fVar10 * DAT_00102028 +
          DAT_0010202c * v * fVar9 +
          DAT_0010202c * fVar5 * fVar8 +
          DAT_00102030 * fVar5 * fVar1 * w +
          DAT_00102034 * fVar6 * w +
          DAT_00102028 * fVar6 * fVar1 +
          DAT_0010202c * fVar1 * fVar9 +
          DAT_0010202c * fVar2 * fVar8 +
          DAT_00102030 * fVar2 * v * w + DAT_00102034 * fVar3 * w + DAT_00102028 * fVar3 * v + fVar4
          + fVar7;
  for (i = 0; i < 0xc; i = i + 1) {
    wP[i] = DAT_00102040 * wP[i];
  }
  return;
}
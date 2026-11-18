void xformMultiply(float *t,float *s)

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
  float t4;
  float t2;
  float t0;
  float *s_local;
  float *t_local;
  
  fVar1 = *s;
  fVar2 = t[1];
  fVar3 = s[2];
  fVar4 = *s;
  fVar5 = t[3];
  fVar6 = s[2];
  fVar7 = *s;
  fVar8 = t[5];
  fVar9 = s[2];
  fVar10 = s[4];
  t[1] = *t * s[1] + t[1] * s[3];
  t[3] = t[2] * s[1] + t[3] * s[3];
  t[5] = t[4] * s[1] + t[5] * s[3] + s[5];
  *t = *t * fVar1 + fVar2 * fVar3;
  t[2] = t[2] * fVar4 + fVar5 * fVar6;
  t[4] = t[4] * fVar7 + fVar8 * fVar9 + fVar10;
  return;
}
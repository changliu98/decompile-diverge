void normalize_quat(float *q)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float mag;
  int i;
  float *q_local;
  
  fVar1 = *q;
  fVar2 = *q;
  fVar3 = q[1];
  fVar4 = q[1];
  fVar5 = q[2];
  fVar6 = q[2];
  fVar7 = q[3];
  fVar8 = q[3];
  for (i = 0; i < 4; i = i + 1) {
    q[i] = q[i] / (fVar7 * fVar8 + fVar5 * fVar6 + fVar1 * fVar2 + fVar3 * fVar4);
  }
  return;
}
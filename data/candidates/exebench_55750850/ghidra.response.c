void rotate_point(float *point)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float sin_phi;
  float cos_phi;
  float sin_theta;
  float cos_theta;
  float temp [3];
  float *point_local;
  
  fVar3 = DAT_00102008;
  fVar2 = DAT_00102004;
  fVar1 = *point;
  fVar6 = point[2] * DAT_0010200c;
  fVar4 = point[1] * DAT_00102010;
  fVar5 = point[1] * DAT_0010200c + point[2] * DAT_00102010;
  *point = fVar1 * DAT_00102008 + -(fVar5 * DAT_00102004);
  point[1] = fVar4 + -fVar6;
  point[2] = fVar1 * fVar2 + fVar5 * fVar3;
  return;
}
void mat3f_rotateQuatVec_new(float *matrix,float *quat)

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
  float zz;
  float yz;
  float yy;
  float xz;
  float xy;
  float xx;
  float wz;
  float wy;
  float wx;
  float zs;
  float ys;
  float xs;
  float s;
  int W;
  int Z;
  int Y;
  int X;
  float *quat_local;
  float *matrix_local;
  
  fVar7 = (float)(DAT_00102010 /
                 (double)(quat[3] * quat[3] + quat[2] * quat[2] + *quat * *quat + quat[1] * quat[1])
                 );
  fVar8 = quat[1] * fVar7;
  fVar9 = quat[2] * fVar7;
  fVar10 = quat[3] * *quat * fVar7;
  fVar1 = quat[3];
  fVar2 = quat[3];
  fVar11 = *quat * *quat * fVar7;
  fVar7 = *quat;
  fVar3 = *quat;
  fVar4 = quat[1];
  fVar5 = quat[1];
  fVar6 = quat[2];
  *matrix = (float)(DAT_00102008 - (double)(fVar4 * fVar8 + fVar6 * fVar9));
  matrix[3] = fVar7 * fVar8 - fVar2 * fVar9;
  matrix[6] = fVar3 * fVar9 + fVar1 * fVar8;
  matrix[1] = fVar7 * fVar8 + fVar2 * fVar9;
  matrix[4] = (float)(DAT_00102008 - (double)(fVar11 + fVar6 * fVar9));
  matrix[7] = fVar5 * fVar9 - fVar10;
  matrix[2] = fVar3 * fVar9 - fVar1 * fVar8;
  matrix[5] = fVar5 * fVar9 + fVar10;
  matrix[8] = (float)(DAT_00102008 - (double)(fVar11 + fVar4 * fVar8));
  return;
}
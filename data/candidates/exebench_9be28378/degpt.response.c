void mat3d_rotateQuatVec_new(double *matrix,double *quat)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double zz;
  double yz;
  double yy;
  double xz;
  double xy;
  double xx;
  double wz;
  double wy;
  double wx;
  double zs;
  double ys;
  double xs;
  double s;
  int W;
  int Z;
  int Y;
  int X;
  double *quat_local;
  double *matrix_local;
  
  dVar7 = DAT_00102010 / (quat[3] * quat[3] + quat[2] * quat[2] + *quat * *quat + quat[1] * quat[1])
  ;
  dVar8 = quat[1] * dVar7;
  dVar9 = quat[2] * dVar7;
  dVar10 = quat[3] * *quat * dVar7;
  dVar1 = quat[3];
  dVar2 = quat[3];
  dVar11 = *quat * *quat * dVar7;
  dVar7 = *quat;
  dVar3 = *quat;
  dVar4 = quat[1];
  dVar5 = quat[1];
  dVar6 = quat[2];
  *matrix = DAT_00102008 - (dVar4 * dVar8 + dVar6 * dVar9);
  matrix[3] = dVar7 * dVar8 - dVar2 * dVar9;
  matrix[6] = dVar3 * dVar9 + dVar1 * dVar8;
  matrix[1] = dVar7 * dVar8 + dVar2 * dVar9;
  matrix[4] = DAT_00102008 - (dVar11 + dVar6 * dVar9);
  matrix[7] = dVar5 * dVar9 - dVar10;
  matrix[2] = dVar3 * dVar9 - dVar1 * dVar8;
  matrix[5] = dVar5 * dVar9 + dVar10;
  matrix[8] = DAT_00102008 - (dVar11 + dVar4 * dVar8);
  return;
}
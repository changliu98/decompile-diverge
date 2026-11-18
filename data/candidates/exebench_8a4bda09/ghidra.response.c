void rsQuat_toMat(float *q,float *mat)

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
  float *mat_local;
  float *q_local;
  
  if ((((*q != 0.0) || (NAN(*q))) || (q[1] != 0.0)) ||
     (((NAN(q[1]) || (q[2] != 0.0)) || (NAN(q[2]))))) {
    fVar7 = DAT_00102008 / (q[3] * q[3] + q[2] * q[2] + *q * *q + q[1] * q[1]);
    fVar8 = q[1] * fVar7;
    fVar9 = q[2] * fVar7;
    fVar10 = q[3] * *q * fVar7;
    fVar1 = q[3];
    fVar2 = q[3];
    fVar11 = *q * *q * fVar7;
    fVar7 = *q;
    fVar3 = *q;
    fVar4 = q[1];
    fVar5 = q[1];
    fVar6 = q[2];
    *mat = (DAT_00102004 - fVar4 * fVar8) - fVar6 * fVar9;
    mat[1] = fVar7 * fVar8 + fVar2 * fVar9;
    mat[2] = fVar3 * fVar9 - fVar1 * fVar8;
    mat[3] = 0.0;
    mat[4] = fVar7 * fVar8 - fVar2 * fVar9;
    mat[5] = (DAT_00102004 - fVar11) - fVar6 * fVar9;
    mat[6] = fVar5 * fVar9 + fVar10;
    mat[7] = 0.0;
    mat[8] = fVar3 * fVar9 + fVar1 * fVar8;
    mat[9] = fVar5 * fVar9 - fVar10;
    mat[10] = (DAT_00102004 - fVar11) - fVar4 * fVar8;
    mat[0xb] = 0.0;
    mat[0xc] = 0.0;
    mat[0xd] = 0.0;
    mat[0xe] = 0.0;
    mat[0xf] = DAT_00102004;
  }
  else {
    *mat = DAT_00102004;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;
    mat[4] = 0.0;
    mat[5] = DAT_00102004;
    mat[6] = 0.0;
    mat[7] = 0.0;
    mat[8] = 0.0;
    mat[9] = 0.0;
    mat[10] = DAT_00102004;
    mat[0xb] = 0.0;
    mat[0xc] = 0.0;
    mat[0xd] = 0.0;
    mat[0xe] = 0.0;
    mat[0xf] = DAT_00102004;
  }
  return;
}
void Mat4_RotateQuaternion(float *mat,float *q)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float buf [4];
  float *v;
  float qt [4];
  float *q_local;
  float *mat_local;
  
  fVar2 = -*q;
  fVar3 = -q[1];
  fVar4 = -q[2];
  fVar1 = q[3];
  fVar6 = -q[2] * mat[1] + q[1] * mat[2] + q[3] * *mat + *q * mat[3];
  fVar7 = -*q * mat[2] + q[2] * *mat + q[3] * mat[1] + q[1] * mat[3];
  fVar8 = -q[1] * *mat + *q * mat[1] + q[3] * mat[2] + q[2] * mat[3];
  fVar9 = -q[2] * mat[2] + -q[1] * mat[1] + q[3] * mat[3] + -(*q * *mat);
  *mat = -fVar8 * fVar3 + fVar7 * fVar4 + fVar9 * fVar2 + fVar6 * fVar1;
  mat[1] = -fVar6 * fVar4 + fVar8 * fVar2 + fVar9 * fVar3 + fVar7 * fVar1;
  mat[2] = -fVar7 * fVar2 + fVar6 * fVar3 + fVar9 * fVar4 + fVar8 * fVar1;
  mat[3] = -fVar8 * fVar4 + -fVar7 * fVar3 + fVar9 * fVar1 + -(fVar6 * fVar2);
  mat[3] = 0.0;
  pfVar5 = mat + 4;
  fVar6 = -q[2] * mat[5] + q[1] * mat[6] + q[3] * *pfVar5 + *q * mat[7];
  fVar7 = -*q * mat[6] + q[2] * *pfVar5 + q[3] * mat[5] + q[1] * mat[7];
  fVar8 = -q[1] * *pfVar5 + *q * mat[5] + q[3] * mat[6] + q[2] * mat[7];
  fVar9 = -q[2] * mat[6] + -q[1] * mat[5] + q[3] * mat[7] + -(*q * *pfVar5);
  *pfVar5 = -fVar8 * fVar3 + fVar7 * fVar4 + fVar9 * fVar2 + fVar6 * fVar1;
  mat[5] = -fVar6 * fVar4 + fVar8 * fVar2 + fVar9 * fVar3 + fVar7 * fVar1;
  mat[6] = -fVar7 * fVar2 + fVar6 * fVar3 + fVar9 * fVar4 + fVar8 * fVar1;
  mat[7] = -fVar8 * fVar4 + -fVar7 * fVar3 + fVar9 * fVar1 + -(fVar6 * fVar2);
  mat[7] = 0.0;
  pfVar5 = mat + 8;
  fVar6 = -q[2] * mat[9] + q[1] * mat[10] + q[3] * *pfVar5 + *q * mat[0xb];
  fVar7 = -*q * mat[10] + q[2] * *pfVar5 + q[3] * mat[9] + q[1] * mat[0xb];
  fVar8 = -q[1] * *pfVar5 + *q * mat[9] + q[3] * mat[10] + q[2] * mat[0xb];
  fVar9 = -q[2] * mat[10] + -q[1] * mat[9] + q[3] * mat[0xb] + -(*q * *pfVar5);
  *pfVar5 = -fVar8 * fVar3 + fVar7 * fVar4 + fVar9 * fVar2 + fVar6 * fVar1;
  mat[9] = -fVar6 * fVar4 + fVar8 * fVar2 + fVar9 * fVar3 + fVar7 * fVar1;
  mat[10] = -fVar7 * fVar2 + fVar6 * fVar3 + fVar9 * fVar4 + fVar8 * fVar1;
  mat[0xb] = -fVar8 * fVar4 + -fVar7 * fVar3 + fVar9 * fVar1 + -(fVar6 * fVar2);
  mat[0xb] = 0.0;
  return;
}
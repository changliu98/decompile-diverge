void ml_multiply_mat2_mat2(float *mat_a,float *mat_b,float *out)

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
  float fVar12;
  float temp [4];
  float *out_local;
  float *mat_b_local;
  float *mat_a_local;
  
  fVar1 = *mat_a;
  fVar2 = mat_b[1];
  fVar3 = mat_a[1];
  fVar4 = mat_b[3];
  fVar5 = mat_a[2];
  fVar6 = *mat_b;
  fVar7 = mat_a[3];
  fVar8 = mat_b[2];
  fVar9 = mat_a[2];
  fVar10 = mat_b[1];
  fVar11 = mat_a[3];
  fVar12 = mat_b[3];
  *out = *mat_a * *mat_b + mat_a[1] * mat_b[2];
  out[1] = fVar1 * fVar2 + fVar3 * fVar4;
  out[2] = fVar5 * fVar6 + fVar7 * fVar8;
  out[3] = fVar9 * fVar10 + fVar11 * fVar12;
  return;
}
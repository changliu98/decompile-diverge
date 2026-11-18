void Mat4_vec3_mul_T(float *v,float *mat,float *src)

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
  float fVar13;
  float fVar14;
  float ret [3];
  float *src_local;
  float *mat_local;
  float *v_local;
  
  fVar1 = mat[4];
  fVar2 = *src;
  fVar3 = mat[5];
  fVar4 = src[1];
  fVar5 = mat[6];
  fVar6 = src[2];
  fVar7 = mat[7];
  fVar8 = mat[8];
  fVar9 = *src;
  fVar10 = mat[9];
  fVar11 = src[1];
  fVar12 = mat[10];
  fVar13 = src[2];
  fVar14 = mat[0xb];
  *v = mat[2] * src[2] + *mat * *src + mat[1] * src[1] + mat[3];
  v[1] = fVar5 * fVar6 + fVar1 * fVar2 + fVar3 * fVar4 + fVar7;
  v[2] = fVar12 * fVar13 + fVar8 * fVar9 + fVar10 * fVar11 + fVar14;
  return;
}
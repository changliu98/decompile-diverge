void Mat4_vec3_mul_inv(float *v,float *mat,float *src)

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
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
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
  fVar7 = mat[4];
  fVar8 = mat[0xc];
  fVar9 = mat[5];
  fVar10 = mat[0xd];
  fVar11 = mat[6];
  fVar12 = mat[0xe];
  fVar13 = mat[8];
  fVar14 = *src;
  fVar15 = mat[9];
  fVar16 = src[1];
  fVar17 = mat[10];
  fVar18 = src[2];
  fVar19 = mat[8];
  fVar20 = mat[0xc];
  fVar21 = mat[9];
  fVar22 = mat[0xd];
  fVar23 = mat[10];
  fVar24 = mat[0xe];
  *v = (mat[2] * src[2] + *mat * *src + mat[1] * src[1]) -
       (mat[2] * mat[0xe] + *mat * mat[0xc] + mat[1] * mat[0xd]);
  v[1] = (fVar5 * fVar6 + fVar1 * fVar2 + fVar3 * fVar4) -
         (fVar11 * fVar12 + fVar7 * fVar8 + fVar9 * fVar10);
  v[2] = (fVar17 * fVar18 + fVar13 * fVar14 + fVar15 * fVar16) -
         (fVar23 * fVar24 + fVar19 * fVar20 + fVar21 * fVar22);
  return;
}
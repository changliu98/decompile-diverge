void Mat4_affine_inv(float *mat)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float v [3];
  float *mat_local;
  
  fVar1 = mat[1];
  mat[1] = mat[4];
  mat[4] = fVar1;
  fVar1 = mat[2];
  mat[2] = mat[8];
  mat[8] = fVar1;
  fVar1 = mat[6];
  mat[6] = mat[9];
  mat[9] = fVar1;
  fVar1 = mat[0xc];
  fVar2 = mat[0xc];
  fVar3 = mat[0xd];
  mat[0xc] = -(mat[8] * mat[0xe] + *mat * mat[0xc] + mat[4] * mat[0xd]);
  mat[0xd] = -(mat[9] * mat[0xe] + mat[1] * fVar1 + mat[5] * mat[0xd]);
  mat[0xe] = -(mat[10] * mat[0xe] + mat[2] * fVar2 + mat[6] * fVar3);
  return;
}
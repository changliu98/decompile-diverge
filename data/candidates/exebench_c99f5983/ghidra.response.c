void Mat4_T(float *mat)

{
  float fVar1;
  float t;
  float *mat_local;
  
  fVar1 = mat[1];
  mat[1] = mat[4];
  mat[4] = fVar1;
  fVar1 = mat[2];
  mat[2] = mat[8];
  mat[8] = fVar1;
  fVar1 = mat[3];
  mat[3] = mat[0xc];
  mat[0xc] = fVar1;
  fVar1 = mat[6];
  mat[6] = mat[9];
  mat[9] = fVar1;
  fVar1 = mat[7];
  mat[7] = mat[0xd];
  mat[0xd] = fVar1;
  fVar1 = mat[0xb];
  mat[0xb] = mat[0xe];
  mat[0xe] = fVar1;
  return;
}
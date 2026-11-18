void Mat4_Translate(float *mat,float *v)

{
  float *v_local;
  float *mat_local;
  
  mat[0xc] = mat[8] * v[2] + *mat * *v + mat[4] * v[1] + mat[0xc];
  mat[0xd] = mat[9] * v[2] + mat[1] * *v + mat[5] * v[1] + mat[0xd];
  mat[0xe] = mat[10] * v[2] + mat[2] * *v + mat[6] * v[1] + mat[0xe];
  return;
}
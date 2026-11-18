void __cdecl Mat4_Translate(float *mat, const float *v)
{
  mat[12] = (float)((float)(mat[8] * v[2]) + (float)((float)(*mat * *v) + (float)(mat[4] * v[1]))) + mat[12];
  mat[13] = (float)((float)(mat[9] * v[2]) + (float)((float)(mat[1] * *v) + (float)(mat[5] * v[1]))) + mat[13];
  mat[14] = (float)((float)(mat[10] * v[2]) + (float)((float)(mat[2] * *v) + (float)(mat[6] * v[1]))) + mat[14];
}
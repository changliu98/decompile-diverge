void __cdecl Mat4_Translate(float *mat, const float *v)
{
  float x = v[0];
  float y = v[1];
  float z = v[2];

  mat[12] += mat[0] * x + mat[4] * y + mat[8]  * z;
  mat[13] += mat[1] * x + mat[5] * y + mat[9]  * z;
  mat[14] += mat[2] * x + mat[6] * y + mat[10] * z;
}
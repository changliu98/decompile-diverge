void __cdecl Mat4_vec3_mul(float *v, const float *mat, const float *src)
{
  // Calculate the X component
  v[0] = mat[0] * src[0] + mat[4] * src[1] + mat[8]  * src[2] + mat[12];

  // Calculate the Y component
  v[1] = mat[1] * src[0] + mat[5] * src[1] + mat[9]  * src[2] + mat[13];

  // Calculate the Z component
  v[2] = mat[2] * src[0] + mat[6] * src[1] + mat[10] * src[2] + mat[14];
}
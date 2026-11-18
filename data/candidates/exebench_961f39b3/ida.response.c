void __cdecl Mat4_vec3_mul_T(float *v, float *mat, float *src)
{
  float ret_4; // [rsp+4h] [rbp-20h]
  float ret_8; // [rsp+8h] [rbp-1Ch]

  ret_4 = (float)((float)(mat[6] * src[2]) + (float)((float)(mat[4] * *src) + (float)(mat[5] * src[1]))) + mat[7];
  ret_8 = (float)((float)(mat[10] * src[2]) + (float)((float)(mat[8] * *src) + (float)(mat[9] * src[1]))) + mat[11];
  *v = (float)((float)(mat[2] * src[2]) + (float)((float)(*mat * *src) + (float)(mat[1] * src[1]))) + mat[3];
  v[1] = ret_4;
  v[2] = ret_8;
}
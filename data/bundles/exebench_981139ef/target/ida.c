void __cdecl Mat4_vec3_mul(float *v, const float *mat, const float *src)
{
  float ret_4; // [rsp+4h] [rbp-20h]
  float ret_8; // [rsp+8h] [rbp-1Ch]

  ret_4 = (float)((float)(mat[9] * src[2]) + (float)((float)(mat[1] * *src) + (float)(mat[5] * src[1]))) + mat[13];
  ret_8 = (float)((float)(mat[10] * src[2]) + (float)((float)(mat[2] * *src) + (float)(mat[6] * src[1]))) + mat[14];
  *v = (float)((float)(mat[8] * src[2]) + (float)((float)(*mat * *src) + (float)(mat[4] * src[1]))) + mat[12];
  v[1] = ret_4;
  v[2] = ret_8;
}
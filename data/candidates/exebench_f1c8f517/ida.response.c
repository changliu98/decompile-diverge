void __cdecl ml_multiply_mat4_vec4(float *mat, float *vec, float *out)
{
  float temp_4; // [rsp+4h] [rbp-2Ch]
  float temp_8; // [rsp+8h] [rbp-28h]
  float temp_12; // [rsp+Ch] [rbp-24h]

  temp_4 = (float)(mat[7] * vec[3])
         + (float)((float)(mat[6] * vec[2]) + (float)((float)(mat[4] * *vec) + (float)(mat[5] * vec[1])));
  temp_8 = (float)(mat[11] * vec[3])
         + (float)((float)(mat[10] * vec[2]) + (float)((float)(mat[8] * *vec) + (float)(mat[9] * vec[1])));
  temp_12 = (float)(mat[15] * vec[3])
          + (float)((float)(mat[14] * vec[2]) + (float)((float)(mat[12] * *vec) + (float)(mat[13] * vec[1])));
  *out = (float)(mat[3] * vec[3])
       + (float)((float)(mat[2] * vec[2]) + (float)((float)(*mat * *vec) + (float)(mat[1] * vec[1])));
  out[1] = temp_4;
  out[2] = temp_8;
  out[3] = temp_12;
}
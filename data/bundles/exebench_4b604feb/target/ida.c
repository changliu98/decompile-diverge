void __cdecl ml_multiply_mat2_mat2(float *mat_a, float *mat_b, float *out)
{
  float temp_4; // [rsp+4h] [rbp-2Ch]
  float temp_8; // [rsp+8h] [rbp-28h]
  float temp_12; // [rsp+Ch] [rbp-24h]

  temp_4 = (float)(*mat_a * mat_b[1]) + (float)(mat_a[1] * mat_b[3]);
  temp_8 = (float)(mat_a[2] * *mat_b) + (float)(mat_a[3] * mat_b[2]);
  temp_12 = (float)(mat_a[2] * mat_b[1]) + (float)(mat_a[3] * mat_b[3]);
  *out = (float)(*mat_a * *mat_b) + (float)(mat_a[1] * mat_b[2]);
  out[1] = temp_4;
  out[2] = temp_8;
  out[3] = temp_12;
}
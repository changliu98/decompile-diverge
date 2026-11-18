void __cdecl ml_multiply_mat4_mat4(float *mat_a, float *mat_b, float *out)
{
  // Row 0
  out[0]  = mat_a[0] * mat_b[0]  + mat_a[1] * mat_b[4]  + mat_a[2] * mat_b[8]  + mat_a[3] * mat_b[12];
  out[1]  = mat_a[0] * mat_b[1]  + mat_a[1] * mat_b[5]  + mat_a[2] * mat_b[9]  + mat_a[3] * mat_b[13];
  out[2]  = mat_a[0] * mat_b[2]  + mat_a[1] * mat_b[6]  + mat_a[2] * mat_b[10] + mat_a[3] * mat_b[14];
  out[3]  = mat_a[0] * mat_b[3]  + mat_a[1] * mat_b[7]  + mat_a[2] * mat_b[11] + mat_a[3] * mat_b[15];

  // Row 1
  out[4]  = mat_a[4] * mat_b[0]  + mat_a[5] * mat_b[4]  + mat_a[6] * mat_b[8]  + mat_a[7] * mat_b[12];
  out[5]  = mat_a[4] * mat_b[1]  + mat_a[5] * mat_b[5]  + mat_a[6] * mat_b[9]  + mat_a[7] * mat_b[13];
  out[6]  = mat_a[4] * mat_b[2]  + mat_a[5] * mat_b[6]  + mat_a[6] * mat_b[10] + mat_a[7] * mat_b[14];
  out[7]  = mat_a[4] * mat_b[3]  + mat_a[5] * mat_b[7]  + mat_a[6] * mat_b[11] + mat_a[7] * mat_b[15];

  // Row 2
  out[8]  = mat_a[8] * mat_b[0]  + mat_a[9] * mat_b[4]  + mat_a[10] * mat_b[8]  + mat_a[11] * mat_b[12];
  out[9]  = mat_a[8] * mat_b[1]  + mat_a[9] * mat_b[5]  + mat_a[10] * mat_b[9]  + mat_a[11] * mat_b[13];
  out[10] = mat_a[8] * mat_b[2]  + mat_a[9] * mat_b[6]  + mat_a[10] * mat_b[10] + mat_a[11] * mat_b[14];
  out[11] = mat_a[8] * mat_b[3]  + mat_a[9] * mat_b[7]  + mat_a[10] * mat_b[11] + mat_a[11] * mat_b[15];

  // Row 3
  out[12] = mat_a[12] * mat_b[0] + mat_a[13] * mat_b[4] + mat_a[14] * mat_b[8]  + mat_a[15] * mat_b[12];
  out[13] = mat_a[12] * mat_b[1] + mat_a[13] * mat_b[5] + mat_a[14] * mat_b[9]  + mat_a[15] * mat_b[13];
  out[14] = mat_a[12] * mat_b[2] + mat_a[13] * mat_b[6] + mat_a[14] * mat_b[10] + mat_a[15] * mat_b[14];
  out[15] = mat_a[12] * mat_b[3] + mat_a[13] * mat_b[7] + mat_a[14] * mat_b[11] + mat_a[15] * mat_b[15];
}
void ml_multiply_mat2_mat2(float *mat_a, float *mat_b, float *out)
{
  float temp1 = (mat_a[0]*mat_b[1]) + (mat_a[1]*mat_b[3]);
  float temp2 = (mat_a[2]*mat_b[0]) + (mat_a[3]*mat_b[2]);
  float temp3 = (mat_a[2]*mat_b[1]) + (mat_a[3]*mat_b[3]);
  out[0] = (mat_a[0]*mat_b[0]) + (mat_a[1]*mat_b[2]);
  out[1] = temp1;
  out[2] = temp2;
  out[3] = temp3;
  return;
}
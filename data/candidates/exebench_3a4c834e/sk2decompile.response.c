static void drmp3_L3_idct3(float x0, float x1, float x2, float *out) {
  float x0_plus_x2 = x0 + x2 * 0.5f;
  float x0_minus_x2 = x0 - x2 * 0.5f;
  out[0] = x0_plus_x2 + 0.86602539f * x1;
  out[1] = x0 + x2;
  out[2] = x0_minus_x2 + 0.86602539f * x1;
}
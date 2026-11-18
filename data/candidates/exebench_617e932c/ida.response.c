void __cdecl parabolic_interpolation(
        float left_val,
        float middle_val,
        float right_val,
        int current_bin,
        float *result_val,
        int *result_bin)
{
  float v6; // xmm0_4
  float v7; // xmm0_4

  v6 = 0.5
     * (float)((float)(left_val - right_val) / (float)((float)(left_val - (float)(middle_val + middle_val)) + right_val));
  *result_bin = (int)v6 + current_bin;
  v7 = -(0.25 * (float)(left_val - right_val)) * v6 + middle_val;
  *result_val = v7;
}
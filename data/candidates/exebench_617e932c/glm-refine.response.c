void __cdecl parabolic_interpolation(
        float left_val,
        float middle_val,
        float right_val,
        int current_bin,
        float *result_val,
        int *result_bin)
{
  // Calculate the fractional bin offset (p)
  float delta_bin = 0.5f * (left_val - right_val) / (left_val - 2.0f * middle_val + right_val);
  
  // Update the bin index by adding the fractional offset to the current bin
  *result_bin = current_bin + (int)delta_bin;
  
  // Calculate the interpolated peak value
  *result_val = middle_val - 0.25f * (left_val - right_val) * delta_bin;
}
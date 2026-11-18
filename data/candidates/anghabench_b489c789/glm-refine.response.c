void __cdecl update16(uint16_t *value, int threshold, int step, int clamp_value)
{
  // If the value exceeds the threshold, cap it at clamp_value.
  // Otherwise, increment it by step.
  if (*value > threshold)
  {
    *value = clamp_value;
  }
  else
  {
    *value += step;
  }
}
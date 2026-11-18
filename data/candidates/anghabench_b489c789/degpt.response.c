void update16(uint16_t *value, int max_value, int step, int upper_bound)
{
  // If the current target value exceeds the maximum allowed value
  if (max_value < (int)(uint)*value) {
    // Clamp the target to the specified limit
    *value = (uint16_t)upper_bound;
  }
  else {
    // Otherwise, increment the target by the intensity value
    *value = *value + (short)step;
  }
}
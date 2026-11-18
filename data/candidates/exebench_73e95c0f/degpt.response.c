/**
 * Clamps a value to a specified range [a_min, a_max].
 *
 * @param a_pValue Pointer to the value to be clamped.
 * @param a_min    The minimum allowed value.
 * @param a_max    The maximum allowed value.
 */
void clamp(double *value, double min, double max)
{
  // If the value is less than the minimum, set it to the minimum.
  if (min > *value) {
    *value = min;
  } 
  // If the value is greater than the maximum, set it to the maximum.
  else if (max < *value) {
    *value = max;
  }
}
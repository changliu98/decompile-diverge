// Clamps the value x to the range [min, max]
float clamp(float value, float lower_bound, float upper_bound)
{
  // If x is less than the minimum, return the minimum value
  if (value < lower_bound) return lower_bound;
  // If x is greater than the maximum, return the maximum value
  if (value > upper_bound) return upper_bound;
  // Otherwise, return x as it is within the valid range
  return value;
}
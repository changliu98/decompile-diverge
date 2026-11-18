// Scales a long integer value by a multiplication factor and division factor.
// Implements rounding to the nearest integer using the "round half up" strategy.
// Parameters:
//   val - The input value to be scaled.
//   mul - The numerator multiplier.
//   div - The denominator divisor.
// Returns:
//   The scaled result as an integer, rounded to the nearest whole number.
int SCALE(long value,int multiplier,int divisor)
{
  // Handle negative values: subtract half the divisor before division to achieve rounding.
  if (value < 0) {
    // For negative numbers, subtracting (div/2) before integer division effectively rounds towards zero.
    return (int)((value * multiplier - (long)(divisor / 2)) / (long)divisor);
  }
  else {
    // For non-negative values, adding (div/2) before integer division achieves standard rounding to nearest.
    return (int)((value * multiplier + (long)(divisor / 2)) / (long)divisor);
  }
}
// Function to calculate the product of two floats, cast to double for precision,
// then multiplied by a constant and cast back to float.
float func0(float value1, float value2)
{
  // Multiply a and h, cast to double to maintain precision during multiplication
  // with the constant, then cast the result back to float.
  return (float)((double)(value1 * value2) * constant_factor);
}
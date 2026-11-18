// Calculates a value based on the input integer n
// Computes the product of n, n+1, and n+2
// Divides the result by a constant value (DAT_00102008)
// Returns the result as a double-precision floating-point number
double func0(int input_value)
{
  // Cast the integer result to double before division to ensure floating-point arithmetic
  return (double)(input_value * (input_value + 1) (input_value + 2)) / constant_divisor;
}
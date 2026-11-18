// Function to compute the square of a non-negative integer, or return -1 if the input is negative.
int func0(int input_value)
{
  // If r is negative, return -1; otherwise, return the square of r.
  return input_value < 0 ? -1 : input_value * input_value;
}
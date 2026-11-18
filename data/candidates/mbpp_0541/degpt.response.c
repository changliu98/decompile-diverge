// Function to check if the double representation of n is less than the sum of n
int isDoubleLessThanSum(int value)
{
  // Cast n to double and compare with the result of get_sum(n)
  // Return 1 if the condition is true, 0 otherwise
  return (uint)((double)value < get_sum(value));
}
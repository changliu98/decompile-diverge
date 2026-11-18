int func0(int lower_bound, int upper_bound)
{
  // Ensure m is less than or equal to n by swapping if necessary
  if (upper_bound < lower_bound) {
    int swap_temp = lower_bound;
    lower_bound = upper_bound;
    upper_bound = swap_temp;
  }
  // Calculate and return the result using the formula
  return (upper_bound * (upper_bound + 1) * ((lower_bound * 3 - upper_bound) + 1)) / 6;
}
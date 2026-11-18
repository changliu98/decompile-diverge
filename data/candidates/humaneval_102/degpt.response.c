int func0(int lower_bound, int upper_bound)
{
  // Return -1 if y is less than x, or if y equals x and y is odd.
  if (upper_bound < lower_bound || (upper_bound == lower_bound && upper_bound % 2 == 1)) {
    return -1;
  }
  // Return the largest even number less than or equal to y.
  return upper_bound - (upper_bound % 2);
}
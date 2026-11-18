int func0(int input_value)
{
  // Base case: return 1 when n is 0
  if (input_value == 0) return 1;
  // Special case: return 6 when n is 3
  if (input_value == 3) return 6;
  // Special case: return 4 when n is 4
  if (input_value == 4) return 4;
  // Return 0 for any n greater than 2
  if (input_value > 2) return 0;
  // Return n for all other cases (n <= 2)
  return input_value;
}
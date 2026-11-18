double calculate_recursive_sum(int input_number) {
  // Base case: if n is less than 2, return the constant value DAT_00102008
  if (input_number < 2) {
    return constant_value;
  }
  // Recursive case: return DAT_00102008 divided by n plus the result of func0(n - 1)
  return constant_value / (double)input_number + calculate_recursive_sum(input_number - 1);
}
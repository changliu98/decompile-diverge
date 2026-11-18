const char *__cdecl func0(const int *seq_nums, int n)
{
  // If the sequence has 2 or fewer elements, it's trivially linear
  if (n <= 2) {
    return "Linear Sequence";
  }

  // Compute the difference between the first two elements
  int first_diff = seq_nums[1] - seq_nums[0];

  // Check if all subsequent differences match the first difference
  for (int i = 2; i < n; ++i) {
    if (seq_nums[i] - seq_nums[i - 1] != first_diff) {
      return "Non Linear Sequence";
    }
  }

  return "Linear Sequence";
}
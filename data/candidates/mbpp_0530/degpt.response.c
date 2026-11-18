double func0(int *nums, int n)
{
  int negative_count = 0; // Counter for negative numbers
  for (int index = 0; index < n; index++) {
    if (nums[index] < 0) { // Check if the current number is negative
      negative_count++; // Increment the counter for negative numbers
    }
  }
  // Calculate the ratio of negative numbers to total numbers, round it, and divide by a constant
  return round(CONSTANT * ((double)negative_count / (double)n)) / CONSTANT;
}
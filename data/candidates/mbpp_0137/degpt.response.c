double func0(int *nums, int n)
{
  int zero_count = 0; // Counter for zero elements
  for (int index = 0; index < n; index++) {
    if (nums[index] == 0) { // Check if current element is zero
      zero_count++; // Increment counter if element is zero
    }
  }
  // Calculate ratio of zeros to total elements, round to nearest multiple of DAT_00102008, then divide by DAT_00102008
  return round(rounding_precision * ((double)zero_count / (double)n)) / rounding_precision;
}
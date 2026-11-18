double func0(int *nums,int n)
{
  int positiveCount = 0; // Initialize counter for positive numbers
  for (int index = 0; index < n; index++) {
    if (nums[index] > 0) { // Check if current number is positive
      positiveCount++; // Increment counter if positive
    }
  }
  // Calculate ratio of positive numbers, round to nearest multiple of 1/DAT_00102008, then divide by DAT_00102008
  return round(roundingFactor * ((double)positiveCount / (double)n)) / roundingFactor;
}
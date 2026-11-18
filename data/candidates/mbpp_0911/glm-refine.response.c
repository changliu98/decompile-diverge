int __cdecl func0(int *nums, int size)
{
  int temp;
  int j;
  int i;

  // Edge case: require at least 3 elements to form a triplet product
  if (size < 3)
    return -1;

  // Sort the array in descending order using Selection Sort
  for (i = 0; i < size - 1; ++i)
  {
    for (j = i + 1; j < size; ++j)
    {
      if (nums[i] < nums[j])
      {
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
      }
    }
  }

  // After sorting:
  // nums[0], nums[1], nums[2] are the three largest numbers.
  // nums[size - 1], nums[size - 2] are the two smallest numbers (potentially negative).
  
  int max_positive_triplet = nums[0] * nums[1] * nums[2];
  int max_mixed_triplet = nums[size - 1] * nums[size - 2] * nums[0];

  // Return the maximum of the two possible triplet products
  if (max_positive_triplet <= max_mixed_triplet)
    return max_mixed_triplet;
  else
    return max_positive_triplet;
}
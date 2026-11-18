void __cdecl func0(int *nums, int size)
{
  int i;
  int digit;
  int max_val;
  int placement;
  int *count;
  int *output;

  // Find the maximum value in the array to know the number of digits
  max_val = *nums;
  for (i = 1; i < size; ++i)
  {
    if (nums[i] > max_val)
      max_val = nums[i];
  }

  // Allocate temporary arrays for counting sort and the output
  output = (int *)malloc(4LL * size);
  count = (int *)malloc(0x28uLL); // 40 bytes = 10 * sizeof(int)

  // Radix sort loop (processes each decimal digit)
  placement = 1;
  while (placement <= max_val)
  {
    // 1. Initialize count array (handles digits 0-9)
    for (i = 0; i < 10; ++i)
      count[i] = 0;

    // 2. Store the count of occurrences for the current digit
    for (i = 0; i < size; ++i)
    {
      digit = (nums[i] / placement) % 10;
      ++count[digit];
    }

    // 3. Change count[i] so that it contains the actual position of this digit in output[]
    for (i = 1; i < 10; ++i)
      count[i] += count[i - 1];

    // 4. Build the output array (iterating backwards to maintain stability)
    for (i = size - 1; i >= 0; --i)
    {
      digit = (nums[i] / placement) % 10;
      output[--count[digit]] = nums[i];
    }

    // 5. Copy the sorted array for the current digit back into the original array
    for (i = 0; i < size; ++i)
      nums[i] = output[i];

    // Move to the next decimal place
    placement *= 10;
  }

  // Free dynamically allocated memory
  free(output);
  free(count);
}
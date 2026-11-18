void __cdecl func0(int *nums, int size)
{
  int temp;
  int i;
  int swapped;
  int gap;

  gap = size;
  swapped = 1;

  // Continue while gap is still shrinking, or while swaps still occur
  while (gap > 1 || swapped)
  {
    // Shrink gap by the standard comb-sort factor of 1.3
    // (float cast chain preserved to match original truncation behavior)
    gap = (int)(float)((float)gap / 1.3);

    swapped = 0;

    // Compare and swap elements `gap` apart
    for (i = 0; i + gap < size; ++i)
    {
      if (nums[i] > nums[gap + i])
      {
        temp          = nums[i];
        nums[i]       = nums[gap + i];
        nums[gap + i] = temp;
        swapped = 1;
      }
    }
  }
}
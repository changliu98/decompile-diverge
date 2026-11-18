bool __cdecl func0(int *nums, int size)
{
  // Check if the array is strictly increasing
  for (int i = 0; i < size - 1; ++i)
  {
    if (nums[i] >= nums[i + 1])
      return false;
  }
  return true;
}
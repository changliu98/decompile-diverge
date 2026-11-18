void __cdecl func0(int *nums, int size, int *result)
{
  for (int i = 0; i < size - 1; ++i)
  {
    result[i] = nums[i] + nums[i + 1];
  }
}
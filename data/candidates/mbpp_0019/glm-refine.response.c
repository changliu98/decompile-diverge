bool __cdecl func0(int *nums, int len)
{
  for (int i = 0; i < len; ++i)
  {
    for (int j = i + 1; j < len; ++j)
    {
      if (nums[i] == nums[j])
        return true;
    }
  }
  return false;
}
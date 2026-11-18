bool __cdecl func0(const int *nums, int size)
{
  for (int i = 0; i < size; ++i)
  {
    if ((nums[i] & 1) != (i & 1))
      return false;
  }
  return true;
}
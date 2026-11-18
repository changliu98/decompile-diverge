int __cdecl func0(int *list1, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (list1[i] >= 0)
      return list1[i];
  }
  return -1;
}
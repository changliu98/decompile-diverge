bool __cdecl func0(int *test_tup, int size)
{
  for (int i = 0; i < size; ++i)
  {
    if (test_tup[i] == 0)
      return true;
  }
  return false;
}
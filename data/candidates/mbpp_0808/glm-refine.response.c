bool __cdecl func0(int *test_tup, int n, int K)
{
  for (int i = 0; i < n; ++i)
  {
    if (test_tup[i] == K)
      return true;
  }
  return false;
}
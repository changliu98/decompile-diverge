void __cdecl func0(const int *test_tup, int size, int *result)
{
  // Calculate the adjacent sums of the input array
  for (int i = 0; i < size - 1; ++i)
    result[i] = test_tup[i] + test_tup[i + 1];
}
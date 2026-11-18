// Checks if all elements of test_tup2 are present in test_tup1.
// Returns true if test_tup2 is a subset of test_tup1, false otherwise.
bool __cdecl is_subset(int *test_tup1, int size1, int *test_tup2, int size2)
{
  bool found;

  // Iterate over each element in the second tuple
  for (int i = 0; i < size2; ++i)
  {
    found = false;

    // Check if the current element exists in the first tuple
    for (int j = 0; j < size1; ++j)
    {
      if (test_tup2[i] == test_tup1[j])
      {
        found = true;
        break;
      }
    }

    // If the element was not found, it's not a subset
    if (!found)
      return false;
  }

  return true;
}
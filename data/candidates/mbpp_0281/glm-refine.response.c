// Checks if all elements in the given integer array are unique.
// Returns true (1) if all elements are distinct, false (0) if any duplicates are found.
bool __cdecl has_unique_elements(const int *arr, int length)
{
  int j;
  int i;

  // Iterate through each element in the array, except the last one
  for (i = 0; i < length - 1; ++i)
  {
    // Compare the current element with all subsequent elements
    for (j = i + 1; j < length; ++j)
    {
      // If a duplicate is found, the elements are not all unique
      if (arr[i] == arr[j])
        return false;
    }
  }
  
  // No duplicates were found
  return true;
}
#include <stdbool.h>

// Checks if every element in 'test_tuple' exists in the array 'K'.
// Returns true if 'test_tuple' is a subset of 'K', false otherwise.
bool __cdecl is_subset(int *test_tuple, int tuple_size, int *K, int K_size)
{
  for (int i = 0; i < tuple_size; ++i)
  {
    bool found = false;
    
    for (int j = 0; j < K_size; ++j)
    {
      if (test_tuple[i] == K[j])
      {
        found = true;
        break;
      }
    }
    
    if (!found)
    {
      return false;
    }
  }
  return true;
}
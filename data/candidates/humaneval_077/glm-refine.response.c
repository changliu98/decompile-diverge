#include <stdlib.h> // for abs()

// Checks if a given integer is a perfect cube.
// Returns 1 if true, 0 if false.
int is_perfect_cube(int a)
{
  int target = abs(a);
  
  for (int i = 0; i * i * i <= target; ++i)
  {
    if (i * i * i == target)
      return 1;
  }
  
  return 0;
}
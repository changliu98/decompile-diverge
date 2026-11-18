#include <limits.h>

int __cdecl find_second_smallest(int *lst, int size)
{
  int i;
  int second_smallest = INT_MAX;
  int smallest = INT_MAX;

  // The function requires at least two elements to find a second smallest
  if (size < 2)
    return -1;

  for (i = 0; i < size; ++i)
  {
    if (lst[i] < smallest)
    {
      // New smallest found; the old smallest becomes the second smallest
      second_smallest = smallest;
      smallest = lst[i];
    }
    else if (lst[i] < second_smallest && lst[i] != smallest)
    {
      // Not a new smallest, but smaller than the current second smallest (and not a duplicate)
      second_smallest = lst[i];
    }
  }

  // If second_smallest was never updated, it means no valid second element was found
  if (second_smallest == INT_MAX)
    return -1;
    
  return second_smallest;
}
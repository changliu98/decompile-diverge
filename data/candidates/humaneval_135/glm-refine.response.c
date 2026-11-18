// Finds the index of the last element that is strictly smaller than its preceding element.
// Returns -1 if the array is strictly non-decreasing or has fewer than 2 elements.
int find_last_unsorted_index(int *arr, int size)
{
  int last_index = -1;

  for (int i = 1; i < size; ++i)
  {
    // If the current element is smaller than the previous one, 
    // it breaks the non-decreasing order. We save its index.
    if (arr[i] < arr[i - 1])
    {
      last_index = i;
    }
  }

  return last_index;
}
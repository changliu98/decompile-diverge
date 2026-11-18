int __cdecl func0(int *arr, int size)
{
  int mismatch_count = 0;
  
  // Iterate through the first half of the array
  for (int i = 0; i < size / 2; ++i)
  {
    // Compare the element from the start with its mirror element from the end
    if (arr[i] != arr[size - 1 - i])
    {
      mismatch_count++;
    }
  }
  
  return mismatch_count;
}
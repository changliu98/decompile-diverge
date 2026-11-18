int __cdecl count_occurrences(int *array, int length, int target)
{
  int count = 0;
  
  for (int i = 0; i < length; ++i)
  {
    if (array[i] == target)
      ++count;
  }
  
  return count;
}
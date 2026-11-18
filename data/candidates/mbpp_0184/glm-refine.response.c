// Checks if all elements in the array are greater than or equal to a minimum value.
// Returns true if all elements meet the condition, false otherwise.
bool __cdecl all_elements_ge(const int *list, int count, int min_val)
{
  for (int i = 0; i < count; ++i)
  {
    if (list[i] < min_val)
      return false;
  }
  return true;
}
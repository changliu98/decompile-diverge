void __cdecl find_min_pos_and_max_neg(const int *arr, int size, int *result)
{
  int max_negative = 0;
  int min_positive = 0;

  for (int i = 0; i < size; ++i)
  {
    // Find the maximum negative number (closest to 0)
    if (arr[i] < 0 && (max_negative == 0 || arr[i] > max_negative))
    {
      max_negative = arr[i];
    }
    
    // Find the minimum positive number (closest to 0)
    if (arr[i] > 0 && (min_positive == 0 || arr[i] < min_positive))
    {
      min_positive = arr[i];
    }
  }
  
  // Store the results
  result[0] = max_negative;
  result[1] = min_positive;
}
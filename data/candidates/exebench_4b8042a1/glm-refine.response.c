int __cdecl next_arr_seq(int *arr, int len, int maxval)
{
  for (int i = 0; i < len; ++i)
  {
    // Increment the current element
    arr[i]++;
    
    // If it doesn't exceed the maximum value, the sequence is valid
    if (arr[i] <= maxval)
      return 1;
      
    // Otherwise, wrap around to 0 and carry the increment to the next element
    arr[i] = 0;
  }
  
  // All elements wrapped around; the sequence has fully overflowed
  return 0;
}
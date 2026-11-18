int func0(int *arr,int arr_len,int repetitions)
{
  int idx;
  int current_max;
  int global_max;
  
  // Initialize max_so_far to the minimum possible integer value
  global_max = -0x80000000;
  // Initialize max_ending_here to 0
  current_max = 0;
  // Iterate through k repetitions of the array elements
  for (idx = 0; idx < arr_len * repetitions; idx = idx + 1) {
    // Add the current element (wrapping around the array using modulo)
    current_max = current_max + arr[idx % arr_len];
    // Update max_so_far if the current subarray sum is greater
    if (global_max < current_max) {
      global_max = current_max;
    }
    // Reset max_ending_here to 0 if it becomes negative
    if (current_max < 0) {
      current_max = 0;
    }
  }
  // Return the maximum subarray sum found
  return global_max;
}
int func0(int *arr, int n)
{
  int idx;
  int current_max = 0; // Maximum sum of subarray ending at current position
  int global_max = 0;      // Maximum sum of subarray found so far
  
  for (idx = 0; idx < n; idx = idx + 1) {
    current_max = current_max + arr[idx]; // Add current element to max_ending_here
    if (current_max < 0) {
      current_max = 0; // Reset max_ending_here if it becomes negative
    }
    else if (global_max < current_max) {
      global_max = current_max; // Update max_so_far if max_ending_here is greater
    }
  }
  return global_max; // Return the maximum subarray sum
}
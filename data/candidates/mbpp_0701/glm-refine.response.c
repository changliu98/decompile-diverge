int __cdecl func0(int *arr, int n)
{
  int total_sum = 0;
  
  // Calculate the total sum of the array
  for (int i = 0; i < n; ++i) {
    total_sum += arr[i];
  }

  int left_sum = 0;
  
  // Iterate to find the equilibrium index
  for (int i = 0; i < n; ++i) {
    // Subtract the current element from total_sum to get the right sum
    total_sum -= arr[i];
    
    // If left sum equals right sum, we found the pivot index
    if (left_sum == total_sum) {
      return i;
    }
    
    // Add the current element to left_sum for the next iteration
    left_sum += arr[i];
  }

  // Return -1 if no pivot index is found
  return -1;
}
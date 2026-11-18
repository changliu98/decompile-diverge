int __cdecl func0(int *arr, int n, int k)
{
  int ans = n - 1;
  
  // Sort the array. 
  // Note: The cast to strcmp is likely a decompiler artifact for a 4-byte integer comparator.
  qsort(arr, n, sizeof(int), (__compar_fn_t)&strcmp);
  
  for (int i = 0; i < n; ++i)
  {
    int j = find_ind(arr[i], i, n, k, arr);
    
    if (j != -1)
    {
      // Calculate the number of elements to remove to leave only the subarray [i, j]
      int elements_to_remove = n - (j - i + 1);
      
      // Update the minimum elements to remove (equivalent to the ternary/branch logic)
      if (elements_to_remove < ans)
      {
        ans = elements_to_remove;
      }
    }
  }
  
  return ans;
}
int __cdecl func0(int *a, int n, int k)
{
  int max_ending_here = 0;
  int max_so_far = 0x80000000; // INT_MIN
  int total_elements = k * n;

  for (int i = 0; i < total_elements; ++i)
  {
    // The array 'a' of size 'n' is virtually repeated 'k' times
    max_ending_here += a[i % n];
    
    if (max_ending_here > max_so_far)
      max_so_far = max_ending_here;
      
    // Reset the running sum if it drops below zero
    if (max_ending_here < 0)
      max_ending_here = 0;
  }
  
  return max_so_far;
}
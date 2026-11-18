int __cdecl computesizes(int *nums, int *narray)
{
  int n = 0;
  int na = 0;
  int a = 0;
  int i = 0;

  // twotoi represents powers of 2 (1, 2, 4, 8, ...)
  // The loop continues as long as the previous power of 2 is less than the initial *narray
  for (int twotoi = 1; twotoi / 2 < *narray; twotoi *= 2)
  {
    if (nums[i] > 0)
    {
      a += nums[i];
      
      // If the running total exceeds the previous power of 2, 
      // update the best fit size (n) and the total elements (na)
      if (a > twotoi / 2)
      {
        n = twotoi;
        na = a;
      }
    }
    
    // If the running total matches the initial *narray, we've processed all elements
    if (a == *narray)
      break;
      
    ++i;
  }
  
  // Output the best fit power of 2 size
  *narray = n;
  
  // Return the total number of elements accommodated
  return na;
}
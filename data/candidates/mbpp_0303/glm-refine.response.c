int __cdecl func0(int *a, int n)
{
  int i;
  int max_so_far;

  // Initialize to INT_MIN (0x80000000)
  max_so_far = INT_MIN; 

  for ( i = 1; i < n; ++i )
  {
    // If the current element is less than the maximum value seen before it, 
    // the array is not sorted.
    if ( max_so_far > a[i] )
      return 0;

    // Update the running maximum. We look at a[i - 1] because it is the 
    // element immediately preceding a[i]. By the time we reach index i, 
    // a[i - 1] is guaranteed to be >= max_so_far.
    if ( a[i - 1] > max_so_far )
      max_so_far = a[i - 1];
  }
  return 1;
}
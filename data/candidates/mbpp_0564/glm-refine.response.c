int __cdecl func0(int *arr, int n)
{
  int j;
  int i;
  int unequal_pairs_count;

  unequal_pairs_count = 0;
  
  // Iterate over all unique pairs in the array
  for ( i = 0; i < n; ++i )
  {
    for ( j = i + 1; j < n; ++j )
    {
      // If the elements at the current pair of indices are not equal, increment the counter
      if ( arr[i] != arr[j] )
        ++unequal_pairs_count;
    }
  }
  
  return unequal_pairs_count;
}
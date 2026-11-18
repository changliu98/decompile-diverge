int __cdecl func0(int *arr, int n)
{
  int i;
  int min_count;
  int max_count;
  int count;

  sortArray(arr, n);
  
  count = 0;
  max_count = 0;
  min_count = n;
  
  for ( i = 0; i < n - 1; ++i )
  {
    if ( arr[i] == arr[i + 1] )
    {
      ++count;
    }
    else
    {
      // Update max_count
      if ( count > max_count )
        max_count = count;
        
      // Update min_count
      if ( count < min_count )
        min_count = count;
        
      count = 0;
    }
  }
  
  return max_count - min_count;
}
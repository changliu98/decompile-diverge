int __cdecl find_most_frequent(int *arr, int length)
{
  int j;
  int current_count;
  int i;
  int most_frequent_val;
  int max_count;

  max_count = 0;
  most_frequent_val = arr[0];
  
  for ( i = 0; i < length; ++i )
  {
    current_count = 0;
    for ( j = 0; j < length; ++j )
    {
      if ( arr[j] == arr[i] )
        ++current_count;
    }
    
    // If the current element's frequency is strictly greater than the max recorded
    if ( current_count > max_count )
    {
      max_count = current_count;
      most_frequent_val = arr[i];
    }
  }
  
  return most_frequent_val;
}
int __cdecl func0(int *arr, int n)
{
  int max_count;
  int i;
  int step;
  int j;
  int temp;
  int count;

  // Bubble sort to sort the array in non-decreasing order
  for ( step = 0; step < n - 1; ++step )
  {
    for ( j = 0; j < n - step - 1; ++j )
    {
      if ( arr[j] > arr[j + 1] )
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  // Find the maximum frequency of any element
  max_count = 0;
  for ( i = 0; i < n; ++i )
  {
    count = 1;
    // Count consecutive occurrences of arr[i]
    while ( i + 1 < n && arr[i] == arr[i + 1] )
    {
      ++i;
      ++count;
    }
    if ( max_count < count )
      max_count = count;
  }
  
  return max_count;
}
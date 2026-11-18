int __cdecl func0(int n, int *arr)
{
  int i;
  int freq;
  int min_val;

  // Initialize the minimum value with the first element
  min_val = arr[0];
  freq = 1;

  // Iterate through the array starting from the second element
  for ( i = 1; i < n; ++i )
  {
    if ( arr[i] >= min_val )
    {
      // If the current element matches the minimum, increment the frequency counter
      if ( arr[i] == min_val )
        ++freq;
    }
    else
    {
      // A new minimum is found; update min_val and reset the frequency counter
      min_val = arr[i];
      freq = 1;
    }
  }
  
  // Return the frequency of the minimum element
  return freq;
}
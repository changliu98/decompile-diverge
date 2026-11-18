int __cdecl func0(int n, int *arr)
{
  if (n <= 0) {
    return 0; // Edge case safety (though original would crash on n=0)
  }

  int max_val = arr[0];
  int max_freq = 1;

  for (int i = 1; i < n; ++i) 
  {
    if (arr[i] > max_val) 
    {
      max_val = arr[i];
      max_freq = 1;
    } 
    else if (arr[i] == max_val) 
    {
      ++max_freq;
    }
  }
  
  return max_freq;
}
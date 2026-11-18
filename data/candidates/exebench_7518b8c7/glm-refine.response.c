int __cdecl max(float *arr)
{
  int max_index = 0;
  float highest = arr[0];

  for (int i = 0; i < 2; ++i)
  {
    if (arr[i] > highest)
    {
      max_index = i;
      highest = arr[i];
    }
  }
  
  return max_index;
}
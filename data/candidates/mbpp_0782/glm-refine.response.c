int __cdecl func0(int *arr, int l)
{
  int Sum = 0;

  for (int i = 0; i < l; ++i)
  {
    // Calculate the weight for the current element
    int weight = (((l - i) * (i + 1)) + 1) / 2;
    
    // Accumulate the weighted value
    Sum += arr[i] * weight;
  }

  return Sum;
}
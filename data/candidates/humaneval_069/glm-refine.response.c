int __cdecl func0(int *lst, int size)
{
  int *freq = (int *)calloc(size + 1, sizeof(int));
  int max = -1;

  for (int i = 0; i < size; ++i)
  {
    int val = lst[i];
    freq[val]++;

    // If the current value's frequency has reached the value itself,
    // and it's greater than the current max, update max.
    if (freq[val] >= val && val > max)
    {
      max = val;
    }
  }

  free(freq);
  return max;
}
int func0(int *array, int n)
{
  int oddPair = 0;
  int i = 0;
  int j = 0;
  for (i = 0; i < n; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if ((array[j] ^ array[i]) % 2)
      {
        oddPair++;
      }
    }
  }
  return oddPair;
}
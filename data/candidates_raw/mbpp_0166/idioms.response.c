int getEvenPairs(int *array, int n)
{
  int evenPair = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if ((array[j] ^ array[i]) % 2 == 0)
      {
        evenPair++;
      }
    }
  }
  return evenPair;
}
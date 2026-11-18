float func0(int *array1, int *array2, int n)
{
  int i = 0;
  int j = 0;
  int prev = -1;
  int current = -1;
  int count = 0;
  while (count < n + 1)
  {
    count++;
    if (i == n)
    {
      prev = current;
      current = array2[0];
      return (prev + current)/2.0;
    }
    if (j == n)
    {
      prev = current;
      current = array1[0];
      return (prev + current)/2.0;
    }
    prev = current;
    if (array1[i] <= array2[j])
    {
      current = array1[i];
      i++;
    }
    else
    {
      current = array2[j];
      j++;
    }
  }
  return (prev + current)/2.0;
}
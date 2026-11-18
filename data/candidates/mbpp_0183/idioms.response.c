int func0(int *array, int n, int k)
{
  int count = 0;
  int i = 0; int j = 0;
  for(i = 0; i < n; i++)
  {
    for(j = i+1; j < n; j++)
    {
      if((array[i]-array[j]) == k || (array[j]-array[i]) == k)
      {
        count++;
      }
    }
  }
  return count;
}
int getRange(int a[], int n)
{
  int i; int count; int max_count; int min_count;
  int temp;
  sortArray(a, n);
  count = 0;
  max_count = 0;
  min_count = n;
  for (i = 0; i < n - 1; i++)
  {
    if (a[i] == a[i + 1])
    {
      count++;
    }
    else
    {
      if (count < max_count)
      {
        temp = max_count;
      }
      else
      {
        temp = count;
      }
      max_count = temp;
      if (count < min_count)
      {
        temp = min_count;
      }
      else
      {
        temp = count;
      }
      min_count = temp;
      count = 0;
    }
  }
  return max_count - min_count;
}
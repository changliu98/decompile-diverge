int func0(int *array, int n)
{
  int i; int j;
  int temp;
  for (i = 0; i < n; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (array[i] > array[j])
      {
        temp = array[j];
        array[j] = array[i];
        array[i] = temp;
      }
    }
  }
  for (i = n - 1; i >= 0; i--)
  {
    if (is_palindrome(array[i]) == 1)
    {
      return array[i];
    }
  }
  return -1;
}
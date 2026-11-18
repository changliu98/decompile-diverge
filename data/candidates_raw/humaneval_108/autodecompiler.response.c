int findNumbers(int array[], int n)
{
  int num = 0, i, j, k, l;

  for (i = 0; i < n; ++i)
  {
    if (array[i] > 0)
      ++num;
    else
    {
      int sum = 0, temp = abs(array[i]);

      while (temp >= 10)
      {
        sum += temp % 10;
        temp /= 10;
      }

      sum -= temp;

      if (sum > 0)
        ++num;
    }
  }

  return num;
}
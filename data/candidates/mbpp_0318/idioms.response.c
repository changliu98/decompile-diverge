int func0(int n)
{
  int max = 0;
  int i; int j; int k;
  for (i = 1; i < n - 1; i++)
    for (j = 1; j < n; j++)
      if ((k = n - i - j) > 0)
        if (i * j * k > max)
          max = i * j * k;
  return max;
}
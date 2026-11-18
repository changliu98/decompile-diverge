int *get_array(int n)
{
  int *out = (int*)malloc(n * sizeof(int));
  int sum = 0;
  int prod = 1;
  int i;
  for (i = 1; i <= n; i++)
  {
    sum += i;
    prod *= i;
    if (i % 2 == 0)
    {
      out[i - 1] = prod;
    }
    else
    {
      out[i - 1] = sum;
    }
  }
  return out;
}
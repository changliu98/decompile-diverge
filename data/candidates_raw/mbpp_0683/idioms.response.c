int is_sum_of_two_squares(int n)
{
  int i; int j;
  for (i = 1; i * i <= n; i++)
    for (j = 1; j * j <= n; j++)
      if (i * i + j * j == n)
        return 1;
  return 0;
}
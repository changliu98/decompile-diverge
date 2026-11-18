char **func0(char **a, int na, char **b, int nb)
{
  int i;
  int sum_a = 0;
  int sum_b = 0;
  for (i = 0; i < na; i++)
    sum_a += strlen(a[i]);
  for (i = 0; i < nb; i++)
    sum_b += strlen(b[i]);
  if (sum_a < sum_b)
    return (a);
  if (sum_a > sum_b)
    return (b);
  return (a);
}
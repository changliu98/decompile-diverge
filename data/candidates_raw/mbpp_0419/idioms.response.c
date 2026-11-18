int get_sum(double *list, int length)
{
  int i; int sum = 0;
  for (i = 0; i < length; i++)
    sum += round(list[i]);
  return (length * sum);
}
int is_in_box(float *lb, float *ub, int n)
{
  int i;
  if (lb == ((void *)0) || ub == ((void *)0))
    return 1;
  for (i = 0; i < n; i++)
    if (lb[i] > ub[i])
      return 0;
  return 1;
}
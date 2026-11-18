int __cdecl slevmar_box_check(float *lb, float *ub, int m)
{
  if (!lb || !ub)
    return 1;

  for (int i = 0; i < m; ++i)
  {
    if (lb[i] > ub[i])
      return 0;
  }

  return 1;
}
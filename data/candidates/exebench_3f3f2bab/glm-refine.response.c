int __cdecl sboxCHECK(float *lb, float *ub, int m)
{
  // Return 1 (failure/error) if either pointer is null
  if (!lb || !ub)
    return 1;

  // Return 0 (failure) if any lower bound exceeds its corresponding upper bound
  for (int i = 0; i < m; ++i)
  {
    if (lb[i] > ub[i])
      return 0;
  }

  // Return 1 (success) if all bounds are valid
  return 1;
}
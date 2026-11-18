int __cdecl func0(int l1, int r1, int l2, int r2, int *x, int *y)
{
  // If l1 and l2 are equal, assign -1. Otherwise, assign the minimum of the two.
  *x = (l1 == l2) ? -1 : (l1 < l2 ? l1 : l2);

  // If r1 and r2 are equal, assign -1. Otherwise, assign the maximum of the two.
  *y = (r1 == r2) ? -1 : (r1 > r2 ? r1 : r2);

  return 0;
}
int __cdecl func0(int x, int y)
{
  // If y is a divisor of x, then y is the greatest common divisor
  if (x % y == 0)
    return y;

  // Iterate downwards from y / 2 to 1 to find the largest common divisor
  for (int k = y / 2; k > 0; --k)
  {
    if (x % k == 0 && y % k == 0)
      return k;
  }

  // Fallback to 1 if no larger common divisor was found
  return 1;
}
bool __cdecl func0(int x)
{
  int digits[100];
  int num_digits = 0;

  // Extract decimal digits of x, least-significant first
  for (int temp = x; temp > 0; temp /= 10)
    digits[num_digits++] = temp % 10;

  // Reverse the array so digits are most-significant first
  for (int lo = 0, hi = num_digits - 1; lo < hi; ++lo, --hi)
  {
    int t = digits[lo];
    digits[lo] = digits[hi];
    digits[hi] = t;
  }

  // Generate successive terms of the Keith sequence by summing the
  // last num_digits terms, stopping once we reach or exceed x.
  int next = 0;
  int i = num_digits;
  while (next < x)
  {
    next = 0;
    for (int j = 1; j <= num_digits; ++j)
      next += digits[i - j];
    digits[i++] = next;
  }

  return next == x;
}
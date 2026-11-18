int __cdecl func0(int x, int y)
{
  // Determine the maximum of the two inputs to use as a starting point
  int z = (x > y) ? x : y;

  // Increment z until it is perfectly divisible by both x and y
  while (z % x != 0 || z % y != 0)
    ++z;

  return z;
}
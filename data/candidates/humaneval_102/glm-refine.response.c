int __cdecl func0(int x, int y)
{
  // Return -1 if y is strictly less than x, 
  // or if y equals x and is odd.
  if (y < x || (y == x && (y % 2 == 1)))
    return -1;

  // If y is odd, return y - 1. Otherwise, return y.
  return (y % 2 == 1) ? y - 1 : y;
}
// Returns true if at least two of the three integers x, y, and z are equal.
_Bool func0(int first, int second, int third)
{
  // Check if x equals y, or y equals z, or z equals x.
  return (first == second) || (second == third) || (third == first);
}
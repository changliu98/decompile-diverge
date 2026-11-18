int __cdecl func0(int n)
{
  // Computes the remainder of n divided by 10, effectively extracting the least significant decimal digit.
  // Note: For negative values of n, the result will have the same sign as n (e.g., -23 % 10 == -3).
  return n % 10;
}
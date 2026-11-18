int __cdecl func0(int n)
{
  // Computes the sum of squares of the first n odd integers: 1^2 + 3^2 + 5^2 + ... + (2n-1)^2
  // Algebraically equivalent to n * (4n^2 - 1) / 3
  return n * (4 * n * n - 1) / 3;
}
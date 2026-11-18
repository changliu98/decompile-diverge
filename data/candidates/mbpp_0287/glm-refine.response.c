int __cdecl func0(int n)
{
  // Computes the sum of squares: 1^2 + 2^2 + 3^2 + ... + n^2
  // Algebraically equivalent to: n * (n + 1) * (2n + 1) / 6
  return n * (n + 1) * (2 * n + 1) / 6;
}
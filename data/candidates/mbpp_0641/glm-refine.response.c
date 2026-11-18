int __cdecl func0(int n)
{
  // Computes the sum of an arithmetic progression:
  // Sum = n * (a1 + an) / 2
  // where a1 = 1 (first term) and an = 7n - 6 (nth term)
  // Resulting in: n * (1 + 7n - 6) / 2 = n * (7n - 5) / 2
  return n * (7 * n - 5) / 2;
}
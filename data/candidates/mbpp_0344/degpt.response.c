// Calculates the number of perfect squares in the range [n, m]
// by computing the difference between the integer square roots of m and n-1
int countPerfectSquares(int start, int end)
{
  // Cast m to double for sqrt, then cast result to int to get floor(sqrt(m))
  // Subtract floor(sqrt(n-1)) to count perfect squares in [n, m]
  return (int)sqrt((double)end) - (int)sqrt((double)(start - 1));
}
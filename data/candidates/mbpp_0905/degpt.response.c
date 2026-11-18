// Computes the ratio of factorial(n+1, 2n) to factorial(1, n)
int func0(int limit)
{
  // Returns the result of dividing factorial(n+1, n << 1) by factorial(1, n)
  return factorial(limit + 1, limit << 1) / factorial(1, limit);
}
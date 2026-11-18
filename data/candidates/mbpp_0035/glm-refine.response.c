/**
 * @brief Calculates the pronic number for a given integer n.
 * A pronic number is the product of two consecutive integers (n * (n + 1)).
 * It is also mathematically equivalent to twice the n-th triangular number.
 * 
 * @param n The input integer.
 * @return int The pronic number of n.
 */
int __cdecl calc_pronic_number(int n)
{
  // (n + 1) * n is preserved exactly to avoid altering integer overflow behavior 
  // that might occur if refactored to (n * n) + n.
  return (n + 1) * n;
}
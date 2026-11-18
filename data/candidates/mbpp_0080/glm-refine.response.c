#include <stdint.h>

/**
 * @brief Calculates the nth tetrahedral number.
 * 
 * Mathematically, this computes the binomial coefficient C(n + 2, 3),
 * which is equivalent to the sum of the first n triangular numbers.
 * Formula: n * (n + 1) * (n + 2) / 6
 * 
 * @param n The index of the tetrahedral number.
 * @return double The nth tetrahedral number.
 * 
 * @note The multiplication is performed using 32-bit signed integer arithmetic.
 *       Integer overflow will occur for large values of n (e.g., |n| > 1290) 
 *       before the result is widened and cast to a double. This behavior is 
 *       preserved exactly from the original decompilation.
 */
double __cdecl tetrahedral_number(int32_t n)
{
  return (double)((n + 2) * (n + 1) * n) / 6.0;
}
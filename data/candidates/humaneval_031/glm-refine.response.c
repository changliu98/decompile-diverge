#include <cstdint>

// Checks if a 64-bit integer is a prime number
bool is_prime(int64_t n)
{
  int64_t divisor;

  // Numbers less than 2 are not prime
  if (n < 2)
    return false;

  // Check for factors up to the square root of n
  for (divisor = 2; divisor * divisor <= n; ++divisor)
  {
    // If n is evenly divisible by 'divisor', it is not prime
    if (n % divisor == 0)
      return false;
  }

  return true;
}
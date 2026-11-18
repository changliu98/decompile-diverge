#include <math.h>

// Function checks if a number is composite (not prime).
// Returns: 1 if a divisor is found (composite), 0 otherwise (prime or n <= 1).
// Note: The original control flow does not break early after finding a divisor, 
// so this semantics is strictly preserved.
int __cdecl is_not_prime(int n)
{
  int found_divisor = 0;

  for (int divisor = 2; divisor <= (int)sqrt((double)n); ++divisor)
  {
    if (n % divisor == 0)
    {
      found_divisor = 1;
    }
  }

  return found_divisor;
}
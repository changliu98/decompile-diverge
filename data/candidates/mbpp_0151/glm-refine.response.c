#include <stdbool.h>

// Checks if x and y are coprime (relatively prime)
bool __cdecl is_coprime(int x, int y)
{
  return gcd(x, y) == 1;
}
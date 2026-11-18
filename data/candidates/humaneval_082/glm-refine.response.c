#include <stdbool.h>
#include <string.h>

bool is_string_length_prime(const char *str)
{
  int length = strlen(str);
  
  // 0 and 1 are not prime numbers
  if (length < 2)
    return false;
    
  // Check for factors from 2 up to the square root of the length
  for (int i = 2; i * i <= length; ++i)
  {
    if (length % i == 0)
      return false;
  }
  
  return true;
}
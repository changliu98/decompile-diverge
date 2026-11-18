#include <math.h>

// Calculates the sum of divisors of 'n'
int __cdecl sum_of_divisors(int n)
{
  int sum_of_powers; // [rsp+8h] [rbp-18h]
  int prime_power;   // [rsp+Ch] [rbp-14h]
  int power_count;   // [rsp+10h] [rbp-10h]
  int i;             // [rsp+14h] [rbp-Ch]
  int total_sum;     // [rsp+18h] [rbp-8h]

  total_sum = 1;
  
  // Remove all factors of 2
  while (n % 2 == 0)
    n /= 2;
    
  // Check for odd factors up to sqrt(n)
  // Replaced `sqrt((double)n) + 1.0 >= (double)i` with integer arithmetic `i * i <= n`
  for (i = 3; i * i <= n; i += 2)
  {
    power_count = 0;
    sum_of_powers = 1;
    prime_power = 1;
    
    while (n % i == 0)
    {
      ++power_count;
      n /= i;
      prime_power *= i;
      sum_of_powers += prime_power;
    }
    total_sum *= sum_of_powers;
  }
  
  // If n is a prime number greater than 2
  if (n >= 2)
    total_sum *= n + 1;
    
  return total_sum;
}
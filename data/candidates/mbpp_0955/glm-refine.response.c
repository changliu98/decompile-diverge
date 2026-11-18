// This function checks if a given integer 'n' is an abundant number.
// An abundant number is a number for which the sum of its proper divisors 
// (excluding the number itself) is greater than the number.
// Returns 1 (true) if 'n' is abundant, otherwise returns 0 (false).
int __cdecl is_abundant(int n)
{
  int divisor;        // [rsp+0h] [rbp-Ch]  // Current divisor being checked
  int divisor_sum;    // [rsp+4h] [rbp-8h]  // Sum of proper divisors

  divisor_sum = 0;
  
  // Iterate from 1 up to n-1 to find all proper divisors
  for ( divisor = 1; divisor < n; ++divisor )
  {
    // If 'divisor' evenly divides 'n', it is a proper divisor
    if ( !(n % divisor) )
      divisor_sum += divisor;
  }
  
  // The number is abundant if the sum of its proper divisors is greater than itself
  return divisor_sum > n;
}
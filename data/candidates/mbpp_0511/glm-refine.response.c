// This function calculates the sum of the prime factors of a given integer `num`.
// For example, if num = 12, the prime factors are 2, 2, and 3. The function returns 2 + 2 + 3 = 7.
// If `num` is a prime number itself, it simply returns `num`.
int __cdecl sum_of_prime_factors(int num)
{
  int factor; // [rsp+0h] [rbp-Ch] - Current potential prime factor
  int sum;    // [rsp+4h] [rbp-8h] - Accumulator for the sum of prime factors

  sum = 0;
  
  // Check for factors starting from 2 up to the square root of `num`.
  // We use `factor * factor <= num` to avoid needing a square root function.
  for ( factor = 2; factor * factor <= num; ++factor )
  {
    // While `factor` evenly divides `num`, it is a prime factor.
    // We repeatedly divide it out to ensure we only capture prime factors.
    while ( !(num % factor) )
    {
      sum += factor;
      num /= factor;
    }
  }
  
  // If `num` is still greater than 1 after the loop, it means the remaining 
  // `num` is a prime number itself and must be included in the sum.
  // (If the original `num` was 1, this will correctly add 0 + 1 = 1, although 1 is not prime).
  return sum + num;
}
// Function to calculate the sum of prime factors of num
int calculatePrimeFactorSum(int number)
{
  int primeFactorSum = 0;
  // Iterate from 2 up to the square root of num
  for (int factor = 2; factor * factor <= number; factor++) {
    // While i divides num, add i to sum and divide num by i
    for (; number % factor == 0; number /= factor) {
      primeFactorSum += factor;
    }
  }
  // If num > 1, then the remaining num is a prime factor
  return number + primeFactorSum;
}
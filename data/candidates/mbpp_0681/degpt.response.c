int func0(int number)
{
  // Check if n is even; if so, return 2 as the smallest divisor
  if (number % 2 == 0) {
    return 2;
  }
  // Iterate through odd numbers starting from 3 up to sqrt(n)
  for (int divisor = 3; divisor * divisor <= number; divisor += 2) {
    // If i divides n, return i as the smallest odd divisor
    if (number % divisor == 0) {
      return divisor;
    }
  }
  // If no divisor is found, n is prime; return n itself
  return number;
}
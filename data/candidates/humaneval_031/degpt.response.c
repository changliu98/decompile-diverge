// Checks if the given number is a prime number.
_Bool func0(longlong number) {
  // Numbers less than 2 are not prime.
  if (number < 2) return false;
  // Iterate from 2 up to the square root of n.
  for (longlong divisor = 2; divisor * divisor <= number; divisor++) {
    // If n is divisible by i, it is not prime.
    if (number % divisor == 0) return false;
  }
  // If no divisors were found, n is prime.
  return true;
}
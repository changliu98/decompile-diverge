// Checks if the given number is a prime number.
_Bool func0(int number)
{
  // Numbers less than 1 are not prime.
  if (number < 1) {
    return false;
  }
  // Check for factors from 2 up to half of the number.
  for (int divisor = 2; divisor <= number / 2; divisor++) {
    // If the number is divisible by i, it is not prime.
    if (number % divisor == 0) {
      return false;
    }
  }
  // If no factors were found, the number is prime.
  return true;
}
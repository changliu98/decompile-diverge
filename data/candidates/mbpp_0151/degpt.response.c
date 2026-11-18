// Function to check if two integers are coprime
// Returns 1 if x and y are coprime (gcd(x, y) == 1), otherwise returns 0
int are_coprime(int numerator, int denominator)
{
  // Compute the greatest common divisor of x and y
  // If gcd(x, y) is 1, then x and y are coprime
  // Cast the boolean result to int: 1 if true, 0 if false
  return (int)(gcd(numerator, denominator) == 1);
}
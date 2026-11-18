int func0(int n)
{
  int divisorCount = 0; // Initialize counter for divisors
  for (int currentNumber = 1; currentNumber <= n; currentNumber++) { // Iterate from 1 to n
    if (n % currentNumber == 0) { // Check if i is a divisor of n
      divisorCount++; // Increment counter if i divides n
    }
  }
  return divisorCount; // Return the total number of divisors
}
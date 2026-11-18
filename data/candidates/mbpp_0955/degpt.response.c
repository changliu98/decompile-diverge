int func0(int n)
{
  int factorSum = 0; // Initialize sum of factors to 0
  for (int factor = 1; factor < n; factor++) { // Iterate through all numbers less than n
    if (n % factor == 0) { // Check if fctr is a factor of n
      factorSum += factor; // Add the factor to the sum
    }
  }
  return n < factorSum; // Return true if n is less than the sum of its proper factors
}
int func0(int inputValue)
{
  // If N is less than 10, compute the factorial of N modulo 100
  if (inputValue < 10) {
    int factorialResult = 1;
    // Calculate factorial iteratively, taking modulo 100 at each step to prevent overflow
    for (int counter = 1; counter <= inputValue; counter++) {
      factorialResult = (factorialResult * counter) % 100;
    }
    return factorialResult;
  }
  // If N is 10 or greater, return 0
  return 0;
}
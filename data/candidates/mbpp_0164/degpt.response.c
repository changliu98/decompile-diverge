// Returns 1 if num1 and num2 have the same number of divisors, otherwise returns 0.
int compareDivisorCounts(int firstNumber, int secondNumber)
{
  // Compare the number of divisors of num1 and num2 using divSum function.
  // Cast the boolean result to int (1 for true, 0 for false).
  return (int)(divSum(firstNumber) == divSum(secondNumber));
}
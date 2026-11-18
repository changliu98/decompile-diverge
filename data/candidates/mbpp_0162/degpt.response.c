// Recursive function that calculates the sum of every other integer from n down to 1 or 0
// For example: func0(5) = 5 + 3 + 1 = 9; func0(4) = 4 + 2 = 6
int sumEveryOtherInteger(int n)
{
  // Base case: if n is less than 1, return 0 to stop recursion
  if (n < 1) {
    return 0;
  }
  // Recursive step: add current n to the result of func0(n - 2)
  return n + sumEveryOtherInteger(n - 2);
}
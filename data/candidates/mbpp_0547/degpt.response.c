int func0(int n)
{
  int total = 0;
  // Iterate through powers of 2 (1, 2, 4, 8, ...) as long as n / i is greater than 0
  for (int powerOfTwo = 1; 0 < n / powerOfTwo; powerOfTwo = powerOfTwo << 1) {
    // Add the integer division of n by the current power of 2 to the sum
    total += n / powerOfTwo;
  }
  return total;
}
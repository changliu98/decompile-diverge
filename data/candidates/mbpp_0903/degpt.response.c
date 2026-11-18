int func0(int n)
{
  int zeroBitCount = 0; // Initialize counter to zero
  for (int number = 1; number <= n; number++) { // Iterate from 1 to n
    for (int currentNumber = number; currentNumber != 0; currentNumber /= 2) { // Process each bit of i by right-shifting
      if (currentNumber % 2 == 0) { // Check if the current least significant bit is 0
        zeroBitCount++; // Increment counter for each zero bit found
      }
    }
  }
  return zeroBitCount; // Return total count of zero bits across all numbers from 1 to n
}
int func0(int limit)
{
  int zeroBitCount = 0;
  // Iterate through powers of 2 (1, 2, 4, 8, ...) up to n
  for (int powerOfTwo = 1; powerOfTwo <= limit; powerOfTwo <<= 1) {
    // Check if the current bit position (represented by x) is 0 in n
    if ((powerOfTwo & limit) == 0) {
      zeroBitCount++;
    }
  }
  // Return the number of zero bits at positions corresponding to powers of 2
  return zeroBitCount;
}
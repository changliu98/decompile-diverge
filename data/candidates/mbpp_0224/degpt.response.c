int func0(int n)
{
  int setBitCount = 0; // Initialize counter for set bits
  for (; n != 0; n = n >> 1) { // Loop until all bits are processed
    setBitCount = (n & 1U) + setBitCount; // Add the least significant bit to count
  }
  return setBitCount; // Return the total number of set bits
}
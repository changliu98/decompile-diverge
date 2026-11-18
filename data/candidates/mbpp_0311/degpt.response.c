int func0(int inputNumber)
{
  // Check if n is not of the form 2^k - 1 (all lower bits set)
  // If (n & (n+1)) != 0, then n does not have all trailing ones
  if ((inputNumber & inputNumber + 1U) != 0) {
    int bitIndex = 0;
    int zeroBitPosition = 0;
    // Iterate through bits of n from LSB to MSB
    for (int currentBitValue = inputNumber; currentBitValue != 0; currentBitValue = currentBitValue >> 1) {
      // If current bit is 0, record its position
      if ((currentBitValue & 1U) == 0) {
        zeroBitPosition = bitIndex;
      }
      bitIndex = bitIndex + 1;
    }
    // Set the rightmost zero bit to 1
    // Cast pos to unsigned char and mask with 0x1f to ensure valid shift amount
    inputNumber = inputNumber | 1 << ((unsigned char)zeroBitPosition & 0x1f);
  }
  return inputNumber;
}
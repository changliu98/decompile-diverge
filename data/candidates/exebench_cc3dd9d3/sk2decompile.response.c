void AssignBit(unsigned long *pulArray, unsigned long ulBit, int fValue) {
  unsigned long ulMask = 1UL << (ulBit & 63);
  unsigned long ulIndex = ulBit >> 6;
  if (fValue)
    pulArray[ulIndex] |= ulMask;
  else
    pulArray[ulIndex] &= ~ulMask;
}
// Sets the bit at position 'bitNum' in the integer pointed to by 'x' to 1.
// The bit position is masked with 0x1f to ensure it stays within the valid range [0, 31].
void SetBitInt(int *targetValue,int bitPosition)
{
  // Create a mask with the bit at position 'bitNum' set to 1, then OR it with the current value of *x.
  *targetValue = 1 << ((byte)bitPosition & 0x1f) | *targetValue;
}
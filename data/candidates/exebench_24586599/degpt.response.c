void set_bit(int *target, int bit_index)
{
  // Set the b-th bit of the integer pointed to by n to 1.
  // 1. Shift 1 left by (b & 0x1f) to create a mask for the b-th bit.
  //    The bitwise AND with 0x1f (31) ensures the shift amount is within 0-31,
  //    preventing undefined behavior for large shift values.
  // 2. Use bitwise OR (|) with the current value of *n to set the bit to 1
  //    without affecting other bits.
  *target = 1 << ((byte)bit_index & 0x1f) | *target;
}
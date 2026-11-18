unsigned int __cdecl and_peep2_qi(unsigned int value, unsigned int *out_ptr)
{
  // Apply a bitmask (0x5F) to the value and store the result via the pointer.
  // 0x5F corresponds to binary 0101 1111, effectively clearing the 7th and 8th bits (0x80 and 0x40).
  *out_ptr = value & 0x5F;
  
  // Return the original value unmodified.
  return value;
}
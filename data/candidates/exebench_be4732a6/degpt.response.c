void bitfield_set(unsigned_long *bit_array, int target_bit)
{
  // Calculate the index of the word containing the bit by dividing bit by 64 (bit >> 6)
  // Set the specific bit within that word using a bitmask (1L << (bit & 0x3f))
  // The mask (bit & 0x3f) extracts the lower 6 bits of 'bit', representing the position within the 64-bit word
  bit_array[target_bit >> 6] |= 1L << (target_bit & 0x3f);
}
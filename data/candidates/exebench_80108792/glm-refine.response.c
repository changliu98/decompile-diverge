void __cdecl bitmap_free(unsigned int *array, int index)
{
  // Calculate which 32-bit element in the array holds the target bit
  int word_index = index / 32;
  
  // Calculate the bit position within that 32-bit element
  int bit_offset = index % 32;
  
  // Create a mask with a 1 at the target bit position, then invert it.
  // (e.g., if bit_offset is 0, mask becomes 0x7FFFFFFF)
  unsigned int mask = ~(0x80000000 >> bit_offset);
  
  // Clear the target bit using a bitwise AND with the inverted mask
  array[word_index] &= mask;
}
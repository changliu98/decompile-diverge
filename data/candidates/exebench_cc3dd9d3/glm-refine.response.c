void __cdecl AssignBit(unsigned __int64 *array, int bit, int value)
{
  // Calculate the index of the 64-bit element in the array
  unsigned __int64 index = (unsigned __int64)bit >> 6;
  
  // Create a bitmask for the specific bit (modulo 64 handles 64-bit wraparound)
  unsigned __int64 mask = 1ULL << (bit & 0x3F);

  // Set or clear the bit based on the boolean 'value'
  if (value)
    array[index] |= mask;
  else
    array[index] &= ~mask;
}
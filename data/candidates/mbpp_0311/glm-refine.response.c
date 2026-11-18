int __cdecl func0(int n)
{
  int bit_pos;   // Tracks the position of the highest 0-bit
  int temp;      // Temporary variable for bit traversal
  int curr_pos;  // Current bit position being checked

  // Check if n is of the form 2^k - 1 (all 1s in binary).
  // For such numbers, (n + 1) is a power of 2, so (n + 1) & n == 0.
  if ( ((n + 1) & n) == 0 )
    return n;

  bit_pos = 0;
  temp = n;
  curr_pos = 0;

  // Traverse the bits of n from least significant to most significant
  while ( temp )
  {
    // If the current bit is 0, update bit_pos to this position.
    // Since we traverse from LSB to MSB, bit_pos ends up holding
    // the position of the highest 0-bit.
    if ( (temp & 1) == 0 )
      bit_pos = curr_pos;

    ++curr_pos;
    temp >>= 1;
  }

  // Set the highest 0-bit to 1 and return the modified value
  return (1 << bit_pos) | n;
}
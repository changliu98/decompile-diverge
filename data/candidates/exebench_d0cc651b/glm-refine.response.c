void __cdecl increment(unsigned int *n)
{
  unsigned int bit;   // Represents the current bit being processed
  unsigned int value; // A copy of the input value being manipulated

  value = *n;
  
  // Iterate through the bits of 'value' starting from the least significant bit (LSB).
  // The loop continues as long as the current bit is set (1).
  for ( bit = 1; (bit & value) != 0; bit <<= 1 )
  {
    // Clear the current bit (since it is 1, XORing it with 'bit' makes it 0)
    value ^= bit;
  }
  
  // Set the first 0 bit to 1 (which stopped the loop) to complete the increment
  *n = value ^ bit;
}
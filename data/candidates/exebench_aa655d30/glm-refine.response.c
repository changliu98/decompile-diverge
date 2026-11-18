int __cdecl decToBin(int n, int *binary)
{
  int remainder = n;
  unsigned int bit_mask = 1;
  unsigned int bit_count = 0;

  // Find the smallest power of 2 strictly greater than `n`
  // to determine the number of bits required to represent `n`.
  while (bit_mask <= (unsigned int)n)
  {
    bit_mask <<= 1; // Equivalent to bit_mask *= 2
    bit_count++;
  }

  // Shift bit_mask down to the highest power of 2 less than or equal to `n`
  bit_mask >>= 1;
  
  // The loop runs `bit_count` times, writing from the most significant 
  // bit down to the least significant bit.
  for (int i = bit_count - 1; i >= 0; --i)
  {
    // Check if the current power of 2 can be subtracted from the remainder
    if ((remainder - (int)bit_mask) < 0)
    {
      binary[bit_count - 1 - i] = 0;
    }
    else
    {
      remainder -= (int)bit_mask;
      binary[bit_count - 1 - i] = 1;
    }
    
    bit_mask >>= 1; // Move to the next lower power of 2
  }

  return bit_count - 1;
}
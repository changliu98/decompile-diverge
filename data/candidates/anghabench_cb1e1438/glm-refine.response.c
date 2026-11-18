unsigned int __cdecl gf32_mod(unsigned __int64 r, int high_bit)
{
  // The constant 517762881 is the hexadecimal value 0x1ED71B41.
  // In the context of Galois Field (GF) arithmetic, this represents the 
  // irreducible polynomial used for modulo operations.
  const unsigned __int64 GF_POLY = 0x1ED71B41;

  while (high_bit >= 32)
  {
    // Check if the current high bit is set in 'r'
    if ((r >> high_bit) & 1)
    {
      // Shift the polynomial to align with the current high bit and XOR it into 'r'
      // The cast to unsigned char ensures well-defined wrap-around behavior 
      // if high_bit - 32 were to exceed 31, though practically it shouldn't here.
      r ^= GF_POLY << (unsigned char)(high_bit - 32);
    }
    --high_bit;
  }
  
  // After clearing all bits 32 and above, the remainder fits in a 32-bit integer
  return (unsigned int)r;
}
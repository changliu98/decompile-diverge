void __cdecl intToBin(unsigned int n, int *binary)
{
  for (int i = 0; i < 8; ++i)
  {
    // Extract the most significant bit (MSB) of the lowest byte
    binary[i] = (n & 0x80) ? 1 : 0;
    
    // Shift the bits to the left by 1
    n <<= 1;
  }
}
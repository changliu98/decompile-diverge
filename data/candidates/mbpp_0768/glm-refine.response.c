bool __cdecl func0(unsigned int x)
{
  int bit_count = 0;
  
  // Brian Kernighan's algorithm to count the number of set bits (1s)
  while (x)
  {
    x &= x - 1;
    ++bit_count;
  }
  
  // Return true if the number of set bits is odd (parity check)
  return (bit_count & 1) != 0;
}
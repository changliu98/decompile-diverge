bool __cdecl func0(int x)
{
  int popcount = 0;
  
  // Brian Kernighan's algorithm to count set bits
  while (x)
  {
    x &= x - 1; 
    ++popcount;
  }
  
  return (popcount % 2) == 0;
}
int __cdecl rand_r(unsigned int *nextp)
{
  unsigned int next = *nextp;
  
  // Linear congruential generator (LCG) step
  next = (next * 1103515245) + 12345;
  *nextp = next;
  
  // Extract the upper 16 bits and mask to 15 bits (0-32767)
  return (next >> 16) & 0x7FFF;
}
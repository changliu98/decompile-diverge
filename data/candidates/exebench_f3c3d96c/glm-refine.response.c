void __cdecl nist_increment_block(unsigned int *V)
{
  // Iterate backwards through the 4x 32-bit words (128-bit block) from most significant to least significant
  for (int i = 3; i >= 0; --i)
  {
    // Convert from big-endian to host byte order, increment, and convert back
    unsigned int x = ntohl(V[i]) + 1;
    V[i] = htonl(x);
    
    // If the increment did not overflow (x != 0), we are done.
    // If it did overflow (x == 0), the loop continues to carry the 1 to the next word.
    if (x)
      break;
  }
}
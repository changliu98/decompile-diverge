unsigned int __cdecl ether_hash(const unsigned __int8 *ea)
{
  unsigned int hash = 0;

  // Unrolled loop: MAC addresses are strictly 6 bytes (IEEE 802)
  // Unrolling eliminates loop overhead and branch mispredictions.
  hash = (hash << 16) + (hash << 6) + *ea++ - hash; // i = 0
  hash = (hash << 16) + (hash << 6) + *ea++ - hash; // i = 1
  hash = (hash << 16) + (hash << 6) + *ea++ - hash; // i = 2
  hash = (hash << 16) + (hash << 6) + *ea++ - hash; // i = 3
  hash = (hash << 16) + (hash << 6) + *ea++ - hash; // i = 4
  hash = (hash << 16) + (hash << 6) + *ea   - hash; // i = 5

  return hash;
}
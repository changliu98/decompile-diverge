void bitfield_set(unsigned_long *bits,int bit)

{
  int bit_local;
  unsigned_long *bits_local;
  
  bits[(ulong)(long)bit >> 6] = 1L << ((byte)bit & 0x3f) | bits[(ulong)(long)bit >> 6];
  return;
}
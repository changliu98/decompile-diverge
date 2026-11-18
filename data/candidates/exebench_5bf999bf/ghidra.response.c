void clear_bit(int nr,unsigned_long *addr)

{
  byte *pbVar1;
  unsigned_long *addr_local;
  int nr_local;
  
  pbVar1 = (byte *)((long)addr + ((long)nr >> 3));
  *pbVar1 = *pbVar1 & ~('\x01' << (nr & 7U));
  return;
}
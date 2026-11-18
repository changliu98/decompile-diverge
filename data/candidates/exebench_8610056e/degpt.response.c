int test_and_set_bit(int nr,unsigned_long *addr)

{
  byte *pbVar1;
  byte bVar2;
  int oldbit;
  unsigned_long *addr_local;
  int nr_local;
  
  LOCK();
  pbVar1 = (byte *)((long)addr + ((long)nr >> 3));
  bVar2 = *pbVar1;
  *pbVar1 = *pbVar1 | '\x01' << (nr & 7U);
  UNLOCK();
  return -(uint)((bVar2 >> (nr & 7U) & 1) != 0);
}
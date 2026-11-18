void clear_bit(int nr,unsigned_long *addr)

{
  unsigned_long *addr_local;
  int nr_local;
  
  addr[(ulong)(long)nr >> 6] =
       (1L << ((byte)nr & 0x3f) ^ 0xffffffffffffffffU) & addr[(ulong)(long)nr >> 6];
  return;
}
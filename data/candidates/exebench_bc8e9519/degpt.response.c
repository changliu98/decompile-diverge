void generic_set_bit(int nr,unsigned_long *addr)

{
  unsigned_long *p;
  unsigned_long mask;
  unsigned_long *addr_local;
  int nr_local;
  
  addr[nr / 0x20] = 1L << ((byte)((long)nr % 0x20) & 0x3f) | addr[nr / 0x20];
  return;
}
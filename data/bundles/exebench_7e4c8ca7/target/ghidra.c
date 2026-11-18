void change_bit(int nr,unsigned_long *addr)

{
  unsigned_long *addr_local;
  int nr_local;
  
  addr[nr / 0x40] = addr[nr / 0x40] ^ 1L << ((byte)((long)nr % 0x40) & 0x3f);
  return;
}
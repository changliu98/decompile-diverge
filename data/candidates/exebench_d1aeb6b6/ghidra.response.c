void bitmap_clear(unsigned_long *map,int start,int nr)

{
  ulong local_40;
  unsigned_long mask_to_clear;
  int bits_to_clear;
  int size;
  unsigned_long *p;
  int nr_local;
  int start_local;
  unsigned_long *map_local;
  
  p = map + start / 0x40;
  mask_to_clear = -1L << ((byte)((long)start % 0x40) & 0x3f);
  bits_to_clear = 0x40 - start % 0x40;
  nr_local = nr;
  while (-1 < nr_local - bits_to_clear) {
    *p = (mask_to_clear ^ 0xffffffffffffffff) & *p;
    nr_local = nr_local - bits_to_clear;
    mask_to_clear = 0xffffffffffffffff;
    p = p + 1;
    bits_to_clear = 0x40;
  }
  if (nr_local != 0) {
    if ((start + nr) % 0x40 == 0) {
      local_40 = 0xffffffffffffffff;
    }
    else {
      local_40 = (1L << ((byte)((long)(start + nr) % 0x40) & 0x3f)) - 1;
    }
    *p = (local_40 & mask_to_clear ^ 0xffffffffffffffff) & *p;
  }
  return;
}
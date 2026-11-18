uint gf32_mod(unsigned_long_long r,int high_bit)

{
  int j;
  int high_bit_local;
  unsigned_long_long r_local;
  
  r_local = r;
  for (j = high_bit; 0x1f < j; j = j + -1) {
    if ((1L << ((byte)j & 0x3f) & r_local) != 0) {
      r_local = 0x1edc6f41L << ((byte)j - 0x20 & 0x3f) ^ r_local;
    }
  }
  return (uint)r_local;
}
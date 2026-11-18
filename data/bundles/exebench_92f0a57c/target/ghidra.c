double HTS_rnd(unsigned_long *next)

{
  double r;
  unsigned_long *next_local;
  
  *next = *next * 0x41c64e6d + 0x3039;
  return (double)(*(uint *)((long)next + 2) & 0x7fff) / DAT_00102008;
}
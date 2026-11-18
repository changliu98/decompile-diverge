int FABSQ(unsigned_long *rd,unsigned_long *rs2)

{
  unsigned_long *rs2_local;
  unsigned_long *rd_local;
  
  *rd = *rs2 & 0x7fffffffffffffff;
  rd[1] = rs2[1];
  return 1;
}
int FNEGQ(unsigned_long *rd,unsigned_long *rs2)

{
  unsigned_long *rs2_local;
  unsigned_long *rd_local;
  
  *rd = *rs2 ^ 0x8000000000000000;
  rd[1] = rs2[1];
  return 1;
}
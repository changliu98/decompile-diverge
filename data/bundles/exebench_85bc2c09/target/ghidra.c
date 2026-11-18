void yxyDES2_Int2Bits(uint _src,char *dstBits)

{
  uint i;
  char *dstBits_local;
  uint _src_local;
  
  for (i = 0; i < 4; i = i + 1) {
    dstBits[i] = (char)((_src << ((byte)i & 0x1f) & 8) >> 3);
  }
  return;
}
static unsigned reassemble_21(unsigned word) {
  unsigned result;
  result = (word & 0x00000001) << 20;
  result |= (word & 0x00000040) << 7;
  result |= (word & 0x00000080) << 14;
  result |= (word & 0x00000002) << 12;
  result |= (word & 0x00000060) << 8;
  return result;
}
int reassemble_21(int as21)

{
  int as21_local;
  
  return (int)(as21 & 0x100000U) >> 0x14 | (int)(as21 & 0xffe00U) >> 8 | (as21 & 0x180U) << 7 |
         (as21 & 0x7cU) << 0xe | (as21 & 3U) << 0xc;
}
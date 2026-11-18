static int reassemble_21(int as21)
{
 return ((as21 & 0x100000) >> 20) |
  ((as21 & 0xffe00) >> 8) |
  ((as21 & 0x180) << 7) |
  ((as21 & 0x7c) << 14) |
  ((as21 & 3) << 12);
}
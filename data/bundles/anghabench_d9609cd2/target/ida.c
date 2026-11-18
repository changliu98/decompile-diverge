int __cdecl reassemble_21(int as21)
{
  return ((as21 & 3) << 12) | ((as21 & 0x7C) << 14) | ((as21 & 0x180) << 7) | ((as21 & 0xFFE00) >> 8) | ((as21 & 0x100000) >> 20);
}
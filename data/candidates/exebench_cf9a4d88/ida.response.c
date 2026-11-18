int __cdecl FABSQ(unsigned __int64 *rd, unsigned __int64 *rs2)
{
  *rd = *rs2 & 0x7FFFFFFFFFFFFFFFLL;
  rd[1] = rs2[1];
  return 1;
}